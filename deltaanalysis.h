#ifndef DELTAANALYSIS_H
#define DELTAANALYSIS_H

#include <string>
#include <ostream>

class DeltaAnalysis
{
        friend std::ostream& operator << (std::ostream& os, const DeltaAnalysis& delta);
public:
        DeltaAnalysis(unsigned oid,
                      unsigned patient_id,
                      unsigned time_offset,
                      const std::string& category,
                      const std::string& desc,
                      const std::string& lab_desc,
                      float a1c);

        DeltaAnalysis(const DeltaAnalysis& raw,
                      unsigned delta,
                      bool triggered);

        unsigned                delta() const;
        bool                    triggered() const;

        unsigned                oid() const;
        unsigned                patient_id() const;
        unsigned                time_offset() const;
        const std::string&      category() const;
        const std::string&      desc() const;
        const std::string&      lab_desc() const;
        float                   a1c() const;
private:
        unsigned        m_delta         = 0;
        bool            m_triggered     = false;
        float           m_a1c;

        unsigned        m_oid;
        unsigned        m_patient_id;
        unsigned        m_time_offset;

        std::string     m_categ;
        std::string     m_lab_desc;
        std::string     m_desc;
};

inline std::ostream& operator << (std::ostream& os, const DeltaAnalysis& delta)
{
        os << "DeltaAnalysis = ["
           << delta.m_oid << ","
           << delta.m_patient_id << ","
           << delta.m_time_offset << ","
           << delta.m_delta << ","
           << delta.m_triggered << ","
           << delta.m_categ << ","
           << delta.m_desc << ","
           << delta.m_lab_desc << ","
           << delta.m_a1c << "]";
        return os;
}


#endif // DELTAANALYSIS_H
