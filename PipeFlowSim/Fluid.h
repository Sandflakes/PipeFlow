#ifndef FLUID_H
#define FLUID_H

class Fluid 
{
public:
    Fluid(double density, double viscosity);
    double getDensity() const;
    double getViscosity() const;

private:
    double density;  // kg/m^3
    double viscosity; // Pa.s
};

#endif // FLUID_H