#ifndef NODE_H
#define NODE_H

#include <vector>

class Pipe;

class Node {
public:
    Node(double pressure = 0.0, double x = 0.0, double y = 0.0, double z = 0.0);
    ~Node();

    double getPressure() const;
    void setPressure(double pressure);

    void addOutgoingPipe(Pipe* pipe);
    void addIncomingPipe(Pipe* pipe);

    double getX() const;
    double getY() const;
    double getZ() const;

private:
    double pressure;
    double x, y, z; // 3D coordinates
    std::vector<Pipe*> outgoingPipes;
    std::vector<Pipe*> incomingPipes;
};

#endif // NODE_H