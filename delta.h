#ifndef DELTAANALYSIS_H
#define DELTAANALYSIS_H

#include <string>
#include <ostream>
#include "medicationorder.h"
#include "labmeasure.h"

namespace csv
{

class SimpleDelta
{
        friend std::ostream& operator << (std::ostream& os, const SimpleDelta& delta);
public:
        static void write_head(std::ostream& os)
        {
                os << "Id,"
                   << "Date,"
                   << "A1C,"

                   << "Delta_TR,"
                   << "Delta_TM,"
                   << "Triggered,"
                   << "Recovered,"
                   << "MedicationChanged";
        }

public:
        SimpleDelta(int pid, unsigned date, float a1c);

        void write(std::ostream& os) const;
public:
        int		pid;
        float		a1c;
        int 		delta_tr = 0;
        int 		delta_tm = 0;
        bool 		triggered = false;
        bool 		recovered = false;
        bool 		medication_changed = false;
        unsigned	date = 0;
        bool		trigger_class[4];
};

class Delta: public SimpleDelta
{
        friend std::ostream& operator << (std::ostream& os, const Delta& delta);
public:
        Delta(const MedicationOrder& order, const LabMeasure& lab);
        Delta(const LabMeasure& lab);

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

        MedicationOrder 	order;
        LabMeasure 		lab;

        bool			has_order;
};

inline std::ostream& operator << (std::ostream& os, const Delta& delta)
{
        os << "Delta = [";
        delta.write(os);
        os << "]";
        return os;
}

inline std::ostream& operator << (std::ostream& os, const SimpleDelta& delta)
{
        os << "SimpleDelta = [";
        delta.write(os);
        os << "]";
        return os;
}

}


#endif // DELTAANALYSIS_H
