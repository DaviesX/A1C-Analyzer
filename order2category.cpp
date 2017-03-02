#include "order2category.h"


csv::Order2Category::Order2Category(const std::string& order_name, int med_code):
        order_name(order_name), med_code(med_code)
{
}

csv::Order2Category::Order2Category(const std::string& order_name):
        order_name(order_name)
{
}


bool
csv::Order2Category::operator<(const Order2Category& rhs) const
{
        return order_name < rhs.order_name;
}
