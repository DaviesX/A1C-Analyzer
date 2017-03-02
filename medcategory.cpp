#include "medcategory.h"


csv::MedCategory::MedCategory(const std::string& med_categ, int med_code, int med_class):
        med_categ(med_categ), med_code(med_code), med_class(med_class)
{
}

csv::MedCategory::MedCategory(const std::string& med_categ):
        med_categ(med_categ)
{
}

bool
csv::MedCategory::operator<(const MedCategory& rhs) const
{
        return med_categ < rhs.med_categ;
}

std::string
csv::MedCategory::get_category() const
{
        return med_categ;
}

int
csv::MedCategory::get_code() const
{
        return med_code;
}

int
csv::MedCategory::get_class() const
{
        return med_class;
}
