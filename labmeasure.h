#ifndef LAB_MEASURE_H
#define LAB_MEASURE_H


#include <string>
#include <ostream>
#include <cmath>

namespace csv
{


class LabMeasure
{
        friend std::ostream& operator<<(std::ostream& os, const LabMeasure& measure);
public:
        LabMeasure(int pid,
                   unsigned test_date,
                   const std::string& observation,
                   float a1c);
        LabMeasure(int pid);

        unsigned	date() const;

        int             pid = -1;
        unsigned 	test_date = 0;
        std::string     observation = "";
        float           a1c = NAN;
};

inline std::ostream& operator <<(std::ostream& os, const LabMeasure& measure)
{
        os << "LabMeasure = ["
           << measure.pid << ","
           << measure.test_date << ","
           << measure.observation << ","
           << measure.a1c << "]";
        return os;
}

}


#endif  // LAB_MEASURE_H
