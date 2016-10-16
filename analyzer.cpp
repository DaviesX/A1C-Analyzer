#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "linkedbst.h"
#include "bst.h"
#include "labmeasure.h"
#include "medicationorder.h"
#include "deltaanalysis.h"
#include "analyzer.h"
#include "timeddata.h"


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
        std::sort(a_labs.begin(), a_labs.end(), cmp<LabMeasure>);
        std::sort(a_orders.begin(), a_orders.end(), cmp<MedicationOrder>);

        unsigned j = 0;
        for (unsigned i = 0; i < a_labs.size() - 1; i ++) {
                unsigned lower = a_labs[i].time_offset();
                unsigned upper = i != a_labs.size() - 1 ? a_labs[i + 1].time_offset() : 0XFFFFFFFF;
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

void delta_analysis(std::vector<LabMeasure>& measures, std::vector<MedicationOrder>& orders, std::vector<DeltaAnalysis>& delta)
{
        ::shuffle<LabMeasure>(measures);
        ::shuffle<MedicationOrder>(orders);

        BST<unsigned> all_patient_data;
        for (LabMeasure measure: measures)
                all_patient_data.insert(measure.pid());
        std::vector<unsigned> all_patients;
        all_patient_data.extract(all_patients);

        LinkedBST<MedicationOrder> order_data;
        for (MedicationOrder order: orders)
                order_data.insert(order);
        LinkedBST<LabMeasure> lab_data;
        std::locale loc;
        for (LabMeasure measure: measures) {
                std::string upper("");
                for (unsigned i = 0; i < measure.desc().length(); i ++)
                        upper += std::toupper(measure.desc().at(i), loc);
                if (upper.find("A1C") != std::string::npos)
                        lab_data.insert(measure);
        }

        std::vector<LabMeasure> a_labs;
        std::vector<MedicationOrder> a_orders;
        for (unsigned pid: all_patients) {
                LinkedList<LabMeasure>* p_measures = lab_data.find(LabMeasure(pid));
                LinkedList<MedicationOrder>* p_orders = order_data.find(MedicationOrder(pid));
                if (p_measures == nullptr || p_orders == nullptr)
                        continue;
                a_labs.clear();
                a_orders.clear();

                p_measures->extract(a_labs);
                p_orders->extract(a_orders);

                merge_into_delta(pid, a_labs, a_orders, delta);
        }
}
