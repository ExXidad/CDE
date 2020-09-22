//
// Created by mi on 22.09.2020.
//

#include "Solver.h"

Solver::Solver(Domain &domain, BoundingRect &boundingRect, double(&icf)(const double &, const double &),
               const double &h)
{
    this->h = h;
    m = boundingRect.getYSize() / h;
    n = boundingRect.getXSize() / h;

    std::cout << "Solver initialized. " << m << "x" << n << std::endl;

    xyU.resize(m, std::vector<std::vector<double>>(n, std::vector<double>(3, 0)));
    domainPointQ.resize(m, std::vector<bool>(n, false));

    double x0 = boundingRect.getSize()[0][0];
    double y0 = boundingRect.getSize()[1][0];

    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            double newX = x0 + i * h;
            double newY = y0 + j * h;

            if (domain.contains(newX, newY)) {
                xyU[j][i] = {newX, newY, icf(newX, newY)};
                domainPointQ[j][i] = true;
            } else {
                xyU[j][i] = {newX, newY, 0};
                domainPointQ[j][i] = false;
            }
        }
    }

}

void Solver::solve(solveMethods method, const double &c, const double &tMax, const int &saveStep)
{
    this->c = c;
    this->tMax = tMax;
    dt = 0.1 * h / c;
    int stepsEstimated = int(tMax / dt) + 1;

    std::cout << "Solve started. t = (0.." << tMax << "), dt = " << dt << std::endl;
    std::cout << "Estimated number of steps: " << stepsEstimated << std::endl;

    std::vector<std::vector<std::vector<double>>> xyU_prev;
    while (stepsElapsed <= stepsEstimated) {
        xyU_prev = xyU;
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                double u = xyU_prev[j][i][2];

                double uNextXNeighbour, uPrevXNeighbour;
                double uNextYNeighbour, uPrevYNeighbour;

                if (i + 1 > n - 1 || !domainPointQ[j][i + 1])
                    uNextXNeighbour = 0;
                else
                    uNextXNeighbour = xyU_prev[j][i + 1][2];

                if (i - 1 < 0 || !domainPointQ[j][i - 1])
                    uPrevXNeighbour = 0;
                else
                    uPrevXNeighbour = xyU_prev[j][i - 1][2];

                if (j + 1 > m - 1 || !domainPointQ[j + 1][i])
                    uNextYNeighbour = 0;
                else
                    uNextYNeighbour = xyU_prev[j + 1][i][2];

                if (j - 1 < 0 || !domainPointQ[j - 1][i])
                    uPrevYNeighbour = 0;
                else
                    uPrevYNeighbour = xyU_prev[j - 1][i][2];

                double dUx = (uNextXNeighbour - uPrevXNeighbour);
                double dUy = (uNextYNeighbour - uPrevYNeighbour);

                double d2Ux = (uNextXNeighbour - 2 * u + uPrevXNeighbour);
                double d2Uy = (uNextYNeighbour - 2 * u + uPrevYNeighbour);

                xyU[j][i][2] =
                        xyU_prev[j][i][2] - c * dt / 2 / h * (dUx + dUy) + c * c * dt * dt / 2 / h / h * (d2Ux + d2Uy);
            }
        }

        if (stepsElapsed % saveStep == 0) {
            std::cout << "Progress: " << 1. * stepsElapsed / stepsEstimated * 100 << "%" << std::endl;
            save();
        }

        t += dt;
        ++stepsElapsed;
    }
}

void Solver::save()
{
    std::fstream file;
    file.open(std::to_string(stepsElapsed), std::ios::out);
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            for (const double &item : xyU[j][i]) {
                file << item << "\t";
            }
            file << std::endl;
        }
    }
    file.close();
}
