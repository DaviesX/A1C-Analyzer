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
        const unsigned n = objs.size();
        for (unsigned i = 1; i < n; i ++) {
                unsigned r = rand()/(float) RAND_MAX * i;
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

void merge_into_delta(unsigned pid,
                      std::vector<LabMeasure>& a_labs,
                      std::vector<MedicationOrder>& a_orders,
                      std::vector<DeltaAnalysis>& delta)
{
        std::sort(a_labs.begin(), a_labs.end(), analysis::cmp<LabMeasure>);
        std::sort(a_orders.begin(), a_orders.end(), analysis::cmp<MedicationOrder>);

        unsigned j = 0;
        for (unsigned i = 0; i < a_labs.size(); i ++) {
                unsigned lower = a_labs[i].time_offset();
                unsigned upper = i != a_labs.size() - 1 ? a_labs[i + 1].time_offset() : 10000;
                for (; j < a_orders.size(); j ++) {
                        if (a_orders[j].time_offset() < lower)
                                continue;
                        if (a_orders[j].time_offset() > upper)
                                break;
                        delta.push_back(DeltaAnalysis(a_orders[j].oid(), pid,
                                                      a_orders[j].time_offset() - a_labs[i].time_offset(),
                                                      a_orders[j].category(), a_orders[j].desc(),
                                                      a_labs[i].desc(), a_labs[i].a1c()));
                }
        }
}

std::hash<std::string> str_hash;

struct TotalOrderKey
{
        TotalOrderKey(unsigned pid, const std::string& desc, unsigned date):
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

        unsigned        pid;
        unsigned        desc_hash;
        unsigned        date;
};


void preprocess(std::vector<LabMeasure>& measures, const std::string& keyword, const float a1c_lvl,
                std::set<unsigned>& lab_patients, LinkedBST<LabMeasure>& result)
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

void join(LinkedBST<LabMeasure>& measures, std::set<unsigned>& lab_patients,
          LinkedBST<MedicationOrder>& orders, std::vector<DeltaAnalysis>& join)
{
        std::vector<LabMeasure> a_labs;
        std::vector<MedicationOrder> a_orders;
        for (unsigned pid: lab_patients) {
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
        unsigned last_id = -1;
        unsigned last_date;
        unsigned offset = 0;
        for (unsigned i = 0; i < raw.size(); i ++) {
                if (raw[i].patient_id() != last_id) {
                        offset = 0;
                        last_id = raw[i].patient_id();
                        last_date = raw[i].time_offset();
                }
                offset += raw[i].time_offset() - last_date;
                delta.push_back(DeltaAnalysis(raw[i], offset, raw[i].a1c() >= a1c_margin));
        }
}

}
