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

double Pipe::getTotalVolume() const
{
    return getArea() * length;
}

double Pipe::getVolume() const
{
    return volume;
}

Fluid& Pipe::getFluid() const
{
    return fluid;
}

// Calculate flow rate using Hagen-Poiseuille Equation
double Pipe::calculateFlowRate(double dP)
{
    double radius = diameter / 2.0;

    double flowRate = (M_PI * pow(radius, 4) * dP) / (8 * fluid.getViscosity() * length);
    return flowRate;
}

// Calculate difference in pressure between two nodes including elevation
double Pipe::calculatePressureDifference()
{
    double pressureDifference = abs(start->getPressure() - end->getPressure());
    double elevationChange = abs(end->getZ() - start->getZ());

    double gravityEffect = fluid.getDensity() * 9.82 * elevationChange;

    return std::max(0.0, pressureDifference - gravityEffect);
}

// Calculate losses in pressure due to resistance in pipes
double Pipe::calculatePressureDrop()
{
    //double pressureOut = 0;


    // TODO: Fix friction calculation 
    //// Darcy-Weisbach friction factor
    //double f = 1;
    //double estimatedVelocity = std::min(30.0, std::max(-30.0, (pressureDifference * pow(diameter, 2)) / (32 * fluid.getViscosity() * length)));
    //double frictionLoss = (f * length * fluid.getDensity() * pow(estimatedVelocity, 2)) / (diameter * 2);




    double pressureDrop = 0;

    return pressureDrop;
}