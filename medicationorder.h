#ifndef MEDICATION_ORDER_H
#define MEDICATION_ORDER_H


#include <string>
#include <ostream>

namespace csv
{

class MedicationOrder
{
        friend std::ostream& operator<<(std::ostream& os, const MedicationOrder& order);
public:
        MedicationOrder(int pid,
                        bool diabetes,
                        bool heart_failure,
                        const std::string& visit_type,
                        unsigned order_year,
                        int start_date,
                        const std::string& order_type,
                        const std::string& order_status,
                        const std::string& discontinue_reason,
                        const std::string& med_category,
                        const std::string& med_name,
                        const std::string& order_name,
                        float dose,
                        const std::string& uom,
                        unsigned quantity,
                        unsigned duration,
                        unsigned num_refills,
                        const std::string& route,
                        const std::string& presc_type,
                        const std::string& frequency,
                        bool is_prn,
                        const std::string& instructions);
        MedicationOrder(int pid);
        MedicationOrder();

        int		date() const;
        int		end_date() const;

        bool            operator <(const MedicationOrder& rhs) const;

        int             oid;
        int             pid;
        bool            diabetes;
        bool            heart_failure;
        std::string     visit_type;
        unsigned 	order_year;
        int             start_date;
        std::string     order_type;
        std::string     order_status;
        std::string     discontinue_reason;
        std::string     med_category;
        std::string     med_name;
        std::string     order_name;
        float           dose;
        std::string     uom;
        unsigned	quantity;
        unsigned 	duration;
        unsigned	num_refills;
        std::string     route;
        std::string     presc_type;
        std::string     frequency;
        bool            is_prn;
        std::string     instructions;
        int		med_class;
};

inline std::ostream& operator <<(std::ostream& os, const MedicationOrder& order)
{
        os << "MedicationOrder = ["
           << order.oid << ","
           << order.pid << ","
           << order.diabetes << ","
           << order.heart_failure << ","
           << order.visit_type << ","
           << order.order_year << ","
           << order.start_date << ","
           << order.order_type << ","
           << order.order_status << ","
           << order.discontinue_reason << ","
           << order.med_category << ","
           << order.med_name << ","
           << order.order_name << ","
           << order.dose << ","
           << order.uom << ","
           << order.quantity << ","
           << order.duration << ","
           << order.num_refills << ","
           << order.route << ","
           << order.frequency << ","
           << order.is_prn << ","
           << order.instructions << "]";
        return os;
}

}

#endif  // MEDICATION_ORDER_H
