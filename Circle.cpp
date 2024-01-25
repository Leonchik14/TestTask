#include "vector"
#include "cmath"

#include "Circle.h"



std::pair <std::vector<double>, std::vector<double>> Circle::getPointAndDerivative(double t) const  {
    return {{radius * cos(t), radius * sin(t), 0},
            {-radius * sin(t), radius * cos(t), 0}};
}
