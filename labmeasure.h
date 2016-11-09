#ifndef LAB_MEASURE_H
#define LAB_MEASURE_H


#include <string>
#include <ostream>
#include <cmath>
#include "timeddata.h"

class LabMeasure: public TimedData
{
        friend std::ostream& operator<<(std::ostream& os, const LabMeasure& measure);
public:
        LabMeasure(int pid,
                   int test_date,
                   const std::string& observation,
                   float a1c);
        LabMeasure(int pid);

        bool            operator <(const LabMeasure& rhs) const;
        bool            operator >(const LabMeasure& rhs) const;
        int             date() const;

        int             pid = -1;
        int             test_date = 0;
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


#endif  // LAB_MEASURE_H
