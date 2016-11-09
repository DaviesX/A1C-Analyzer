#ifndef DRUGFILTER_H
#define DRUGFILTER_H

#include <string>

class DrugFilter
{
public:
        DrugFilter(const std::string& category, bool is_filtered);

        const std::string       category;
        const bool              is_filtered;
};

#endif // DRUGFILTER_H
