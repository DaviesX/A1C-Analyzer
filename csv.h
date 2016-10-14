#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <string>
#include <vector>
#include "medicationorder.h"
#include "labmeasure.h"

#define COL_DELIM       ','

class CSV
{
public:
        void            load_medication_order(const std::string& filename, std::vector<MedicationOrder>& orders) const;
        void            load_lab_measure(const std::string& filename, std::vector<LabMeasure>& measures) const;
private:
        void            load_rows(const std::string& filename, std::vector<std::vector<std::string>>& rows) const;
};

#endif  // CSV_LOADER_H
