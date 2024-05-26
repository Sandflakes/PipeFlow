#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Node.h"
#include "Pipe.h"
#include "Fluid.h"

class Network 
{
public:
    Network();
    ~Network();

    Node* createNode(double pressure, double x, double y, double z);
    Pipe* createPipe(Node* start, Node* end, double length, double diameter, Fluid& fluid);

    void simulate(double timeStep, double totalTime);
    void visualize() const;

private:
    std::vector<Node*> nodes;
    std::vector<Pipe*> pipes;
};

#endif // NETWORK_H