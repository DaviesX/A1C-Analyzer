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
        return a.time_offset() < b.time_offset();
}

void merge_into_delta(int pid,
                      std::vector<LabMeasure>& a_labs,
                      std::vector<MedicationOrder>& a_orders,
                      std::vector<DeltaAnalysis>& delta)
{
        std::sort(a_labs.begin(), a_labs.end(), analysis::cmp<LabMeasure>);
        std::sort(a_orders.begin(), a_orders.end(), analysis::cmp<MedicationOrder>);

        unsigned j = 0;
        for (unsigned i = 0; i < a_labs.size(); i ++) {
                int lower = a_labs[i].time_offset();
                int upper = (int) i != (int) a_labs.size() - 1 ? a_labs[i + 1].time_offset() : 0XFFFFFFFF;
                for (; j < a_orders.size(); j ++) {
                        if (a_orders[j].time_offset() < lower)
                                continue;
                        if (a_orders[j].time_offset() > upper)
                                break;
                        delta.push_back(DeltaAnalysis(a_orders[j].oid(), pid,
                                                      a_orders[j].time_offset(),
                                                      a_orders[j].category(), a_orders[j].desc(),
                                                      a_labs[i].desc(), a_labs[i].a1c()));
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
                pid(order.pid()), desc_hash(str_hash(order.category())), date(order.time_offset())
        {
        }

        TotalOrderKey(const LabMeasure& lab):
                pid(lab.pid()), desc_hash(str_hash(lab.desc())), date(lab.time_offset())
        {
        }

        TotalOrderKey(const DeltaAnalysis& delta):
                pid(delta.patient_id()), desc_hash(str_hash(delta.desc())), date(delta.time_offset())
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
                if (measure.a1c() < a1c_lvl)
                        continue;

                std::string upper("");
                for (unsigned i = 0; i < measure.desc().length(); i ++)
                        upper += std::toupper(measure.desc().at(i), loc);
                if (upper.find(keyword) == std::string::npos)
                        continue;

                analysis::TotalOrderKey key(measure);
                if (!existing_objs.find(key)) {
                        existing_objs.insert(key);
                        result.insert(measure);
                        lab_patients.insert(measure.pid());
                }
        }
}

void preprocess(std::vector<MedicationOrder>& orders,
                LinkedBST<MedicationOrder>& result)
{
        analysis::shuffle<MedicationOrder>(orders);

        BST<analysis::TotalOrderKey> existing_objs;
        for (MedicationOrder order: orders) {
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

                analysis::merge_into_delta(pid, a_labs, a_orders, join);
        }
}

void filter(const std::vector<DeltaAnalysis>& delta, float a1c_margin, std::vector<DeltaAnalysis>& filtered)
{
        for (DeltaAnalysis d: delta) {
                if (d.a1c() >= a1c_margin)
                        filtered.push_back(d);
        }
}

void delta(const std::vector<DeltaAnalysis>& raw, std::vector<DeltaAnalysis>& delta, float a1c_margin)
{
        bool trigger_status = false;
        int last_id = -1;
        int last_date;
        int offset = 0;
        for (unsigned i = 0; i < raw.size(); i ++) {
                if (raw[i].a1c() < a1c_margin)
                        trigger_status = false;
                if (raw[i].patient_id() != last_id || trigger_status == false) {
                        offset = 0;
                        last_id = raw[i].patient_id();
                        last_date = raw[i].time_offset();
                }
                if (raw[i].a1c() >= a1c_margin)
                        trigger_status = true;
                offset = raw[i].time_offset() - last_date;
                delta.push_back(DeltaAnalysis(raw[i], trigger_status ? offset : 0, raw[i].a1c() >= a1c_margin));
        }
}

}
