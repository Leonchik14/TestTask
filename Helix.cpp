#include "Helix.h"

std::pair<std::vector<double>, std::vector<double>> Helix::getPointAndDerivative(double t) const {
    return {{radius * cos(t), radius * sin(t), step * t / (2 * M_PI)},
            {-radius * sin(t), radius * cos(t), step / (2 * M_PI)}};
}