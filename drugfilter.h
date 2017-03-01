#ifndef DRUGFILTER_H
#define DRUGFILTER_H

#include <string>

namespace filter
{

class DrugFilter
{
public:
        DrugFilter(const std::string& category);
        DrugFilter(const std::string& category, bool is_filtered);

        bool operator<(const DrugFilter& rhs) const;

        const std::string       category;
        const bool              is_filtered;
};

}


#endif // DRUGFILTER_H
