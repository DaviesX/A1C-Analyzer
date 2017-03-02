#ifndef MEDCATEGORY_H
#define MEDCATEGORY_H

#include <string>

namespace csv
{

class MedCategory
{
public:
        MedCategory(const std::string& med_categ, int med_code, int med_class);
        MedCategory(const std::string& med_categ);

        bool operator<(const MedCategory& rhs) const;

        std::string	get_category() const;
        int		get_code() const;
        int		get_class() const;

private:
        std::string	med_categ;
        int		med_code;
        int		med_class;
};

}


#endif // MEDCATEGORY_H
