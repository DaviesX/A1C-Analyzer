#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "medicationorder.h"
#include "labmeasure.h"
#include "csv.h"



static void split(const std::string &s, char delim, std::vector<std::string> &elems)
{
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
                elems.push_back(item);
        }
}


static std::vector<std::string> split(const std::string &s, char delim)
{
        std::vector<std::string> elems;
        ::split(s, delim, elems);
        return elems;
}

void CSV::load_rows(const std::string& filename, std::vector<std::vector<std::string>>& rows) const
{
        std::ifstream s(filename);
        if (!s.is_open())
                throw "Failed to open " + filename;

        std::string line;
        while (!s.eof()) {
                std::getline(s, line);
                rows.push_back(::split(line.substr(0, line.find_last_of("\n\r")), COL_DELIM));
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

void CSV::load_medication_order(const std::string& filename, std::vector<MedicationOrder>& orders) const
{
        std::vector<std::vector<std::string>> rows;
        load_rows(filename, rows);

        bool first_row = true;
        std::map<std::string, unsigned> col_map;
        for (std::vector<std::string> parts: rows) {
                if (first_row) {
                        std::vector<std::string>& ddl = parts;
                        if (!::set_column_mapping("OrderDate_Days", ddl, col_map))
                                throw "Column OrderDate_Days doesn't exist";
                        if (!::set_column_mapping("Id", ddl, col_map))
                                throw "Column Id doesn't exist";
                        if (!::set_column_mapping("TherapeuticCategory", ddl, col_map))
                                throw "Column TherapeuticCategory doesn't exist";
                        if (!::set_column_mapping("GenericItemName", ddl, col_map))
                                throw "Column GenericItemName doesn't exist";
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

void CSV::load_lab_measure(const std::string& filename, std::vector<LabMeasure>& measures) const
{
        std::vector<std::vector<std::string>> rows;
        load_rows(filename, rows);

        bool first_row = true;
        std::map<std::string, unsigned> col_map;
        for (std::vector<std::string> parts: rows) {
                if (first_row) {
                        std::vector<std::string>& ddl = parts;
                        if (!::set_column_mapping("Id", ddl, col_map))
                                throw "Column Id doesn't exist";
                        if (!::set_column_mapping("Result", ddl, col_map))
                                throw "Column Result doesn't exist";
                        if (!::set_column_mapping("Observation", ddl, col_map))
                                throw "Column Observation doesn't exist";
                        if (!::set_column_mapping("Result_Days", ddl, col_map))
                                throw "Column Result_Days doesn't exist";
                        first_row = false;
                } else {
                        if (parts.size() > 0) {
                                const std::string& id = parts[col_map["Id"]];
                                const std::string& date_offset = parts[col_map["Result_Days"]];
                                const std::string& desc = parts[col_map["Observation"]];
                                const std::string& result = parts[col_map["Result"]];
                                measures.push_back(LabMeasure(std::atoi(id.c_str()), std::atoi(date_offset.c_str()), desc, std::atof(result.c_str())));
                        }
                }
        }
}
