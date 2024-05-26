#include "Pipe.h"
#include "Node.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Pipe::Pipe(Node* start, Node* end, double length, double diameter, Fluid& fluid)
    : start(start), end(end), length(length), diameter(diameter), fluid(fluid) 
{
}

Node* Pipe::getStart() const 
{
    return start;
}

Node* Pipe::getEnd() const 
{
    return end;
}

double Pipe::getLength() const 
{
    return length;
}

double Pipe::getDiameter() const 
{
    return diameter;
}

double Pipe::getArea() const
{
    return M_PI * std::pow(diameter / 2.0, 2);
}

double Pipe::getVolume() const
{
    return getArea() * length;
}

Fluid& Pipe::getFluid() const
{
    return fluid;
}

// Calculate flow rate using Hagen-Poiseuille Equation
double Pipe::calculateFlowRate()
{
    double radius = diameter / 2.0;

    double dP = calculatePressureDifference();
    double flowRate = (M_PI * pow(radius, 4) * dP) / (8 * fluid.getViscosity() * length);
    return flowRate;
}

// Calculate losses in pressure due to resistance in pipes and elevation change
double Pipe::calculatePressureDifference()
{
    double pressureOut = 0;

    double pressureDifference = start->getPressure() - end->getPressure();
    double elevationChange = end->getZ() - start->getZ();

    // TODO: Fix friction calculation 
    //// Darcy-Weisbach friction factor
    //double f = 1;
    //double estimatedVelocity = std::min(30.0, std::max(-30.0, (pressureDifference * pow(diameter, 2)) / (32 * fluid.getViscosity() * length)));
    //double frictionLoss = (f * length * fluid.getDensity() * pow(estimatedVelocity, 2)) / (diameter * 2);


    // Simplify code by extracting the direction
    double flowDir = signbit(pressureDifference) ? -1 : 1;
    double elevationDir = signbit(elevationChange) ? -1 : 1;

    pressureDifference = abs(pressureDifference);
    elevationChange = abs(elevationChange);
    

    double gravityEffect = fluid.getDensity() * 9.82 * elevationChange;

    pressureOut = std::max(0.0, pressureDifference - gravityEffect * elevationDir * flowDir) * flowDir;


    return pressureOut;
}