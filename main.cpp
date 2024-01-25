#include <iostream>
#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"
#include "random"
#include "algorithm"

std::vector<Curve*> generateFiguresVector(int count, double lowerBound, double upperBound) {
    std::vector<Curve*> figures(10);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<double> distribution(lowerBound, upperBound);
    for (int i = 0; i < count; ++i) {
        switch (  (int)distribution(rng) % 3) {
            case 0:
                figures[i] = new Circle(distribution(rng));
                break;
            case 1:
                figures[i] = new Ellipse(distribution(rng), distribution(rng));
                break;
            case 2:
                figures[i] = new Helix(distribution(rng), distribution(rng));
                break;
        }
    }
    return figures;
}

void printInfoAboutFigures(std::vector<Curve*>& figures, double t) {
    for (int i = 0; i < figures.size(); ++i) {
        std::pair <std::vector<double>, std::vector<double>> info = figures[i]->getPointAndDerivative(t);
        std::cout << "Figure " << i + 1;
        std::cout << "3D Point: " << info.first[0] << " " << info.first[1] << " " << info.first[2] << '\n';
        std::cout << "First derivative: " << info.second[0] << " " << info.second[1] << " " << info.second[2] << '\n';
        std::cout << '\n';
    }
}

std::vector<Circle*> getCirclesFromFigures(std::vector<Curve*>& figures) {
    std::vector<Circle*> circles;
    for (auto & figure : figures) {
        if (auto *p = dynamic_cast<Circle *>(figure)) {
            circles.push_back(p);
        }
    }
    return circles;
}

bool circleComparator(const Circle* lhs, const Circle* rhs)
{
    return lhs->getRadius() < rhs->getRadius();
}

double getRadiiSum(std::vector<Circle*>& circles) {
    double  sum = 0;
    for (auto *circle : circles) {
        sum += circle->getRadius();
    }
    return sum;
}

int main() {
    std::vector<Curve*> figures = generateFiguresVector(10, 1, 10);
    printInfoAboutFigures(figures, M_PI/4);
    std::vector<Circle*> circles = getCirclesFromFigures(figures);
    std::sort(circles.begin(), circles.end(), circleComparator);
    std::cout << getRadiiSum(circles);

}
