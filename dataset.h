#ifndef ANALYZER_H
#define ANALYZER_H

#include <map>
#include <set>
#include <vector>
#include "medicationorder.h"
#include "labmeasure.h"
#include "labfilter.h"
#include "drugfilter.h"
#include "medcategory.h"
#include "order2category.h"
#include "patientrecord.h"
#include "delta.h"
#include "statistics.h"

namespace dataset
{

typedef std::map<int, std::vector<csv::LabMeasure>> patient_measures_t;
typedef std::pair<int, std::vector<csv::LabMeasure>> patient_measure_t;

typedef std::map<int, std::vector<csv::MedicationOrder>> patient_orders_t;
typedef std::pair<int, std::vector<csv::MedicationOrder>> patient_order_t;

typedef std::map<int, analysis::PatientRecord> patient_records_t;
typedef std::pair<int, analysis::PatientRecord> patient_record_t;

void sort(std::vector<csv::LabMeasure>& a);
void sort(std::vector<csv::MedicationOrder>& a);

void make(const std::vector<csv::LabMeasure>& in, patient_measures_t& out);
void make(const std::vector<csv::MedicationOrder>& in,
          const std::set<csv::MedCategory>& med_categ,
          const std::set<csv::Order2Category>& order2categ, patient_orders_t& out);

void join(std::set<csv::Order2Category>& order_map, const std::set<csv::MedCategory>& med_categ);

void filter(const patient_measures_t& measures, const std::set<filter::LabFilter>& filter, patient_measures_t& filtered);
void filter(const patient_orders_t& orders, const std::set<filter::DrugFilter>& filter, patient_orders_t& filtered);
void join_time_asc(const patient_measures_t& measures, const patient_orders_t& orders, patient_records_t& records);

void delta(const patient_records_t& record, float a1c, std::vector<csv::Delta>& delta);
void delta(const patient_records_t& record, float a1c, std::vector<csv::SimpleDelta>& delta);

void statistics(const patient_records_t& records, float a1c, analysis::Statistics& stat);

}


#endif // ANALYZER_H

