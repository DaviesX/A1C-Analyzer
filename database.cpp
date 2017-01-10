#include "database.h"

Database::Database()
{

}

void Database::reset()
{
        orders.clear();
        measures.clear();
        filter.clear();

        joined.clear();
        delta.clear();
        lab_patients.clear();
}
