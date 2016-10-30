#include "medicationorder.h"


static int uuid = 0;

MedicationOrder::MedicationOrder(int patiend_id,
                                 const std::string& med_categ,
                                 const std::string& med_desc,
                                 int date_offset)
{
        m_order_id = uuid ++;
        m_patient_id = patiend_id;
        m_med_categ = med_categ;
        m_med_desc = med_desc;
        m_date_offset = date_offset;
}

MedicationOrder::MedicationOrder(int patiend_id)
{
        m_patient_id = patiend_id;
}

MedicationOrder::MedicationOrder(const MedicationOrder& other)
{
        m_order_id = other.m_order_id;
        m_patient_id = other.m_patient_id;
        m_med_categ = other.m_med_categ;
        m_med_desc = other.m_med_desc;
        m_date_offset = other.m_date_offset;
}

int MedicationOrder::time_offset() const
{
        return m_date_offset;
}

int MedicationOrder::pid() const
{
        return m_patient_id;
}

int MedicationOrder::oid() const
{
        return m_order_id;
}

const std::string& MedicationOrder::category() const
{
        return m_med_categ;
}

const std::string& MedicationOrder::desc() const
{
        return m_med_desc;
}

bool MedicationOrder:: operator <(const MedicationOrder& rhs) const
{
        return m_patient_id < rhs.m_patient_id;
}

bool MedicationOrder:: operator >(const MedicationOrder& rhs) const
{
        return m_patient_id > rhs.m_patient_id;
}
