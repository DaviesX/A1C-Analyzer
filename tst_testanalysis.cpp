#include <iostream>
#include "csv.h"
#include "deltaanalysis.h"
#include "analyzer.h"
#include "tst_testanalysis.h"


void test_delta_analysis()
{
        std::vector<MedicationOrder> orders;

        csv::load_medication_order("in_order.csv", orders);
        csv::load_medication_order("out_order.csv", orders);

        std::vector<LabMeasure> measures;
        csv::load_lab_measure("lab.csv", measures);

        std::vector<DeltaAnalysis> delta;
        std::vector<DeltaAnalysis> filtered;
        analysis::delta(measures, orders, delta);
        analysis::filter(delta, 7.0f, filtered);

        for (auto d: filtered)
                std::cout << d << std::endl;

        csv::write_delta_analysis("delta.csv", filtered);
}
