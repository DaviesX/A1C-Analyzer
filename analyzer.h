#ifndef ANALYZER_H
#define ANALYZER_H

#include <vector>
#include "medicationorder.h"
#include "labmeasure.h"
#include "deltaanalysis.h"

namespace analysis
{
void delta(std::vector<LabMeasure>& measures, std::vector<MedicationOrder>& orders, std::vector<DeltaAnalysis>& delta);
void filter(const std::vector<DeltaAnalysis>& delta, float a1c_margin, std::vector<DeltaAnalysis>& filtered);
}


#endif // ANALYZER_H

