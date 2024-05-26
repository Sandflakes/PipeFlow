#include "Node.h"
#include "Pipe.h"

Node::Node(double pressure, double x, double y, double z)
    : pressure(pressure), x(x), y(y), z(z) 
{
}

Node::~Node() 
{
}

double Node::getPressure() const 
{
    return pressure;
}

void Node::setPressure(double pressure) 
{
    this->pressure = pressure;
}

void Node::addOutgoingPipe(Pipe* pipe) 
{
    outgoingPipes.push_back(pipe);
}

void Node::addIncomingPipe(Pipe* pipe) 
{
    incomingPipes.push_back(pipe);
}

double Node::getX() const 
{
    return x;
}

double Node::getY() const 
{
    return y;
}

double Node::getZ() const 
{
    return z;
}