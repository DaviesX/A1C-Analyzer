#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <string>
#include <vector>
#include <set>
#include "medicationorder.h"
#include "labmeasure.h"
#include "drugfilter.h"
#include "delta.h"

#define COL_DELIM       ','

namespace csv
{
void load_medication_order(const std::string& filename, std::vector<MedicationOrder>& orders);
void load_lab_measure(const std::string& filename, std::vector<LabMeasure>& measures);
void load_drug_filter(const std::string& filename, std::set<filter::DrugFilter>& filter);
void write_delta_analysis(const std::string& filename, std::vector<Delta>& analysis);
void write_delta_analysis(const std::string& filename, std::vector<SimpleDelta>& analysis);

}

#endif  // CSV_LOADER_H
