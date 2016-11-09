#include <iostream>
#include <string>
#include <set>
#include "csv.h"
#include "deltaanalysis.h"
#include "analyzer.h"
#include "drugfilter.h"
#include "tst_testanalysis.h"


void test_delta_analysis()
{
        std::vector<DrugFilter> filter;
        csv::load_drug_filter("filter.csv", filter);

        std::vector<MedicationOrder> orders;

        //csv::load_medication_order("order.csv", orders);
        csv::load_medication_order("order2.csv", orders);

        std::vector<LabMeasure> measures;
        csv::load_lab_measure("lab.csv", measures);

        LinkedBST<LabMeasure> cleaned_lab;
        LinkedBST<MedicationOrder> cleaned_orders;
        std::set<int> lab_patients;

        analysis::preprocess(measures, "A1C", 0.0f, lab_patients, cleaned_lab);
        analysis::preprocess(orders, filter, cleaned_orders);

        std::vector<DeltaAnalysis> joined, delta;
        analysis::join(cleaned_lab, lab_patients, cleaned_orders, joined);
        analysis::delta(joined, delta, 8.0f);

        //for (auto d: delta)
        //        std::cout << d << std::endl;

        csv::write_delta_analysis("result.csv", delta);
}

