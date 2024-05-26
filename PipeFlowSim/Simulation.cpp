#include "Simulation.h"
#include "Pipe.h" // Include the definition of Pipe
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Simulation::Simulation(const Fluid& fluid, const Pipe& pipe)
    : fluid(fluid), pipe(pipe) {}

void Simulation::run() {
    double flowRate = calculateFlowRate();
    double pressureDrop = calculatePressureDrop();

    std::cout << "Flow Rate: " << flowRate << " m^3/s" << std::endl;
    std::cout << "Pressure Drop: " << pressureDrop << " Pa" << std::endl;
}

double Simulation::calculateFlowRate() const {
    // Example calculation using the Hagen-Poiseuille equation for laminar flow
    double radius = pipe.getDiameter() / 2.0;
    double area = M_PI * std::pow(radius, 2);
    double flowRate = (area * std::pow(radius, 2) * fluid.getDensity()) / (8 * fluid.getViscosity() * pipe.getLength());
    return flowRate;
}

double Simulation::calculatePressureDrop() const {
    // Example calculation of pressure drop using Darcy-Weisbach equation
    double radius = pipe.getDiameter() / 2.0;
    double velocity = calculateFlowRate() / (M_PI * std::pow(radius, 2));
    double reynoldsNumber = (fluid.getDensity() * velocity * pipe.getDiameter()) / fluid.getViscosity();
    double frictionFactor = 64.0 / reynoldsNumber; // For laminar flow
    double pressureDrop = (frictionFactor * pipe.getLength() / pipe.getDiameter()) * (0.5 * fluid.getDensity() * std::pow(velocity, 2));
    return pressureDrop;
}