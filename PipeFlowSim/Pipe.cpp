#include "Pipe.h"
#include "Node.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Pipe::Pipe(Node* start, Node* end, double length, double diameter, const Fluid& fluid)
    : start(start), end(end), length(length), diameter(diameter), fluid(fluid) {}

Node* Pipe::getStart() const {
    return start;
}

Node* Pipe::getEnd() const {
    return end;
}

double Pipe::getLength() const {
    return length;
}

double Pipe::getDiameter() const {
    return diameter;
}

double Pipe::calculateFlowRate() const {
    // Example calculation using the Hagen-Poiseuille equation for laminar flow
    double radius = diameter / 2.0;
    double area = M_PI * std::pow(radius, 2);
    double pressureDifference = start->getPressure() - end->getPressure();

    double flowRate = (area * std::pow(radius, 2) * pressureDifference) / (8 * fluid.getViscosity() * length);
    return flowRate;
}

double Pipe::calculatePressureDrop() const {
    double elevationChange = end->getZ() - start->getZ();
    double gravityEffect = fluid.getDensity() * 9.81 * elevationChange; // 9.81 m/s^2 is the gravitational acceleration

    double flowRate = calculateFlowRate();
    double frictionLoss = 8 * fluid.getViscosity() * flowRate * length / (M_PI * std::pow(diameter, 4));

    return frictionLoss + gravityEffect;
}