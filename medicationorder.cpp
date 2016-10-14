#include "medicationorder.h"


static unsigned uuid = 0;

MedicationOrder::MedicationOrder(unsigned patiend_id,
                                 const std::string& med_categ,
                                 const std::string& med_desc, 
                                 unsigned date_offset)
{
        m_order_id = uuid ++;
        m_patient_id = patiend_id;
        m_med_categ = med_categ;
        m_med_desc = med_desc;
        m_date_offset = date_offset;
}

MedicationOrder::MedicationOrder(unsigned patiend_id)
{
        m_patient_id = patiend_id;
}

unsigned MedicationOrder::pid() const
{
        return m_patient_id;
}

bool MedicationOrder::lt(const MedicationOrder& rhs) const
{
        return m_patient_id < rhs.m_patient_id;
}

bool MedicationOrder::gt(const MedicationOrder& rhs) const
{
        return m_patient_id > rhs.m_patient_id;
}
