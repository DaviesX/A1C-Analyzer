#include <math.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "medicationorder.h"
#include "labmeasure.h"
#include "delta.h"
#include "csv.h"


static void
split(const std::string& s, char delim, std::vector<std::string>& result)
{
        // Split according to the delimiter but skip quotes.
        unsigned last = 0;
        bool in_quote = false;
        for (unsigned i = 0; i < s.length(); i ++) {
                if (s[i] == '\"')
                        in_quote = !in_quote;
                if (in_quote)
                        continue;
                if (s[i] == delim) {
                        result.push_back(s.substr(last, i - last));
                        last = i + 1;
                } else if (i == s.length() - 1) {
                        result.push_back(s.substr(last, i - last + 1));
                }
        }
}

static void
load_rows(const std::string& filename, std::vector<std::vector<std::string>>& rows)
{
        std::ifstream s(filename);
        if (!s.is_open())
                throw "Failed to open " + filename;

        std::string line;
        while (!s.eof()) {
                std::getline(s, line);
                std::vector<std::string> cols;
                ::split(line.substr(0, line.find_last_of("\n\r")), COL_DELIM, cols);
                rows.push_back(cols);
        }
        s.close();
}

static bool
set_column_mapping(const std::string& key, const std::vector<std::string>& ddl, std::map<std::string, unsigned>& col_map)
{
        for (unsigned i = 0; i < ddl.size(); i ++) {
                if (ddl[i] == key) {
                        col_map[key] = i;
                        return true;
                }
        }
        return false;
}

static std::string
safe_fetch(const std::vector<std::string>& parts,
           const std::string& key,
           const std::map<std::string, unsigned>& col_map)
{
        auto it = col_map.find(key);
        if (it->second < parts.size())
                return parts[it->second];
        else
                return std::string("");
}

void
csv::load_medication_order(const std::string& filename, std::vector<MedicationOrder>& orders)
{
        std::vector<std::vector<std::string>> rows;
        load_rows(filename, rows);

        bool first_row = true;
        std::map<std::string, unsigned> col_map;
        for (std::vector<std::string> parts: rows) {
                if (first_row) {
                        std::vector<std::string>& ddl = parts;
                        if (!set_column_mapping("Id", ddl, col_map))
                                throw filename + " is not a medication order file: Column Id doesn't exist";
                        if (!set_column_mapping("Diabetes_Flag", ddl, col_map))
                                throw filename + " is not a medication order file: Column Diabetes_Flag doesn't exist";
                        if (!set_column_mapping("Heart_Failure_Flag", ddl, col_map))
                                throw filename + " is not a medication order file: Column Heart_Failure_Flag doesn't exist";
                        if (!set_column_mapping("Visit Type", ddl, col_map))
                                throw filename + " is not a medication order file: Column Visit Type doesn't exist";
                        if (!set_column_mapping("OrderYear", ddl, col_map))
                                throw filename + " is not a medication order file: Column OrderYear doesn't exist";
                        if (!set_column_mapping("OrderDate_Days", ddl, col_map))
                                throw filename + " is not a medication order file: Column OrderDate_Days doesn't exist";
                        if (!set_column_mapping("OrderType", ddl, col_map))
                                throw filename + " is not a medication order file: Column OrderType doesn't exist";
                        if (!set_column_mapping("OrderStatus", ddl, col_map))
                                throw filename + " is not a medication order file: Column OrderStatus doesn't exist";
                        if (!set_column_mapping("DiscontinueReason", ddl, col_map))
                                throw filename + " is not a medication order file: Column DiscontinueReason doesn't exist";
                        if (!set_column_mapping("TherapeuticCategory", ddl, col_map))
                                throw filename + " is not a medication order file: Column TherapeuticCategory doesn't exist";
                        if (!set_column_mapping("GenericItemName", ddl, col_map))
                                throw filename + " is not a medication order file: Column GenericItemName doesn't exist";
                        if (!set_column_mapping("GenericItemName", ddl, col_map))
                                throw filename + " is not a medication order file: Column GenericItemName doesn't exist";
                        if (!set_column_mapping("Order Name", ddl, col_map))
                                throw filename + " is not a medication order file: Column Order Name doesn't exist";
                        if (!set_column_mapping("Dose", ddl, col_map))
                                throw filename + " is not a medication order file: Column Dose doesn't exist";
                        if (!set_column_mapping("UOM", ddl, col_map))
                                throw filename + " is not a medication order file: Column UOM doesn't exist";
                        if (!set_column_mapping("QuantityAmount", ddl, col_map))
                                throw filename + " is not a medication order file: Column QuantityAmount doesn't exist";
                        if (!set_column_mapping("DurationAmount", ddl, col_map))
                                throw filename + " is not a medication order file: Column DurationAmount doesn't exist";
                        if (!set_column_mapping("NumRefills", ddl, col_map))
                                throw filename + " is not a medication order file: Column NumRefills doesn't exist";
                        if (!set_column_mapping("Route", ddl, col_map))
                                throw filename + " is not a medication order file: Column Route doesn't exist";
                        if (!set_column_mapping("PrescriptionType", ddl, col_map))
                                throw filename + " is not a medication order file: Column PrescriptionType doesn't exist";
                        if (!set_column_mapping("Frequency", ddl, col_map))
                                throw filename + " is not a medication order file: Column Frequency doesn't exist";
                        if (!set_column_mapping("IsPRN", ddl, col_map))
                                throw filename + " is not a medication order file: Column isPRN doesn't exist";
                        if (!set_column_mapping("Instructions", ddl, col_map))
                                throw filename + " is not a medication order file: Column Instructions doesn't exist";
                        first_row = false;
                } else {
                        if (parts.size() > 0) {
                                const std::string id                    = safe_fetch(parts, "Id", col_map);
                                const std::string diabetes_flag         = safe_fetch(parts, "Diabetes_Flag", col_map);
                                const std::string heart_failure_flag    = safe_fetch(parts, "Heart_Failure_Flag", col_map);
                                const std::string visit_type            = safe_fetch(parts, "Visit Type", col_map);
                                const std::string order_year            = safe_fetch(parts, "OrderYear", col_map);
                                const std::string order_date_days       = safe_fetch(parts, "OrderDate_Days", col_map);
                                const std::string order_type            = safe_fetch(parts, "OrderType", col_map);
                                const std::string order_status          = safe_fetch(parts, "OrderStatus", col_map);
                                const std::string discon_reason         = safe_fetch(parts, "DiscontinueReason", col_map);
                                const std::string med_categ             = safe_fetch(parts, "TherapeuticCategory", col_map);
                                const std::string med_name              = safe_fetch(parts, "GenericItemName", col_map);
                                const std::string order_name            = safe_fetch(parts, "Order Name", col_map);
                                const std::string dose                  = safe_fetch(parts, "Dose", col_map);
                                const std::string uom                   = safe_fetch(parts, "UOM", col_map);
                                const std::string quan_amount           = safe_fetch(parts, "QuantityAmount", col_map);
                                const std::string duration              = safe_fetch(parts, "DurationAmount", col_map);
                                const std::string num_refills           = safe_fetch(parts, "NumRefills", col_map);
                                const std::string route                 = safe_fetch(parts, "Route", col_map);
                                const std::string presc_type            = safe_fetch(parts, "PrescriptionType", col_map);
                                const std::string frequency             = safe_fetch(parts, "Frequency", col_map);
                                const std::string is_prn                = safe_fetch(parts, "IsPRN", col_map);
                                const std::string instructions          = safe_fetch(parts, "Instructions", col_map);

                                orders.push_back(MedicationOrder(std::atoi(id.c_str()),
                                                                 diabetes_flag == "Yes",
                                                                 heart_failure_flag == "Yes",
                                                                 visit_type,
                                                                 static_cast<unsigned>(std::atoi(order_year.c_str())),
                                                                 static_cast<int>(std::atoi(order_date_days.c_str())),
                                                                 order_type,
                                                                 order_status,
                                                                 discon_reason,
                                                                 med_categ,
                                                                 med_name,
                                                                 order_name,
                                                                 static_cast<float>(std::atof(dose.c_str())),
                                                                 uom,
                                                                 static_cast<unsigned>(std::atoi(quan_amount.c_str())),
                                                                 static_cast<unsigned>(std::atoi(duration.c_str())),
                                                                 static_cast<unsigned>(std::atoi(num_refills.c_str())),
                                                                 route,
                                                                 presc_type,
                                                                 frequency,
                                                                 is_prn == "1",
                                                                 instructions));
                        }
                }
        }
}

void
csv::load_lab_measure(const std::string& filename, std::vector<LabMeasure>& measures)
{
        std::vector<std::vector<std::string>> rows;
        load_rows(filename, rows);

        bool first_row = true;
        std::map<std::string, unsigned> col_map;
        unsigned min = 0;
        for (std::vector<std::string> parts: rows) {
                if (first_row) {
                        std::vector<std::string>& ddl = parts;
                        if (!set_column_mapping("Id", ddl, col_map))
                                throw filename + " is not a lab test file: Column Id doesn't exist";
                        if (!set_column_mapping("Result", ddl, col_map))
                                throw filename + " is not a lab test file: Column Result doesn't exist";
                        if (!set_column_mapping("Observation", ddl, col_map))
                                throw filename + " is not a lab test file: Column Observation doesn't exist";
                        if (!set_column_mapping("Result_Days", ddl, col_map))
                                throw filename + " is not a lab test file: Column Result_Days doesn't exist";
                        min = std::max(min, col_map["Id"]);
                        min = std::max(min, col_map["Result"]);
                        min = std::max(min, col_map["Observation"]);
                        min = std::max(min, col_map["Result_Days"]);
                        first_row = false;
                } else {
                        if (parts.size() > min) {
                                const std::string& id = parts[col_map["Id"]];
                                const std::string& date_offset = parts[col_map["Result_Days"]];
                                const std::string& desc = parts[col_map["Observation"]];
                                const std::string& result = parts[col_map["Result"]];
                                measures.push_back(LabMeasure(std::atoi(id.c_str()),
                                                              static_cast<int>(std::atoi(date_offset.c_str())), desc,
                                                              static_cast<float>(std::atof(result.c_str()))));
                        }
                }
        }
}

/*
 * Need not to purify.
 *
static std::string purify(const std::string& s)
{
        std::string r;
        for (unsigned i = 0; i < s.length(); i ++) {
                r += s.at(i) == ',' ? '*' : s.at(i);
        }
        return r;
}
*/

void
csv::write_delta_analysis(const std::string& filename, std::vector<Delta>& analysis)
{
        std::ofstream file(filename);
        if (!file.is_open())
                throw std::string("Failed to write to " + filename);

        Delta::write_head(file);
        file << std::endl;
        for (Delta delta: analysis) {
                delta.write(file);
                file << std::endl;
        }
        file.close();
}

void
csv::write_delta_analysis(const std::string& filename, std::vector<SimpleDelta>& analysis)
{
        std::ofstream file(filename);
        if (!file.is_open())
                throw std::string("Failed to write to " + filename);

        SimpleDelta::write_head(file);
        file << std::endl;
        for (SimpleDelta delta: analysis) {
                delta.write(file);
                file << std::endl;
        }
        file.close();
}

void
csv::load_drug_filter(const std::string& filename, std::set<filter::DrugFilter>& filter)
{
        std::vector<std::vector<std::string>> rows;
        load_rows(filename, rows);

        for (std::vector<std::string> parts: rows) {
                const std::string& category = parts[0];
                const std::string& b = parts[1];
                if (parts.size() == 0)
                        continue;
                filter.insert(filter::DrugFilter(category, b == "0"));
        }
}
