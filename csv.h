#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <string>
#include <vector>
#include "medicationorder.h"
#include "labmeasure.h"
#include "drugfilter.h"
#include "deltaanalysis.h"

#define COL_DELIM       ','

namespace csv
{
void load_medication_order(const std::string& filename, std::vector<MedicationOrder>& orders);
void load_lab_measure(const std::string& filename, std::vector<LabMeasure>& measures);
void load_drug_filter(const std::string& filename, std::vector<DrugFilter>& filter);
void write_delta_analysis(const std::string& filename, std::vector<DeltaAnalysis>& analysis);
}

#endif  // CSV_LOADER_H
