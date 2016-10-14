#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include "medicationorder.h"
#include "labmeasure.h"

void delta_analysis(const std::vector<LabMeasure>& measures, const std::vector<MedicationOrder>& orders, std::vector<DeltaAnalysis>& delta);


#endif // ANALYZER_H

