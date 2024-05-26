#ifndef PIPE_H
#define PIPE_H

#include "Fluid.h"

class Node;

class Pipe {
public:
    Pipe(Node* start, Node* end, double length, double diameter, const Fluid& fluid);

    Node* getStart() const;
    Node* getEnd() const;
    double getLength() const;
    double getDiameter() const;

    double calculateFlowRate() const;
    double calculatePressureDrop() const;

private:
    Node* start;
    Node* end;
    double length;
    double diameter;
    const Fluid& fluid;
};

#endif // PIPE_H