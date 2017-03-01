#include "labfilter.h"

filter::LabFilter::LabFilter(const std::string& keep):
        keep(keep)
{
}

bool filter::LabFilter::operator<(const LabFilter& rhs) const
{
        return keep < rhs.keep;
}
