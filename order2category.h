#ifndef ORDER2CATEGORY_H
#define ORDER2CATEGORY_H

#include <string>

namespace csv
{

class Order2Category
{
public:
        Order2Category(const std::string& order_name, int med_code);
        Order2Category(const std::string& order_name);

        bool operator<(const Order2Category& rhs) const;

        std::string		order_name;
        int			med_code;
        mutable std::string	med_categ;
};

}

#endif // ORDER2CATEGORY_H
