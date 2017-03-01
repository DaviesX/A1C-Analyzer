#include "statistics.h"


analysis::Statistics::Statistics()
{
}

std::ostream& analysis::operator<<(std::ostream& os, const Statistics& s)
{
        os << "Statistics = [p(patient=recovered)=" << s.p_recovered << "]";
        return os;
}
