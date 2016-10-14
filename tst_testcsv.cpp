#include <iostream>
#include <vector>
#include "labmeasure.h"
#include "medicationorder.h"
#include "deltaanalysis.h"
#include "csv.h"
#include "tst_testcsv.h"


void test_csv()
{
        std::vector<MedicationOrder> orders;
        CSV csv;
        csv.load_medication_order("in_order.csv", orders);
        /*for (MedicationOrder order: orders) {
                std::cout << order << std::endl;
        }*/

        std::vector<LabMeasure> measures;
        csv.load_lab_measure("lab.csv", measures);
        /*for (LabMeasure measure: measures) {
                std::cout << measure << std::endl;
        }*/

        std::vector<DeltaAnalysis> delta;
        delta.push_back(DeltaAnalysis(1111, 1, 5, "a1c", "null", 6.7));
        delta.push_back(DeltaAnalysis(1112, 1, 6, "a1c", "null", 8.7));
        delta.push_back(DeltaAnalysis(1113, 3, 9, "a1c", "null", 3.2));
        delta.push_back(DeltaAnalysis(1114, 3, 2, "a1c", "null", 6.9));
        delta.push_back(DeltaAnalysis(1115, 5, 1, "a1c", "null", 6.4));
        csv.write_delta_analysis("delta.csv", delta);
}
