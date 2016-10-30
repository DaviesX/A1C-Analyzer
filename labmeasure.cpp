#include "labmeasure.h"



LabMeasure::LabMeasure(int patient_id,
                       int date_offset,
                       const std::string& lab_desc,
                       float a1c)
{
        m_patient_id = patient_id;
        m_date_offset = date_offset;
        m_lab_desc = lab_desc;
        m_a1c = a1c;
}

LabMeasure::LabMeasure(int patient_id)
{
        m_patient_id = patient_id;
}

LabMeasure::LabMeasure(const LabMeasure& other)
{
        m_patient_id = other.m_patient_id;
        m_date_offset = other.m_date_offset;
        m_lab_desc = other.m_lab_desc;
        m_a1c = other.m_a1c;
}

int LabMeasure::pid() const
{
        return m_patient_id;
}

int LabMeasure::time_offset() const
{
        return m_date_offset;
}

const std::string& LabMeasure::desc() const
{
        return m_lab_desc;
}

float LabMeasure::a1c() const
{
        return m_a1c;
}

bool LabMeasure:: operator <(const LabMeasure& rhs) const
{
        return m_patient_id < rhs.m_patient_id;
}

bool LabMeasure:: operator >(const LabMeasure& rhs) const
{
        return m_patient_id > rhs.m_patient_id;
}
