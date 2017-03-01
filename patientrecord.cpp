#include <limits>
#include <algorithm>
#include <map>
#include "patientrecord.h"


analysis::PatientRecord::PatientRecord(int pid):
        pid(pid)
{
}

void
analysis::PatientRecord::add_measure(const csv::LabMeasure& measure)
{
        labs.push_back(measure);
}

void
analysis::PatientRecord::add_order(const csv::MedicationOrder& order)
{
        orders.push_back(order);
}

void
analysis::PatientRecord::add_measures(const std::vector<csv::LabMeasure>& measures)
{
        labs.insert(labs.end(), measures.begin(), measures.end());
}

void
analysis::PatientRecord::add_orders(const std::vector<csv::MedicationOrder>& orders)
{
        this->orders.insert(this->orders.end(), orders.begin(), orders.end());
}

void
analysis::PatientRecord::sort_all()
{
        std::sort(labs.begin(), labs.end(), [](const csv::LabMeasure& x, const csv::LabMeasure& y) {
                return x.date() < y.date();
        });
        std::sort(orders.begin(), orders.end(), [](const csv::MedicationOrder& x, const csv::MedicationOrder& y) {
                return x.date() < y.date();
        });
}

bool
analysis::PatientRecord::operator<(const PatientRecord& rhs) const
{
        return pid < rhs.pid;
}

typedef std::map<std::string, csv::MedicationOrder>	categorized_orders_t;
typedef std::pair<std::string, csv::MedicationOrder>	categorized_order_t;

struct SM {
        bool 			is_triggered = false;
        bool			is_triggered_m = false;
        bool 			is_recovered = false;
        unsigned 		trigger_date = 0;
        categorized_orders_t	curr_orders;
        unsigned		curr_date;

        void transit(const csv::LabMeasure& lab, unsigned date, float a1c_margin)
        {
                curr_date = date;
                if (lab.a1c >= a1c_margin) {
                        is_triggered = true;
                        is_recovered = false;
                } else {
                        if (is_triggered)
                                is_recovered = true;
                        is_triggered = false;
                }
        }

        void transit(const csv::MedicationOrder& order, unsigned date)
        {
                curr_date = date;

                categorized_orders_t::iterator it = curr_orders.find(order.med_category);
                if (it != curr_orders.end()) {
                        // Found medication order.
                        const csv::MedicationOrder& order_found = it->second;
                        if (curr_date < order_found.end_date()) {
                                // Intensification.
                                is_triggered_m = true;
                        } else if (curr_date > order_found.end_date() + 5) {
                                // Expired, update.
                                is_triggered_m = true;
                        } else {
                                if (order.dose > order_found.dose) {
                                        // Intensification.
                                        is_triggered_m = true;
                                } else {
                                        // Nothing changed, just a continuation.
                                        is_triggered_m = false;
                                }

                        }
                        it->second = order;
                } else {
                        // Couldn't find the order, medication has changed.
                        is_triggered_m = true;
                        curr_orders.insert(categorized_order_t(order.med_category, order));
                }
        }

        void set(csv::SimpleDelta& delta) const
        {
                delta.triggered = is_triggered;
                delta.recovered = is_recovered;
                delta.medication_changed = is_triggered_m;
                if (is_triggered) {
                        delta.delta_tr = static_cast<int>(curr_date) - static_cast<int>(trigger_date);
                } else {
                        delta.delta_tr = -1;
                }
                if (is_triggered_m) {
                        delta.delta_tm = static_cast<int>(curr_date) - static_cast<int>(trigger_date);
                } else {
                        delta.delta_tm = -1;
                }
        }
};

void
analysis::PatientRecord::get_analysis(float a1c, std::vector<csv::Delta>& deltas) const
{
        SM sm;
        for (unsigned i = 0; i < labs.size(); i ++) {
                unsigned t_curr_lab = labs[i].date();
                unsigned t_next_lab = i == labs.size() - 1 ? std::numeric_limits<unsigned>::max() : labs[i + 1].date();

                sm.transit(labs[i], labs[i].date(), a1c);
                csv::Delta lab_delta(labs[i]);
                sm.set(lab_delta);
                deltas.push_back(lab_delta);

                for (unsigned j = 0; j < orders.size() && orders[j].date() <= t_next_lab; j ++) {
                        if (orders[j].date() >= t_curr_lab || orders[j].end_date() >= t_curr_lab) {
                                sm.transit(orders[j], orders[j].date());
                                csv::Delta order_delta(orders[j], labs[i]);
                                sm.set(order_delta);
                                deltas.push_back(order_delta);
                        }
                }
        }
}

void
analysis::PatientRecord::get_analysis(float a1c, std::vector<csv::SimpleDelta>& deltas) const
{
        std::vector<csv::Delta> detailed;
        get_analysis(a1c, detailed);

        for (unsigned i = 0; i < detailed.size(); i ++) {
                unsigned date = detailed[i].date;
                csv::SimpleDelta curr_delta = detailed[i];
                while (i < detailed.size() && date == detailed[i + 1].date) {
                        for (unsigned k = 0; k < sizeof(curr_delta.trigger_class); k ++) {
                                curr_delta.trigger_class[k] |= detailed[i + 1].trigger_class[k];
                        }
                        curr_delta.medication_changed |= detailed[i + 1].medication_changed;
                        i ++;
                }
                deltas.push_back(curr_delta);
        }
}

void
analysis::PatientRecord::get_analysis(unsigned around, std::vector<csv::MedicationOrder>& orders) const
{
        for (unsigned j = 0; j < orders.size() && orders[j].date() <= around; j ++) {
                if (orders[j].end_date() >= around) {
                        orders.push_back(orders[j]);
                }
        }
}

bool
analysis::PatientRecord::has_recovered(float a1c) const
{
       return labs[labs.size() - 1].a1c < a1c;
}
