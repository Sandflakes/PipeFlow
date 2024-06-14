#ifndef PIPE_H
#define PIPE_H

#include "Fluid.h"

class Node;

class Pipe {
public:
    Pipe(Node* start, Node* end, double length, double diameter, Fluid& fluid);

    Node* getStart() const;
    Node* getEnd() const;
    double getLength() const;
    double getDiameter() const;
    double getArea() const;
    double getTotalVolume() const;
    double getVolume() const;
    Fluid& getFluid() const;
    
    double calculateFlowRate(double dp);
    double calculatePressureDifference();
    double calculatePressureDrop();

private:
    double volume;
    Node* start;
    Node* end;
    double length;
    double diameter;
    Fluid& fluid;
};

#endif // PIPE_H