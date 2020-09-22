//
// Created by mi on 22.09.2020.
//

#ifndef CDE_SOLVER_H
#define CDE_SOLVER_H

#include <vector>
#include <iostream>
#include <fstream>

#include "Domain.h"
#include "BoundingRect.h"


enum solveMethods
{
    LV, CIR
};

class Solver
{
private:
    std::vector<std::vector<std::vector<double>>> xyU;
    std::vector<std::vector<bool>> domainPointQ;

    int m, n;

    double c, h,  dt, tMax;

    int stepsElapsed = 0;
    double t = 0;

private:
    void save();

public:
    Solver(Domain &domain, BoundingRect &boundingRect, double(&icf)(const double &, const double &), const double &h);

    void solve(solveMethods method, const double &c, const double &tMax, const int &saveStep);
};


#endif //CDE_SOLVER_H
