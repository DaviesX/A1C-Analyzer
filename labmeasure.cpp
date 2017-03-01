#include "labmeasure.h"



csv::LabMeasure::LabMeasure(int pid,
                            unsigned test_date,
                            const std::string& observation,
                            float a1c):
        pid(pid), test_date(test_date), observation(observation), a1c(a1c)
{
}

csv::LabMeasure::LabMeasure(int pid):
        pid(pid)
{
}

unsigned csv::LabMeasure::date() const
{
        return test_date;
}
