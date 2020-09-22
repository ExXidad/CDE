//
// Created by mi on 22.09.2020.
//

#ifndef CDE_SOLVER_H
#define CDE_SOLVER_H

#include <vector>
#include <iostream>

#include "Domain.h"
#include "BoundingRect.h"

class Solver
{
private:
    std::vector<std::vector<double>> u;
    int m, n;

    double c, h, t, dt, tMax;

public:
    Solver(Domain &domain, BoundingRect &boundingRect, double(&icf)(const double &, const double &),
           const double &h);

};


#endif //CDE_SOLVER_H
