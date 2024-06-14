#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Pipe.h"

class Node
{
public:
    Node(double pressure = 0.0, double x = 0.0, double y = 0.0, double z = 0.0);
    ~Node();

    double getPressure() const;
    void setPressure(double pressure);

    void addPipe(Pipe* pipe);

    double getX() const;
    double getY() const;
    double getZ() const;

    void distributePressureChanges(double timeStep);

private:
    double pressure;
    double x, y, z; // 3D coordinates
    std::vector<Pipe*> connectedPipes;
};

#endif // NODE_H