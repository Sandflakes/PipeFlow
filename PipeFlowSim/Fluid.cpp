#include "Fluid.h"

Fluid::Fluid(double density, double viscosity)
    : density(density), viscosity(viscosity) {}

double Fluid::getDensity() const 
{
    return density;
}

double Fluid::getViscosity() const 
{
    return viscosity;
}