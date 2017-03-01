#ifndef STATISTICS_H
#define STATISTICS_H

#include <map>
#include <ostream>

namespace analysis
{

typedef std::map<int, float> int_dist_t;
typedef std::pair<int, float> int_dist_ent_t;

void		int_dist_add_sample(int_dist_t& dist, const int_dist_ent_t& ent);
void 		int_dist_normalize(int_dist_t& dist);
void		int_dist_msm(const int_dist_t& dist, float& miu, float& sigma, int& median);
std::ostream& 	operator<<(std::ostream& os, const int_dist_t& dist);


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
