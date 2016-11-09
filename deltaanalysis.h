#ifndef DELTAANALYSIS_H
#define DELTAANALYSIS_H

#include <string>
#include <ostream>
#include "medicationorder.h"
#include "labmeasure.h"

class DeltaAnalysis
{
        friend std::ostream& operator << (std::ostream& os, const DeltaAnalysis& delta);
public:
        DeltaAnalysis(const MedicationOrder& order, const LabMeasure& lab);

        static void write_head(std::ostream& os)
        {
                os << "Id,"
                   << "Diabetes_Flag,"
                   << "Heart_Failure_Flag,"
                   << "Visit Type,"
                   << "OrderYear,"
                   << "OrderDate_Days,"
                   << "OrderType,"
                   << "OrderStatus,"
                   << "DiscontinueReason,"
                   << "TherapeuticCategory,"
                   << "GenericItemName,"
                   << "Order Name,"
                   << "Dose,"
                   << "UOM,"
                   << "QuantityAmount,"
                   << "DurationAmount,"
                   << "NumRefills,"
                   << "Route,"
                   << "PrescriptionType,"
                   << "Frequency,"
                   << "IsPRN,"
                   << "Instructions,"

                   << "Lab_Test_Date,"
                   << "Lab_Observation,"
                   << "A1C,"

                   << "Delta_TR,"
                   << "Delta_TM,"
                   << "Triggered,"
                   << "Recovered,"
                   << "MedicationChanged";
        }

        void write(std::ostream& os) const;

        MedicationOrder order;
        LabMeasure lab;

        int delta_tr;
        int delta_tm;
        bool triggered;
        bool recovered;
        bool medication_changed;
};

inline std::ostream& operator << (std::ostream& os, const DeltaAnalysis& delta)
{
        os << "DeltaAnalysis = [";
        delta.write(os);
        os << "]";
        return os;
}


#endif // DELTAANALYSIS_H
