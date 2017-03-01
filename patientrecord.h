#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H

#include <vector>
#include "labmeasure.h"
#include "medicationorder.h"
#include "delta.h"

namespace analysis
{

class PatientRecord
{
public:
        PatientRecord(int pid);

        void add_measure(const csv::LabMeasure& measure);
        void add_order(const csv::MedicationOrder& order);
        void add_measures(const std::vector<csv::LabMeasure>& measures);
        void add_orders(const std::vector<csv::MedicationOrder>& orders);
        void sort_all();
        bool operator<(const PatientRecord& rhs) const;

        void get_analysis(float a1c, std::vector<csv::Delta>& deltas) const;
        void get_analysis(float a1c, std::vector<csv::SimpleDelta>& deltas) const;
        void get_analysis(unsigned around, std::vector<csv::MedicationOrder>& orders) const;

        bool has_recovered(float a1c) const;
private:
        int					pid;
        std::vector<csv::LabMeasure>		labs;
        std::vector<csv::MedicationOrder> 	orders;
};

}

#endif // PATIENTRECORD_H
