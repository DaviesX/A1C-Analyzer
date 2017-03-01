#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>
#include <functional>
#include "labmeasure.h"
#include "medicationorder.h"
#include "dataset.h"


void
dataset::sort(std::vector<csv::LabMeasure>& a)
{
        std::sort(a.begin(), a.end(), [](const csv::LabMeasure& x, const csv::LabMeasure& y) {
                return x.date() < y.date();
        });
}

void
dataset::sort(std::vector<csv::MedicationOrder>& a)
{
        std::sort(a.begin(), a.end(), [](const csv::MedicationOrder& x, const csv::MedicationOrder& y) {
                return x.date() < y.date();
        });
}

void
dataset::make(const std::vector<csv::LabMeasure>& in, patient_measures_t& out)
{
        for (const csv::LabMeasure& measure: in) {
                patient_measures_t::iterator it = out.find(measure.pid);
                if (it == out.end()) {
                        std::vector<csv::LabMeasure> measures;
                        measures.push_back(measure);
                        out.insert(patient_measure_t(measure.pid, measures));
                } else {
                        it->second.push_back(measure);
                }
        }
}

void
dataset::make(const std::vector<csv::MedicationOrder>& in, patient_orders_t& out)
{
        for (const csv::MedicationOrder& order: in) {
                patient_orders_t::iterator it = out.find(order.pid);
                if (it == out.end()) {
                        std::vector<csv::MedicationOrder> orders;
                        orders.push_back(order);
                        out.insert(patient_order_t(order.pid, orders));
                } else {
                        it->second.push_back(order);
                }
        }
}

static bool substring_in(const std::set<filter::LabFilter>& filter, const std::string& s)
{
        for (filter::LabFilter f: filter) {
                if (s.npos != s.find(f.keep)) {
                        return true;
                }
        }
        return false;
}

void
dataset::filter(const patient_measures_t& measures, const std::set<filter::LabFilter>& filter, patient_measures_t& filtered)
{
        for (patient_measures_t::const_iterator it = measures.begin(); it != measures.end(); ++ it) {
                std::vector<csv::LabMeasure> target;
                const std::vector<csv::LabMeasure>& measures = it->second;
                for (const csv::LabMeasure& measure: measures) {
                        if (::substring_in(filter, measure.observation)) {
                                target.push_back(measure);
                        }
                }
                filtered.insert(patient_measure_t(it->first, target));
        }
}

void
dataset::filter(const patient_orders_t& orders, const std::set<filter::DrugFilter>& filter, patient_orders_t& filtered)
{
        for (patient_orders_t::const_iterator it = orders.begin(); it != orders.end(); ++ it) {
                std::vector<csv::MedicationOrder> target;
                const std::vector<csv::MedicationOrder>& orders = it->second;
                for (const csv::MedicationOrder& order: orders) {
                        if (filter.end() == filter.find(filter::DrugFilter(order.med_category))) {
                                target.push_back(order);
                        }
                }
                filtered.insert(patient_order_t(it->first, target));
        }
}

void
dataset::join_time_asc(const patient_measures_t& measures, const patient_orders_t& orders, patient_records_t& records)
{
        for (patient_measures_t::const_iterator it = measures.begin(); it != measures.end(); ++ it) {
                analysis::PatientRecord record(it->first);
                record.add_measures(it->second);
                patient_orders_t::const_iterator order_iter = orders.find(it->first);
                if (order_iter != orders.end()) {
                        record.add_orders(order_iter->second);
                        record.sort_all();
                }
                records.insert(patient_record_t(it->first, record));
        }
}

void
dataset::delta(const patient_records_t& record, float a1c, std::vector<csv::Delta>& delta)
{
        for (patient_records_t::const_iterator it = record.begin(); it != record.end(); ++ it) {
                std::vector<csv::Delta> patient_deltas;
                it->second.get_analysis(a1c, patient_deltas);
                delta.insert(delta.end(), patient_deltas.begin(), patient_deltas.end());
        }
}

void
dataset::delta(const patient_records_t& record, float a1c, std::vector<csv::SimpleDelta>& delta)
{
        for (patient_records_t::const_iterator it = record.begin(); it != record.end(); ++ it) {
                std::vector<csv::SimpleDelta> patient_deltas;
                it->second.get_analysis(a1c, patient_deltas);
                delta.insert(delta.end(), patient_deltas.begin(), patient_deltas.end());
        }
}
