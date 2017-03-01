#include "database.h"

dataset::Database::Database()
{

}

void
dataset::Database::reset()
{
        orders.clear();
        measures.clear();
        filter.clear();
        lab_filter.clear();

        records.clear();
}
