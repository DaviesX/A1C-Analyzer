#include <iostream>
#include <vector>
#include "labmeasure.h"
#include "medicationorder.h"
#include "csv.h"
#include "tst_testcsv.h"


void test_csv()
{
        std::vector<MedicationOrder> orders;
        CSV csv;
        csv.load_medication_order("in_order.csv", orders);
        for (MedicationOrder order: orders) {
                std::cout << order << std::endl;
        }

        std::vector<LabMeasure> measures;
        csv.load_lab_measure("lab.csv", measures);
        for (LabMeasure measure: measures) {
                std::cout << measure << std::endl;
        }
}
