#include "medicationorder.h"
#include "labmeasure.h"
#include "delta.h"


Delta::Delta(const MedicationOrder& order,
                             const LabMeasure& lab):
        order(order),
        lab(lab),
        delta_tr(0),
        delta_tm(0),
        triggered(false),
        medication_changed(false)
{
}

void Delta::write(std::ostream& os) const
{
        os << order.pid << ","
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
           << order.instructions << ","

           << lab.test_date << ","
           << lab.observation << ","
           << lab.a1c << ","

           << delta_tr << ","
           << delta_tm << ","
           << triggered << ","
           << recovered << ","
           << medication_changed;
}
