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
#include "deltaanalysis.h"
#include "csv.h"


namespace csv
{

static void split(const std::string& s, char delim, std::vector<std::string>& result)
{
        // Split according to the delimiter but skip quotes.
        int last = 0;
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

static void load_rows(const std::string& filename, std::vector<std::vector<std::string>>& rows)
{
        std::ifstream s(filename);
        if (!s.is_open())
                throw "Failed to open " + filename;

        std::string line;
        while (!s.eof()) {
                std::getline(s, line);
                std::vector<std::string> cols;
                csv::split(line.substr(0, line.find_last_of("\n\r")), COL_DELIM, cols);
                rows.push_back(cols);
        }
        s.close();
}

static bool set_column_mapping(const std::string& key, const std::vector<std::string>& ddl, std::map<std::string, unsigned>& col_map)
{
        for (unsigned i = 0; i < ddl.size(); i ++) {
                if (ddl[i] == key) {
                        col_map[key] = i;
                        return true;
                }
        }
        return false;
}

void load_medication_order(const std::string& filename, std::vector<MedicationOrder>& orders)
{
        std::vector<std::vector<std::string>> rows;
        csv::load_rows(filename, rows);

        bool first_row = true;
        std::map<std::string, unsigned> col_map;
        for (std::vector<std::string> parts: rows) {
                if (first_row) {
                        std::vector<std::string>& ddl = parts;
                        if (!csv::set_column_mapping("OrderDate_Days", ddl, col_map))
                                throw filename + " is not a medication order file: Column OrderDate_Days doesn't exist";
                        if (!csv::set_column_mapping("Id", ddl, col_map))
                                throw filename + " is not a medication order file: Column Id doesn't exist";
                        if (!csv::set_column_mapping("TherapeuticCategory", ddl, col_map))
                                throw filename + " is not a medication order file: Column TherapeuticCategory doesn't exist";
                        if (!csv::set_column_mapping("GenericItemName", ddl, col_map))
                                throw filename + " is not a medication order file: Column GenericItemName doesn't exist";
                        first_row = false;
                } else {
                        if (parts.size() > 0) {
                                const std::string& id = parts[col_map.at("Id")];
                                const std::string& date_offset = parts[col_map["OrderDate_Days"]];
                                const std::string& categ = parts[col_map["TherapeuticCategory"]];
                                const std::string& desc = parts[col_map["GenericItemName"]];
                                orders.push_back(MedicationOrder(std::atoi(id.c_str()), desc, categ, std::atoi(date_offset.c_str())));
                        }
                }
        }
}

void load_lab_measure(const std::string& filename, std::vector<LabMeasure>& measures)
{
        std::vector<std::vector<std::string>> rows;
        csv::load_rows(filename, rows);

        bool first_row = true;
        std::map<std::string, unsigned> col_map;
        unsigned min = 0;
        for (std::vector<std::string> parts: rows) {
                if (first_row) {
                        std::vector<std::string>& ddl = parts;
                        if (!csv::set_column_mapping("Id", ddl, col_map))
                                throw filename + " is not a lab test file: Column Id doesn't exist";
                        if (!csv::set_column_mapping("Result", ddl, col_map))
                                throw filename + " is not a lab test file: Column Result doesn't exist";
                        if (!csv::set_column_mapping("Observation", ddl, col_map))
                                throw filename + " is not a lab test file: Column Observation doesn't exist";
                        if (!csv::set_column_mapping("Result_Days", ddl, col_map))
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
                                measures.push_back(LabMeasure(std::atoi(id.c_str()), std::atoi(date_offset.c_str()), desc, std::atof(result.c_str())));
                        }
                }
        }
}

static std::string purify(const std::string& s)
{
        std::string r;
        for (unsigned i = 0; i < s.length(); i ++) {
                r += s.at(i) == ',' ? '*' : s.at(i);
        }
        return r;
}

void write_delta_analysis(const std::string& filename, std::vector<DeltaAnalysis>& analysis)
{
        std::ofstream file(filename);
        if (!file.is_open())
                throw "Failed to write to " + filename;
        file << "Id, Order ID, Order Category, Order Description, Lab Description, Delta, A1C, Triggered" << std::endl;
        for (DeltaAnalysis delta: analysis) {
                file << delta.patient_id() << ","
                     << delta.oid() << ","
                     << csv::purify(delta.category()) << ","
                     << csv::purify(delta.desc()) << ","
                     << csv::purify(delta.lab_desc()) << ","
                     << delta.delta() << ","
                     << delta.a1c() << ","
                     << (delta.triggered() ? "1" : "0") << std::endl;
        }
        file.close();
}

}
