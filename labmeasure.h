#ifndef LAB_MEASURE_H
#define LAB_MEASURE_H


#include <string>
#include <ostream>
#include "timeddata.h"

class LabMeasure: public TimedData
{
        friend std::ostream& operator<<(std::ostream& os, const LabMeasure& measure);
public:
        LabMeasure(unsigned patient_id,
                   unsigned date_offset,
                   const std::string& lab_desc,
                   float a1c);
        LabMeasure(unsigned patient_id);
        LabMeasure(const LabMeasure& other);

        unsigned                pid() const;
        unsigned                time_offset() const;
        const std::string&      desc() const;
        float                   a1c() const;
        bool            operator <(const LabMeasure& rhs) const;
        bool            operator >(const LabMeasure& rhs) const;
private:
        unsigned        m_patient_id;
        unsigned        m_date_offset;
        std::string     m_lab_desc;
        float           m_a1c;
};

inline std::ostream& operator <<(std::ostream& os, const LabMeasure& measure)
{
        os << "LabMeasure = ["
           << measure.m_patient_id << ","
           << measure.m_date_offset << ","
           << measure.m_lab_desc << ","
           << measure.m_a1c << "]";
        return os;
}


#endif  // LAB_MEASURE_H
