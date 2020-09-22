//
// Created by mi on 22.09.2020.
//

#ifndef CDE_DOMAIN_H
#define CDE_DOMAIN_H

#include <vector>

class Domain
{
private:
    std::vector<bool(*)(const double &,const double &)> domainFunctions;

public:
    Domain();

    void addDomainFunction(bool(&domainFunction)(const double &,const double &));

    bool contains(const double &x, const double &y);
};


#endif //CDE_DOMAIN_H
