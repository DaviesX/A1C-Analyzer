#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "medicationorder.h"
#include "labmeasure.h"
#include "csvloader.h"


CSV::CSV()
{
}

void CSV::load_rows(const std::string& filename, std::vector<std::vector<std::string>>& rows)
{
        std::ifstream s(filename);
        if (!s.is_open())
                throw "Failed to open " + filename;

        while (true) {
                std::string line = "";
                s >> line;
                rows.push(s);
        }
}

static bool set_column_mapping(const std::string& key, const std::vector<std::string>& ddl, std::map& col_map)
{
        for (int i = 0; i < ddl.size(); i ++) {
                if (key == ddl[i]) {
                        col_map[key] = i;
                        return true;
                }
        }
        return false;
}

std::vector<MedicationOrder> CSV::load_medication_order(const std::string& filename)
{
        std::vector<std::vector<std::string>> rows;
        load_rows(filename, rows);

        bool first_row = true;
        std::map col_map;
        for (std::vector<std::string> parts: rows) {
                if (i == 0) {
                        std::vector<std::string> ddl;
                        if (!::set_column_mapping("A1C", ddl, col_map))
                                throw "Column A1C doesn't exist";
                        if (!::set_column_mapping("A1C", ddl, col_map))
                                throw "Column xxx doesn't exist";
                        first_row = true;
                        continue;
                }
        }
        return orders;
}

std::vector<LabMeasure> CSV::load_lab_measure(const std::string& filename)
{
        return measures;
}
