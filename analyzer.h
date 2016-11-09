#ifndef ANALYZER_H
#define ANALYZER_H

#include <set>
#include <vector>
#include "linkedbst.h"
#include "bst.h"
#include "medicationorder.h"
#include "labmeasure.h"
#include "drugfilter.h"
#include "deltaanalysis.h"

namespace analysis
{
void preprocess(std::vector<LabMeasure>& measures, const std::string& keyword, const float a1c_lvl,
                std::set<int>& lab_patients, LinkedBST<LabMeasure>& result);
void preprocess(std::vector<MedicationOrder>& orders, std::vector<DrugFilter>& filter, LinkedBST<MedicationOrder>& result);
void join(LinkedBST<LabMeasure>& measures, std::set<int>& lab_patients,
          LinkedBST<MedicationOrder>& orders, std::vector<DeltaAnalysis>& join);
void filter(const std::vector<DeltaAnalysis>& delta, float a1c_margin, std::vector<DeltaAnalysis>& filtered);
void delta(const std::vector<DeltaAnalysis>& raw, std::vector<DeltaAnalysis>& delta, float a1c_margin);
}


#endif // ANALYZER_H

