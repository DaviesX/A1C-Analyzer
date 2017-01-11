#ifndef ANALYZER_H
#define ANALYZER_H

#include <set>
#include <vector>
#include "linkedbst.h"
#include "bst.h"
#include "medicationorder.h"
#include "labmeasure.h"
#include "drugfilter.h"
#include "delta.h"

namespace analysis
{
void preprocess(std::vector<LabMeasure>& measures, const std::string& keyword, const float a1c_lvl,
                std::set<int>& lab_patients, LinkedBST<LabMeasure>& result);
void preprocess(std::vector<MedicationOrder>& orders, std::vector<DrugFilter>& filter, LinkedBST<MedicationOrder>& result);
void join(LinkedBST<LabMeasure>& measures, std::set<int>& lab_patients,
          LinkedBST<MedicationOrder>& orders, std::vector<Delta>& join);
void filter(const std::vector<Delta>& extract_delta, float a1c_margin, std::vector<Delta>& filtered);
void extract_delta(const std::vector<Delta>& raw, std::vector<Delta>& extract_delta, float a1c_margin);
void extract_medication_set(const std::vector<Delta>& raw, int pid, int before_date, std::vector<MedicationOrder>& order);
}


#endif // ANALYZER_H

