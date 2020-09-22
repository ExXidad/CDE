#include <iostream>
#include <cmath>
#include "Solver.h"
#include "BoundingRect.h"
#include "Domain.h"

//df - domain function
bool df1(const double &x, const double &y)
{
    return (0 <= x && x <= 10) && (0 <= y && y <= 20);
}

bool df2(const double &x, const double &y)
{
    return (x-5)*(x-5)+(y-5)*(y-5) <= 25;
    }

//icf - initial condition function
double icf(const double &x, const double &y)
{
    return exp(-(x - 5) * (x - 5) - (y - 5) * (y - 5));
}

int main()
{
    double h = 0.1;

    Domain domain = Domain();
    domain.addDomainFunction(df2);

    BoundingRect boundingRect(-1, 11, -1, 11);

    Solver solver = Solver(domain, boundingRect, icf, h);

    solver.solve(LV, 1, 20, 50);


    return 0;
}
