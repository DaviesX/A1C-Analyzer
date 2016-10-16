#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include "medicationorder.h"
#include "labmeasure.h"

void delta_analysis(std::vector<LabMeasure>& measures, std::vector<MedicationOrder>& orders, std::vector<DeltaAnalysis>& delta);


#endif // ANALYZER_H

