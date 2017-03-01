#ifndef DATABASE_H
#define DATABASE_H


#include <vector>
#include <set>

#include "labmeasure.h"
#include "medicationorder.h"
#include "drugfilter.h"
#include "labfilter.h"
#include "dataset.h"
#include "delta.h"

namespace dataset
{

class Database
{
public:
        Database();

        void reset();

        std::vector<csv::MedicationOrder>    	orders;
        std::vector<csv::LabMeasure>         	measures;
        std::set<filter::DrugFilter> 		filter;
        std::set<filter::LabFilter> 		lab_filter;
        std::vector<csv::Delta>			delta;

        patient_records_t			records;
};

}

#endif // DATABASE_H
