#ifndef TESTTASK_HELIX_H
#define TESTTASK_HELIX_H
#include "vector"
#include "cmath"

class Helix : public Curve {
    double radius, step;
public:
    Helix(double r, double s) : radius(r > 0 ? r : 1), step(s > 0 ? s : 1) {}
    ~Helix() override = default;
    [[nodiscard]] std::pair<std::vector<double>, std::vector<double>> getPointAndDerivative(double t) const override;
};

#endif //TESTTASK_HELIX_H
