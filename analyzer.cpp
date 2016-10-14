#include "linkedbst.h"
#include "labmeasure.h"
#include "medicationorder.h"
#include "deltaanalysis.h"
#include "analyzer.h"


void delta_analysis(const std::vector<LabMeasure>& measures, const std::vector<MedicationOrder>& orders, std::vector<DeltaAnalysis>& delta)
{
        LinkedBST<MedicationOrder> order_data;
        for (MedicationOrder order: orders)
                order_data.insert(order);
        LinkedBST<LabMeasure> lab_data;
        for (LabMeasure measure: measures)
                lab_data.insert(measure);
}
