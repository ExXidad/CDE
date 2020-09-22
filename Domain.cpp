//
// Created by mi on 22.09.2020.
//

#include "Domain.h"

void Domain::addDomainFunction(bool (&domainFunction)(const double &, const double &))
{
    domainFunctions.emplace_back(&domainFunction);
}

bool Domain::belongs(const double &x, const double &y)
{
    for (auto &domainFunction : domainFunctions) {
        if (!domainFunction(x,y)) return false;
    }
    return true;
}

Domain::Domain()
{

}
