#ifndef TESTTASK_CURVE_H
#define TESTTASK_CURVE_H
#include "vector"
#include "cmath"

class Curve {
public:
    virtual ~Curve() = default;
    [[nodiscard]] virtual std::pair<std::vector<double>, std::vector<double>> getPointAndDerivative(double t) const = 0;
};



#endif //TESTTASK_CURVE_H
