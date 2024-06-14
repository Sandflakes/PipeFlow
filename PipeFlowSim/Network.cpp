#include "Network.h"
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

std::string ptrToStr(const void* ptr)
{
    std::ostringstream oss;
    oss << ptr;
    std::string str = oss.str();
    return str.substr(str.length() - 2); // Using the last two characters
}

Network::Network()
{
}

Network::~Network()
{
    for (Node* node : nodes)
    {
        delete node;
    }
    for (Pipe* pipe : pipes)
    {
        delete pipe;
    }
}

Node* Network::createNode(double pressure, double x, double y, double z)
{
    Node* node = new Node(pressure, x, y, z);
    nodes.push_back(node);
    return node;
}

Pipe* Network::createPipe(Node* start, Node* end, double length, double diameter, Fluid& fluid)
{
    Pipe* pipe = new Pipe(start, end, length, diameter, fluid);
    start->addPipe(pipe);
    end->addPipe(pipe);
    pipes.push_back(pipe);
    return pipe;
}

void Network::simulate(double timeStep, double totalTime)
{
    for (double time = 0; time < totalTime; time += timeStep)
    {
        std::cout << "Time: " << time << " s\n";

        for (Node* node : nodes)
        {
            node->distributePressureChanges(timeStep);
        }

        visualize();
        std::cout << std::endl;
    }
}

void Network::visualize() const
{
    std::map<std::string, char> nodeIds;
    char currentId = 'A';

    for (const Node* node : nodes)
    {
        nodeIds[ptrToStr(node)] = currentId++;
    }

    std::cout << "Network State:\n";

    for (const Node* node : nodes)
    {
        std::cout << "Node " << nodeIds.at(ptrToStr(node)) << " ("
            << "x: " << node->getX() << ", y: " << node->getY() << ", z: " << node->getZ() << ") "
            << "pressure: " << std::fixed << std::setprecision(2) << node->getPressure() << " Pa\n";
    }

    //for (Pipe* pipe : pipes)
    //{
    //    double pressureDrop = pipe->calculatePressureDrop();
    //    std::cout << "Pipe from Node " << nodeIds.at(ptrToStr(pipe->getStart()))
    //        << " to Node " << nodeIds.at(ptrToStr(pipe->getEnd()))
    //        << " flow rate: " << pipe->calculateFlowRate(pressureDrop) << " m^3/s"
    //        << " pressure drop: " << pressureDrop << " Pa\n";
    //}

    std::cout << "\nNetwork Diagram:\n";
    for (const Pipe* pipe : pipes)
    {
        std::cout << nodeIds.at(ptrToStr(pipe->getStart())) << " -> "
            << nodeIds.at(ptrToStr(pipe->getEnd())) << "\n";
    }

    std::cout << std::endl;
}