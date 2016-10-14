#ifndef DELTAANALYSIS_H
#define DELTAANALYSIS_H

#include <string>

class DeltaAnalysis
{
public:
        DeltaAnalysis(unsigned oid,
                      unsigned patient_id,
                      unsigned time_offset,
                      const std::string& category,
                      const std::string& desc,
                      float a1c);

        unsigned                oid() const;
        unsigned                patient_id() const;
        unsigned                time_offset() const;
        const std::string&      category() const;
        const std::string&      desc() const;
        float                   a1c() const;
private:
        unsigned        m_oid;
        unsigned        m_patient_id;
        unsigned        m_time_offset;
        std::string     m_categ;
        std::string     m_desc;
        float           m_a1c;
};

#endif // DELTAANALYSIS_H
