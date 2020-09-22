//
// Created by mi on 22.09.2020.
//

#ifndef CDE_BOUNDINGRECT_H
#define CDE_BOUNDINGRECT_H

#include <vector>

class BoundingRect
{
private:
    std::vector<std::vector<double>> size = std::vector<std::vector<double>>(2, std::vector<double>(2, 0));
public:
    const std::vector<std::vector<double>> &getSize() const;

    void setSize(const std::vector<std::vector<double>> &size);

    double getXSize();
    double getYSize();


public:
    BoundingRect(const double &xmin, const double &xmax, const double &ymin, const double &ymax);
};


#endif //CDE_BOUNDINGRECT_H
