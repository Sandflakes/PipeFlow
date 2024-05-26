#include "Network.h"
#include <iostream>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm> // Include algorithm for std::max

// Helper function to convert a pointer to a unique identifier
std::string ptrToStr(const void* ptr) 
{
    std::ostringstream oss;
    oss << ptr;
    std::string str = oss.str();
    return str.substr(str.length() - 2); // Using the last two characters
}

Network::Network() 
{
    // Constructor implementation can be empty for now
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
    start->addOutgoingPipe(pipe);
    end->addIncomingPipe(pipe);
    pipes.push_back(pipe);
    return pipe;
}

void Network::simulate(double timeStep, double totalTime) 
{
    // Visualize the state of the network for each time step
    std::cout << "Time: " << 0.0 << " s\n";
    visualize();
    std::cout << std::endl;

    for (double time = timeStep; time < totalTime; time += timeStep)
    {   
        std::cout << "Time: " << time << " s\n";
        //std::vector<double> pressureChanges(nodes.size(), 0.0);

        for (Pipe* pipe : pipes) 
        {
            double flowRate = pipe->calculateFlowRate();
            std::cout << "FlowRate: " << flowRate << " m^3/s, " << "Velocity: " << flowRate / pipe->getArea() << " m/s\n";

            Node* start = pipe->getStart();
            Node* end = pipe->getEnd();

            

            double startPressure = start->getPressure();
            double endPressure = end->getPressure();

            // Calculate the change in volume due to flow in the pipe
            double deltaVolume = std::max(-pipe->getVolume() / 2, std::min(pipe->getVolume() / 2, flowRate * timeStep));

            double deltaP = pipe->getFluid().getDensity() * 9.82 * deltaVolume / pipe->getVolume();
            std::cout << "deltaP: " << deltaP << " Pa\n";

            double deltaPSign = signbit(deltaP) ? -1 : 1;

            double dPStart = startPressure - std::max(0.0, startPressure - deltaP);
            double dPEnd = endPressure - std::max(0.0, endPressure + deltaP);

            deltaP = std::min( abs(dPStart), abs(dPEnd)) * deltaPSign;

            

            // Adjust the pressures at the nodes
            double newStartPressure = std::max(0.0, startPressure - deltaP);
            double newEndPressure = std::max(0.0, endPressure + deltaP);

            start->setPressure(newStartPressure);
            end->setPressure(newEndPressure);


        }

        // Visualize the state of the network for each time step
        visualize();
        std::cout << std::endl;
    }
}

void Network::visualize() const 
{
    std::map<std::string, char> nodeIds;
    char currentId = 'A';

    // Assign a unique letter to each node
    for (const Node* node : nodes) 
    {
        nodeIds[ptrToStr(node)] = currentId++;
    }

    std::cout << "Network State:\n";

    // Print nodes with pressures and coordinates
    for (const Node* node : nodes) 
    {
        std::cout << "Node " << nodeIds.at(ptrToStr(node)) << " ("
            << "x: " << node->getX() << ", y: " << node->getY() << ", z: " << node->getZ() << ") "
            << "pressure: " << std::fixed << std::setprecision(2) << node->getPressure() << " Pa\n";
    }

    //// Print pipes with flow rates and pressure drops
    //for (Pipe* pipe : pipes) 
    //{
    //    std::cout << "Pipe from Node " << nodeIds.at(ptrToStr(pipe->getStart()))
    //        << " to Node " << nodeIds.at(ptrToStr(pipe->getEnd()))
    //        << " flow rate: " << pipe->calculateFlowRate() << " m^3/s"
    //        << " pressure drop: " << pipe->calculatePressureDrop() << " Pa\n";
    //}

    // Print ASCII art of the network
    std::cout << "\nNetwork Diagram:\n";

    // Using a simple layout where nodes are letters and pipes are lines
    for (const Pipe* pipe : pipes) 
    {
        std::cout << nodeIds.at(ptrToStr(pipe->getStart())) << " -> "
            << nodeIds.at(ptrToStr(pipe->getEnd())) << "\n";
    }

    std::cout << std::endl;
}