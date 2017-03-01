#ifndef LABFILTER_H
#define LABFILTER_H

#include <string>

namespace filter
{

class LabFilter
{
public:
        LabFilter(const std::string& keep);
        bool operator<(const LabFilter& rhs) const;
public:
        std::string keep;
};

}


#endif // LABFILTER_H
