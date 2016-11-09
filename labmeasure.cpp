#include "labmeasure.h"



LabMeasure::LabMeasure(int pid,
                       int test_date,
                       const std::string& observation,
                       float a1c):
        pid(pid), test_date(test_date), observation(observation), a1c(a1c)
{
}

LabMeasure::LabMeasure(int pid):
        pid(pid)
{
}

int LabMeasure::date() const
{
        return test_date;
}

bool LabMeasure::operator <(const LabMeasure& rhs) const
{
        return pid < rhs.pid;
}

bool LabMeasure::operator >(const LabMeasure& rhs) const
{
        return pid > rhs.pid;
}
