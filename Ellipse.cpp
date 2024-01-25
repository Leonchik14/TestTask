#include "Ellipse.h"

std::pair<std::vector<double>, std::vector<double>> Ellipse::getPointAndDerivative(double t) const {
    return {{radiusX * cos(t), radiusY * sin(t), 0},
            {-radiusX * sin(t), radiusY * cos(t), 0}};
}