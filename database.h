#ifndef DATABASE_H
#define DATABASE_H


#include <vector>
#include <set>

#include "labmeasure.h"
#include "medicationorder.h"
#include "drugfilter.h"
#include "deltaanalysis.h"


class Database
{
public:
        Database();

        void reset();

        std::vector<MedicationOrder>    orders;
        std::vector<LabMeasure>         measures;
        std::vector<DrugFilter>         filter;

        std::set<int>                   lab_patients;
        std::vector<DeltaAnalysis>      joined;
        std::vector<DeltaAnalysis>      delta;
};

#endif // DATABASE_H
