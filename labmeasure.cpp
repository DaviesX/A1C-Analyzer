#include "labmeasure.h"



LabMeasure::LabMeasure(unsigned patient_id,
                       unsigned date_offset,
                       const std::string& lab_desc,
                       float a1c)
{
        m_patient_id = patient_id;
        m_date_offset = date_offset;
        m_lab_desc = lab_desc;
        m_a1c = a1c;
}

unsigned LabMeasure::pid() const
{
        return m_patient_id;
}

bool LabMeasure::lt(const LabMeasure& rhs) const
{
        return m_patient_id < rhs.m_patient_id;
}

bool LabMeasure::gt(const LabMeasure& rhs) const
{
        return m_patient_id > rhs.m_patient_id;
}
