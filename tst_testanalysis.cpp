#include <iostream>
#include <string>
#include <set>
#include "csv.h"
#include "delta.h"
#include "dataset.h"
#include "medcategory.h"
#include "order2category.h"
#include "drugfilter.h"
#include "labfilter.h"
#include "patientrecord.h"
#include "statistics.h"
#include "tst_testanalysis.h"


void test::test_delta_analysis()
{
        float const a1c_margin = 8.0f;

        std::set<filter::DrugFilter> drug_filter;
        csv::load_drug_filter("../filter.csv", drug_filter);

        std::set<csv::MedCategory> med_categ;
        csv::load_medication_category("../category.csv", med_categ);

        std::set<csv::Order2Category> o2c;
        csv::load_order_map("../order2categ.csv", o2c);

        dataset::join(o2c, med_categ);

        std::set<filter::LabFilter> lab_filter;
        lab_filter.insert(filter::LabFilter("A1C"));

        std::vector<csv::MedicationOrder> in_orders;

        //csv::load_medication_order("order.csv", in_orders);
        //csv::load_medication_order("order2.csv", in_orders);
        csv::load_medication_order("../out_order.csv", in_orders);

        std::vector<csv::LabMeasure> in_measures;
        csv::load_lab_measure("../lab.csv", in_measures);

        dataset::join(o2c, med_categ);

        dataset::patient_measures_t measures;
        dataset::patient_orders_t   orders;
        dataset::make(in_measures, measures);
        dataset::make(in_orders, med_categ, o2c, orders);

        dataset::patient_measures_t measures_filtered;
        dataset::patient_orders_t orders_filtered;
        dataset::patient_records_t records;
        dataset::filter(measures, lab_filter, measures_filtered);
        dataset::filter(orders, drug_filter, orders_filtered);
        dataset::join_time_asc(measures_filtered, orders_filtered, records);

        std::vector<csv::Delta> delta;
        std::vector<csv::SimpleDelta> simple_delta;
        dataset::delta(records, a1c_margin, delta);
        dataset::delta(records, a1c_margin, simple_delta);
        csv::write_delta_analysis("../test_result.csv", delta);
        csv::write_delta_analysis("../test_result_merged.csv", simple_delta);

        analysis::Statistics stat;
        dataset::statistics(records, a1c_margin, stat);
        std::cout << stat << std::endl;
}

