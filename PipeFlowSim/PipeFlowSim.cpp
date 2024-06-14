#include <iostream>
#include "Fluid.h"
#include "Network.h"

int main() 
{
    Fluid water(1000, 0.001); // Density in kg/m^3, viscosity in Pa.s

    Network network;

    Node* N0 = network.createNode(100000, 0.0, 0.0, 0.0);
    Node* N1 = network.createNode(0, 0.0, 0.0, 0.0);
    Node* N2 = network.createNode(0, 0.0, 0.0, 0.0);
    Node* N3 = network.createNode(0, 0.0, 0.0, 0.0);
    Node* N4 = network.createNode(0, 0.0, 0.0, 0.0);

    network.createPipe(N0, N1, 1, 1, water);
    network.createPipe(N1, N2, 10, 0.1, water);
    network.createPipe(N2, N3, 10, 0.1, water);
    network.createPipe(N2, N4, 10, 0.1, water);

    network.simulate(0.1, 10); // Simulate with a time step of 0.1 seconds for a total of 10 seconds

    return 0;
}