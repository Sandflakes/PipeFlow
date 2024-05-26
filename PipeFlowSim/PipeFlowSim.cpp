#include <iostream>
#include "Fluid.h"
#include "Network.h"

int main() {
    Fluid water(1000, 0.001); // Density in kg/m^3, viscosity in Pa.s

    Network network;

    Node* source = network.createNode(100000, 0.0, 0.0, 0.0); // Source with high pressure (Pa) at (0,0,10)
    Node* junction = network.createNode(50000, 0.0, 0.0, 0.0); // Intermediate junction (Pa) at (10,0,5)
    Node* consumer = network.createNode(100, 0.0, 0.0, 0.0); // Consumer with low pressure (Pa) at (20,0,0)

    network.createPipe(source, junction, 10, 0.1, water); // Pipe from source to junction
    network.createPipe(junction, consumer, 10, 0.1, water); // Pipe from junction to consumer

    network.simulate(0.1, 10); // Simulate with a time step of 0.1 seconds for a total of 10 seconds

    return 0;
}