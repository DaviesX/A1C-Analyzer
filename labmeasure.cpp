#include "labmeasure.h"



csv::LabMeasure::LabMeasure(int pid,
                            int test_date,
                            const std::string& observation,
                            float a1c):
        pid(pid), test_date(test_date), observation(observation), a1c(a1c)
{
}

csv::LabMeasure::LabMeasure(int pid):
        pid(pid)
{
}

int
csv::LabMeasure::date() const
{
        return test_date;
}
