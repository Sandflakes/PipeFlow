#ifndef SIMULATION_H
#define SIMULATION_H

#include "Fluid.h"

class Pipe; // Forward declaration

class Simulation {
public:
    Simulation(const Fluid& fluid, const Pipe& pipe);
    void run();

private:
    Fluid fluid;
    const Pipe& pipe; // Use a reference instead of a value to avoid incomplete type issues

    double calculateFlowRate() const;
    double calculatePressureDrop() const;
};

#endif // SIMULATION_H