#include "deltaanalysis.h"


DeltaAnalysis::DeltaAnalysis(unsigned oid,
                             unsigned patient_id,
                             unsigned time_offset,
                             const std::string& category,
                             const std::string& desc,
                             float a1c)
{
        m_oid = oid;
        m_patient_id = patient_id;
        m_time_offset = time_offset;
        m_categ = category;
        m_desc = desc;
        m_a1c = a1c;
}

unsigned DeltaAnalysis::oid() const
{
        return m_oid;
}

unsigned DeltaAnalysis::patient_id() const
{
        return m_patient_id;
}

unsigned DeltaAnalysis::time_offset() const
{
        return m_time_offset;
}

const std::string& DeltaAnalysis::category() const
{
        return m_categ;
}

const std::string& DeltaAnalysis::desc() const
{
        return m_desc;
}

float DeltaAnalysis::a1c() const
{
        return m_a1c;
}
