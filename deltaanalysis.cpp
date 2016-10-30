#include "deltaanalysis.h"


DeltaAnalysis::DeltaAnalysis(int oid,
                             int patient_id,
                             int time_offset,
                             const std::string& category,
                             const std::string& desc,
                             const std::string& lab_desc,
                             float a1c)
{
        m_oid = oid;
        m_patient_id = patient_id;
        m_time_offset = time_offset;
        m_categ = category;
        m_desc = desc;
        m_lab_desc = lab_desc;
        m_a1c = a1c;
}

DeltaAnalysis::DeltaAnalysis(const DeltaAnalysis& raw,
                             int delta,
                             bool triggered)
{
        m_oid = raw.m_oid;
        m_patient_id = raw.m_patient_id;
        m_time_offset = raw.m_time_offset;
        m_categ = raw.m_categ;
        m_desc = raw.m_desc;
        m_lab_desc = raw.m_lab_desc;
        m_a1c = raw.m_a1c;

        m_triggered = triggered;
        m_delta = delta;
}

int DeltaAnalysis::delta() const
{
        return m_delta;
}

bool DeltaAnalysis::triggered() const
{
        return m_triggered;
}

int DeltaAnalysis::oid() const
{
        return m_oid;
}

int DeltaAnalysis::patient_id() const
{
        return m_patient_id;
}

int DeltaAnalysis::time_offset() const
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

const std::string& DeltaAnalysis::lab_desc() const
{
        return m_lab_desc;
}

float DeltaAnalysis::a1c() const
{
        return m_a1c;
}
