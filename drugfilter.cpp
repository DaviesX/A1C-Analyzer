#include "drugfilter.h"


filter::DrugFilter::DrugFilter(const std::string& category):
        category(category), is_filtered(false)
{
}

filter::DrugFilter::DrugFilter(const std::string& category, bool is_filtered):
        category(category), is_filtered(is_filtered)
{
}

bool filter::DrugFilter::operator<(const DrugFilter& rhs) const
{
        return category < rhs.category;
}
