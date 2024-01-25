#ifndef TESTTASK_ELLIPSE_H
#define TESTTASK_ELLIPSE_H
#include "vector"
#include "cmath"

class Ellipse : public Curve{
    double radiusX, radiusY;
public:
    Ellipse(double rx, double ry) : radiusX(rx > 0 ? rx : 1), radiusY(ry > 0 ? ry : 1) {}
    ~Ellipse() override = default;
    [[nodiscard]] std::pair<std::vector<double>, std::vector<double>> getPointAndDerivative(double t) const override;
};

#endif //TESTTASK_ELLIPSE_H
