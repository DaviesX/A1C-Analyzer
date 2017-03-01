#include <limits>
#include <cmath>
#include "statistics.h"


analysis::Statistics::Statistics()
{
}

std::ostream& analysis::operator<<(std::ostream& os, const Statistics& s)
{
        float m_r_len, s_r_len;
        int median_r_len;
        int_dist_msm(s.dist_r_len, m_r_len, s_r_len, median_r_len);

        os << "Statistics = [p(patient=recovered)=" << s.p_recovered;
        os << ", recovery_length: " << std::endl;
        os << s.dist_r_len << std::endl;
        os << "miu: " << m_r_len << ", sigma: " << s_r_len << ", median: " << median_r_len;
        os << "]";
        return os;
}


void
analysis::int_dist_add_sample(int_dist_t& dist, const int_dist_ent_t& ent)
{
        int_dist_t::iterator it = dist.find(ent.first);
        if (it != dist.end())	it->second += ent.second;
        else			dist.insert(ent);
}

void
analysis::int_dist_normalize(int_dist_t& dist)
{
        float sum = 0.0f;
        for (int_dist_ent_t ent: dist)
                sum += ent.second;

        for (int_dist_t::iterator it = dist.begin(); it != dist.end(); ++ it)
                it->second /= sum;
}

void
analysis::int_dist_msm(const int_dist_t& dist, float& miu, float& sigma, int& median)
{
        float sum = 0.0f;
        miu = 0;
        sigma = 0;
        for (int_dist_ent_t ent: dist) {
                miu += ent.second*ent.first;
                sigma += ent.second*ent.first*ent.first;
                sum += ent.second;
                if (sum <= 0.5f)
                        median = ent.first;
        }
        // Population variance.
        sigma = static_cast<float>(sqrt(sigma - miu*miu));
}

static void
draw_proportion(std::ostream& os, int x, float y, float scale)
{
        os << x << ":";
        for (unsigned i = 0; i < scale*y; i ++) {
                os << "+";
        }
        os << " " << y << std::endl;
}

std::ostream&
analysis::operator<<(std::ostream& os, const int_dist_t& dist)
{
        float max = 0.0f;
        std::pair<int, int> range(std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
        for (int_dist_ent_t ent: dist) {
                max = std::max(max, ent.second);
                range.first = std::min(range.first, ent.first);
                range.second = std::max(range.second, ent.first);
        }

        unsigned bins = 30;
        unsigned intv = static_cast<unsigned>(std::ceil(static_cast<double>(range.second - range.first)/bins));
        float scale = max != 0.0 ? 100.0f/(max*intv) : 0;

        for (int i = range.first; i <= range.second; i += intv) {
                float sum = 0;
                for (int j = i; j < i + static_cast<int>(intv); j ++) {
                        int_dist_t::const_iterator it = dist.find(j);
                        sum += it != dist.end() ? it->second : 0.0f;
                }
                draw_proportion(os, i, sum, scale);
        }
        return os;
}
