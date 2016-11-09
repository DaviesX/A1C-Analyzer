#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include "linkedbst.h"
#include "bst.h"
#include "labmeasure.h"
#include "medicationorder.h"
#include "deltaanalysis.h"
#include "analyzer.h"
#include "timeddata.h"


namespace analysis
{

template <typename T>
static void shuffle(std::vector<T>& objs)
{
        const int n = objs.size();
        for (int i = 1; i < n; i ++) {
                int r = rand()/(float) RAND_MAX * i;
                T tmp = objs[i];
                objs[i] = objs[r];
                objs[r] = tmp;
        }
}

template <typename T>
static bool cmp(const T& a, const T& b)
{
        return a.date() < b.date();
}

void merge_into_delta(std::vector<LabMeasure>& a_labs,
                      std::vector<MedicationOrder>& a_orders,
                      std::vector<DeltaAnalysis>& delta)
{
        std::sort(a_labs.begin(), a_labs.end(), analysis::cmp<LabMeasure>);
        std::sort(a_orders.begin(), a_orders.end(), analysis::cmp<MedicationOrder>);

        unsigned j = 0;
        for (unsigned i = 0; i < a_labs.size(); i ++) {
                int lower = a_labs[i].date();
                int upper = (int) i != (int) a_labs.size() - 1 ? a_labs[i + 1].date() : 0XFFFFFFFF;
                for (; j < a_orders.size(); j ++) {
                        if (a_orders[j].end_date() < lower)
                                continue;
                        if (a_orders[j].date() > upper)
                                break;
                        delta.push_back(DeltaAnalysis(a_orders[j], LabMeasure(a_labs[i])));
                }
        }
}

std::hash<std::string> str_hash;

struct TotalOrderKey
{
        TotalOrderKey(int pid, const std::string& desc, int date):
                pid(pid), desc_hash(str_hash(desc)), date(date)
        {
        }

        TotalOrderKey(const MedicationOrder& order):
                pid(order.pid), desc_hash(str_hash(order.med_category)), date(order.date())
        {
        }

        TotalOrderKey(const LabMeasure& lab):
                pid(lab.pid), desc_hash(str_hash(lab.observation)), date(lab.date())
        {
        }

        explicit TotalOrderKey(const TotalOrderKey& copy):
                pid(copy.pid), desc_hash(copy.desc_hash), date(copy.date)
        {
        }

        bool operator < (const TotalOrderKey& rhs) const
        {
                return pid < rhs.pid ||
                       desc_hash < rhs.desc_hash ||
                       date < rhs.date;
        }

        bool operator > (const TotalOrderKey& rhs) const
        {
                return pid > rhs.pid ||
                       desc_hash > rhs.desc_hash ||
                       date > rhs.date;
        }

        int        pid;
        int        desc_hash;
        int        date;
};


void preprocess(std::vector<LabMeasure>& measures, const std::string& keyword, const float a1c_lvl,
                std::set<int>& lab_patients, LinkedBST<LabMeasure>& result)
{
        analysis::shuffle<LabMeasure>(measures);

        BST<analysis::TotalOrderKey> existing_objs;
        std::locale loc;
        for (LabMeasure measure: measures) {
                if (measure.a1c < a1c_lvl)
                        continue;

                std::string upper("");
                for (unsigned i = 0; i < measure.observation.length(); i ++)
                        upper += std::toupper(measure.observation.at(i), loc);
                if (upper.find(keyword) == std::string::npos)
                        continue;

                analysis::TotalOrderKey key(measure);
                if (!existing_objs.find(key)) {
                        existing_objs.insert(key);
                        result.insert(measure);
                        lab_patients.insert(measure.pid);
                }
        }
}

void preprocess(std::vector<MedicationOrder>& orders,
                std::vector<DrugFilter>& filter,
                LinkedBST<MedicationOrder>& result)
{
        analysis::shuffle<MedicationOrder>(orders);

        std::set<std::string> filtered_med;
        // for (DrugFilter drug: filter)
        //         if (drug.is_filtered)
        //                 filtered_med.insert(drug.category);

        BST<analysis::TotalOrderKey> existing_objs;
        for (MedicationOrder order: orders) {
                if (filtered_med.find(order.med_category) != filtered_med.end())
                        continue;
                analysis::TotalOrderKey key(order);
                if (!existing_objs.find(key)) {
                        existing_objs.insert(key);
                        result.insert(order);
                }
        }
}

void join(LinkedBST<LabMeasure>& measures, std::set<int>& lab_patients,
          LinkedBST<MedicationOrder>& orders, std::vector<DeltaAnalysis>& join)
{
        std::vector<LabMeasure> a_labs;
        std::vector<MedicationOrder> a_orders;
        for (int pid: lab_patients) {
                LinkedList<LabMeasure>* p_measures = measures.find(LabMeasure(pid));
                LinkedList<MedicationOrder>* p_orders = orders.find(MedicationOrder(pid));
                if (p_measures == nullptr || p_orders == nullptr)
                        continue;
                a_labs.clear();
                a_orders.clear();

                p_measures->extract(a_labs);
                p_orders->extract(a_orders);

                analysis::merge_into_delta(a_labs, a_orders, join);
        }
}

void filter(const std::vector<DeltaAnalysis>& delta, float a1c_margin, std::vector<DeltaAnalysis>& filtered)
{
        for (DeltaAnalysis d: delta) {
                if (d.lab.a1c >= a1c_margin)
                        filtered.push_back(d);
        }
}

unsigned patient_range(const std::vector<DeltaAnalysis>& deltas, int i)
{
        int curr_id = deltas[i].order.pid;
        for (unsigned j = i; j < deltas.size(); j ++) {
                if (deltas[j].order.pid != curr_id)
                        return j;
        }
        return deltas.size();
}

void delta(const std::vector<DeltaAnalysis>& raw, std::vector<DeltaAnalysis>& delta, float a1c_margin)
{
        for (unsigned i = 0; i < raw.size(); i ++) {
                unsigned end = analysis::patient_range(raw, i);

                bool ts = false;
                bool tr = false;

                int triggered_date = -1;
                int recovery_date = -1;

                for (; i < end; i ++) {
                        if (raw[i].lab.a1c < a1c_margin) {
                                if (ts) {
                                        recovery_date = raw[i].lab.test_date;
                                        tr = true;
                                        ts = false;
                                }
                        } else {
                                triggered_date = raw[i].lab.test_date;
                                ts = true;
                                tr = false;
                        }

                        DeltaAnalysis da = raw[i];
                        da.triggered = ts;
                        da.recovered = tr;
                        if (tr)
                                da.delta_tr = recovery_date - triggered_date;
                        else
                                da.delta_tr = -1;

                        delta.push_back(da);
                }
        }
}

}
