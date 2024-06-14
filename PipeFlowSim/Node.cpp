#include "Node.h"
#include "Pipe.h"
#include <algorithm>

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

void Node::addPipe(Pipe* pipe)
{
    connectedPipes.push_back(pipe);
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

void Node::distributePressureChanges(double timeStep)
{
    // Calculate the pressure drop for each connected pipe segment and summarize it
    double totalPressureDrop = 0;
    double totalPressureDifference = 0;
    std::vector<std::pair<Pipe*, std::pair<double, double>>> pipePressureDrop;

    for (Pipe* pipe : connectedPipes)
    {
        double pressureDrop = pipe->calculatePressureDrop();
        totalPressureDrop += pressureDrop;

        double pressureDifference = pipe->calculatePressureDifference();

        totalPressureDifference += pressureDifference;

        pipePressureDrop.push_back({ pipe, {pressureDrop, pressureDifference} });

    }

    double targetPressure = totalPressureDifference / (connectedPipes.size() + 1);

    // Distribute the pressure drop across all connected nodes
    for (const auto& pair : pipePressureDrop)
    {
        Pipe* pipe = pair.first;
        double pressureDrop = pair.second.first;
        double pressureDifference = pair.second.second;

        Node* start = pipe->getStart();
        Node* end = pipe->getEnd();

        double pressureProportion = pressureDifference - targetPressure;

        //double flowRate = pipe->calculateFlowRate(pressureProportion);

        //// Calculate the change in volume due to flow in the pipe
        //double deltaVolume = std::max(-pipe->getTotalVolume() / 2, std::min(pipe->getTotalVolume() / 2, flowRate * timeStep));

        //double deltaP = pipe->getFluid().getDensity() * 9.82 * deltaVolume / pipe->getTotalVolume();

        //double deltaPSign = signbit(deltaP) ? -1 : 1;

        //double startPressure = start->getPressure();
        //double endPressure = end->getPressure();

        //double dPStart = startPressure - std::max(0.0, startPressure - deltaP);
        //double dPEnd = endPressure - std::max(0.0, endPressure + deltaP);

        //deltaP = std::min(abs(dPStart), abs(dPEnd)) * deltaPSign;


        //// Adjust the pressures at the nodes
        //double newStartPressure = std::max(0.0, startPressure - deltaP);
        //double newEndPressure = std::max(0.0, endPressure + deltaP);
        
        /*start->setPressure(newStartPressure);
        end->setPressure(newEndPressure);*/


        double startPressure = start->getPressure();
        double endPressure = end->getPressure();
        double newStartPressure = std::max(0.0, startPressure - pressureProportion);
        double newEndPressure = std::max(0.0, endPressure + pressureProportion);
        start->setPressure(newStartPressure);
        end->setPressure(newEndPressure);

        //if (start == this)
        //{
        //    start->setPressure(std::max(0.0, start->getPressure() - deltaP));
        //    end->setPressure(end->getPressure() + deltaP);
        //}
        //else if (end == this)
        //{
        //    end->setPressure(std::max(0.0, end->getPressure() - deltaP));
        //    start->setPressure(start->getPressure() + deltaP);
        //}
    }
}