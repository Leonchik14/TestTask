#include <iostream>
#include <memory>
#include "Curve.h"
#include "Circle.cpp"
#include "Ellipse.cpp"
#include "Helix.cpp"
#include "random"
#include "algorithm"
#include "omp.h"

std::vector<std::shared_ptr<Curve>> generateFiguresVector(int count, double lowerBound, double upperBound) {
    std::vector<std::shared_ptr<Curve>> figures(count);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> distribution(lowerBound, upperBound);
    for (int i = 0; i < count; ++i) {
        switch (  (int)distribution(rng) % 3) {
            case 0:
                figures[i] = std::make_shared<Circle>(distribution(rng));
                break;
            case 1:
                figures[i] = std::make_shared<Ellipse>(distribution(rng), distribution(rng));
                break;
            case 2:
                figures[i] = std::make_shared<Helix>(distribution(rng), distribution(rng));
                break;
        }
    }
    return figures;
}

void printInfoAboutFigures(std::vector<std::shared_ptr<Curve>>& figures, double t) {
    for (int i = 0; i < figures.size(); ++i) {
        std::pair <std::vector<double>, std::vector<double>> info = figures[i]->getPointAndDerivative(t);
        std::cout << "Figure " << i + 1 << '\n';
        std::cout << "3D Point: " << info.first[0] << " " << info.first[1] << " " << info.first[2] << '\n';
        std::cout << "First derivative: " << info.second[0] << " " << info.second[1] << " " << info.second[2] << '\n';
        std::cout << '\n';
    }
}

std::vector<std::shared_ptr<Circle>> getCirclesFromFigures(std::vector<std::shared_ptr<Curve>>& figures) {
    std::vector<std::shared_ptr<Circle>> circles;
    for (auto & figure : figures) {
        if (std::shared_ptr<Circle> p = std::dynamic_pointer_cast<Circle>(figure)) {
            circles.push_back(p);
        }
    }
    return circles;
}

bool circleComparator(const std::shared_ptr<Circle>& lhs, const std::shared_ptr<Circle>& rhs)
{
    return lhs->getRadius() < rhs->getRadius();
}

double getRadiiSum(std::vector<std::shared_ptr<Circle>>& circles) {
    double radiiSum = 0;

    #pragma omp parallel for reduction(+:radiiSum)
    for (const auto& circle : circles) {
        radiiSum += circle->getRadius();
    }
    return radiiSum;
}

void printCirclesRadios(std::vector<std::shared_ptr<Circle>>& circles) {
    for (const auto& circle : circles) {
        std::cout << circle->getRadius() << " ";
    }
    std::cout << '\n';
}

int main() {
    std::vector<std::shared_ptr<Curve>> figures = generateFiguresVector(10000, 1, 10);
    printInfoAboutFigures(figures, M_PI/4);
    std::vector<std::shared_ptr<Circle>> circles = getCirclesFromFigures(figures);
    std::cout << "Circles before sorting:\n";
    printCirclesRadios(circles);
    std::sort(circles.begin(), circles.end(), circleComparator);
    std::cout << "Circles after sorting:\n";
    printCirclesRadios(circles);
    std::cout << "Sum of all radios: " << getRadiiSum(circles);
}
