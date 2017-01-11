#include <iostream>
#include <vector>
#include "labmeasure.h"
#include "medicationorder.h"
#include "delta.h"
#include "csv.h"
#include "tst_testcsv.h"


void test_csv()
{
        std::vector<MedicationOrder> orders;

        csv::load_medication_order("in_order.csv", orders);
        for (MedicationOrder order: orders) {
                std::cout << order << std::endl;
        }

        std::vector<LabMeasure> measures;
        csv::load_lab_measure("lab.csv", measures);
        for (LabMeasure measure: measures) {
                std::cout << measure << std::endl;
        }

//        std::vector<DeltaAnalysis> delta;
//        delta.push_back(DeltaAnalysis(1111, 1, 5, 3, 4, "a1c", "null", "null2", 6.7));
//        delta.push_back(DeltaAnalysis(1112, 1, 6, 3, 4, "a1c", "null", "null2", 8.7));
//        delta.push_back(DeltaAnalysis(1113, 3, 9, 3, 4, "a1c", "null", "null2", 3.2));
//        delta.push_back(DeltaAnalysis(1114, 3, 2, 3, 4, "a1c", "null", "null2", 6.9));
//        delta.push_back(DeltaAnalysis(1115, 5, 1, 3, 4, "a1c", "null", "null2", 6.4));
//        csv::write_delta_analysis("delta.csv", delta);
}
