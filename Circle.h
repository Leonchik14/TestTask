
#ifndef TESTTASK_CIRCLE_H
#define TESTTASK_CIRCLE_H


class Circle : public Curve {
    double radius;
public:
    explicit Circle(double r) : radius(r > 0 ? r : 1) {}
    ~Circle() override = default;
    [[nodiscard]] double getRadius() const { return radius; }
    [[nodiscard]] std::pair<std::vector<double>, std::vector<double>> getPointAndDerivative(double t) const override;
};


#endif //TESTTASK_CIRCLE_H
