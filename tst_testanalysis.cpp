#include "csv.h"
#include "deltaanalysis.h"
#include "analyzer.h"
#include "tst_testanalysis.h"


void test_delta_analysis()
{
        std::vector<MedicationOrder> orders;
        CSV csv;
        csv.load_medication_order("in_order.csv", orders);

        std::vector<LabMeasure> measures;
        csv.load_lab_measure("lab.csv", measures);

        std::vector<DeltaAnalysis> delta;
        delta_analysis(measures, orders, delta);

        csv.write_delta_analysis("delta.csv", delta);
}
