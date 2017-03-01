#ifndef STATISTICS_H
#define STATISTICS_H

#include <map>
#include <ostream>

namespace analysis
{

typedef std::map<unsigned, unsigned> int_dist_t;
typedef std::pair<unsigned, unsigned> int_dist_ent_t;

class Statistics
{
        friend std::ostream& operator<<(std::ostream& os, const Statistics& s);
public:
        Statistics();

        float		p_recovered = 0;
        int_dist_t	dist_r_len;
};

std::ostream& operator<<(std::ostream& os, const Statistics& s);

}

#endif // STATISTICS_H
