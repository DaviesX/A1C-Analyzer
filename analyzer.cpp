#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <functional>
#include "linkedbst.h"
#include "bst.h"
#include "labmeasure.h"
#include "medicationorder.h"
#include "delta.h"
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
                      std::vector<Delta>& delta)
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
                        delta.push_back(Delta(a_orders[j], LabMeasure(a_labs[i])));
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
        for (DrugFilter drug: filter)
                if (drug.is_filtered)
                        filtered_med.insert(drug.category);

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
          LinkedBST<MedicationOrder>& orders, std::vector<Delta>& join)
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

void filter(const std::vector<Delta>& delta, float a1c_margin, std::vector<Delta>& filtered)
{
        for (Delta d: delta) {
                if (d.lab.a1c >= a1c_margin)
                        filtered.push_back(d);
        }
}

unsigned patient_range(const std::vector<Delta>& deltas, int i)
{
        int curr_id = deltas[i].order.pid;
        for (unsigned j = i; j < deltas.size(); j ++) {
                if (deltas[j].order.pid != curr_id)
                        return j;
        }
        return deltas.size();
}

struct order_compare {
        bool operator() (const Delta& lhs, const Delta& rhs) const
        {
                std::stringstream s1,s2;
                s1 << lhs.order.order_name << lhs.order.dose;
                s2 << rhs.order.order_name << rhs.order.dose;
                return s1.str() < s2.str();
        }
};

void extract_delta(const std::vector<Delta>& raw, std::vector<Delta>& delta, float a1c_margin)
{
        std::set<Delta, order_compare> curr_meds;

        for (unsigned i = 0; i < raw.size(); i ++) {
                unsigned end = analysis::patient_range(raw, i);

                bool ts = false;
                bool tr = false;

                int triggered_date = -1;
                int recovery_date = -1;

                curr_meds.clear();

                for (; i < end; i ++) {
                        Delta da = raw[i];

                        // Detect a1c trigger.
                        if (da.lab.a1c < a1c_margin) {
                                if (ts) {
                                        recovery_date = da.lab.test_date;
                                        tr = true;
                                        ts = false;
                                }
                        } else {
                                triggered_date = da.lab.test_date;
                                ts = true;
                                tr = false;
                        }

                        // Remove expired medications.
                        int curr_date = da.lab.test_date;
                        const MedicationOrder& new_med = da.order;
                        for (std::set<Delta>::iterator it = curr_meds.begin(); it != curr_meds.end(); ) {
                                const Delta& curr_med = *it;
                                const MedicationOrder& order = curr_med.order;
                                int expiration = order.date() + (1 + order.num_refills)*order.duration;
                                if (curr_date > expiration &&
                                    !(order.med_name == new_med.med_name && order.dose == new_med.dose))
                                        it = curr_meds.erase(it);
                                else
                                        ++ it;
                        }

                        // Update trigger information.
                        da.triggered = ts;
                        da.recovered = tr;
                        if (tr)
                                da.delta_tr = recovery_date - triggered_date;
                        else
                                da.delta_tr = -1;

                        // Detect medication change.
                        std::set<Delta>::iterator old = curr_meds.find(da);
                        da.medication_changed = old == curr_meds.end();

                        if (old == curr_meds.end())
                                curr_meds.insert(da);

                        delta.push_back(da);
                }
        }
}

void extract_medication_set(const std::vector<Delta>& raw, int pid, int before_date, std::vector<MedicationOrder>& orders)
{
        std::set<Delta, order_compare> curr_meds;

        for (unsigned i = 0; i < raw.size(); i ++) {
                Delta da = raw[i];
                if (da.lab.pid != pid)
                        continue;

                unsigned end = analysis::patient_range(raw, i);

                for (; i < end; i ++) {
                        da = raw[i];
                        int expiration = da.order.date() + (1 + da.order.num_refills)*da.order.duration;
                        if (da.order.date() < before_date && expiration >= before_date)
                                curr_meds.insert(da);
                }
        }

        for (Delta curr_med: curr_meds) {
                orders.push_back(curr_med.order);
        }

        std::sort(orders.begin(), orders.end(), [](const MedicationOrder& a, const MedicationOrder& b) {
                return a.date() < b.date();
        });
}

}
