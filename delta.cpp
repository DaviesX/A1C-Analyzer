#include <limits>
#include "medicationorder.h"
#include "labmeasure.h"
#include "delta.h"


// Simple Delta.
csv::SimpleDelta::SimpleDelta(int pid, int date, float a1c):
        pid(pid), a1c(a1c), date(date)
{
}

void
csv::SimpleDelta::write(std::ostream& os) const
{
        os << pid << ",";
        os << date << ",";
        os << a1c << ","
           << delta_tr << ","
           << delta_tm << ","
           << triggered << ","
           << recovered << ","
           << medication_changed;
}

// Full Delta.
csv::Delta::Delta(const MedicationOrder& order, const LabMeasure& lab):
        SimpleDelta(lab.pid, order.date(), lab.a1c), order(order), lab(lab), has_order(true)
{
}

csv::Delta::Delta(const LabMeasure& lab):
        SimpleDelta(lab.pid, lab.date(), lab.a1c), order(lab.pid), lab(lab), has_order(false)
{
}

void
csv::Delta::write(std::ostream& os) const
{
        if (has_order) {
                os << pid << ","
                   << order.diabetes << ","
                   << order.heart_failure << ","
                   << order.visit_type << ","
                   << order.order_year << ","
                   << order.start_date << ","
                   << order.order_type << ","
                   << order.order_status << ","
                   << order.discontinue_reason << ","
                   << order.med_category << ","
                   << order.med_name << ","
                   << order.order_name << ","
                   << order.dose << ","
                   << order.uom << ","
                   << order.quantity << ","
                   << order.duration << ","
                   << order.num_refills << ","
                   << order.route << ","
                   << order.presc_type << ","
                   << order.frequency << ","
                   << order.is_prn << ","
                   << order.instructions << ",";
        } else {
                os << ",,,,,,,,,,,,,,,,,,,,,,";
        }

        os << lab.test_date << ",";
        os << lab.observation << ","
           << lab.a1c << ",";

        os << delta_tr << ","
           << delta_tm << ","
           << triggered << ","
           << recovered << ","
           << medication_changed;
}
