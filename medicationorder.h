#ifndef MEDICATION_ORDER_H
#define MEDICATION_ORDER_H


#include <string>
#include <ostream>
#include "timeddata.h"

class MedicationOrder: public TimedData
{
        friend std::ostream& operator<<(std::ostream& os, const MedicationOrder& order);
public:
        MedicationOrder(int patiend_id,
                        const std::string& med_desc,
                        const std::string& med_categ,
                        int date_offset);
        MedicationOrder(int patiend_id);
        MedicationOrder(const MedicationOrder& other);

        int                time_offset() const;
        int                oid() const;
        int                pid() const;
        const std::string&      category() const;
        const std::string&      desc() const;

        bool            operator <(const MedicationOrder& rhs) const;
        bool            operator >(const MedicationOrder& rhs) const;
private:
        int        m_order_id;
        int        m_patient_id;
        std::string     m_med_categ;
        std::string     m_med_desc;
        int        m_date_offset;
};


inline std::ostream& operator <<(std::ostream& os, const MedicationOrder& order)
{
        os << "MedicationOrder = [" << order.m_order_id << ","
           << order.m_patient_id << ","
           << order.m_med_categ << ","
           << order.m_med_desc  << ","
           << order.m_date_offset << "]";
        return os;
}


#endif  // MEDICATION_ORDER_H
