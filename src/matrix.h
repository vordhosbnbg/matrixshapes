#pragma once

#include <array>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <list>
#include <deque>

template<typename MatrixValueType, typename VisitedNodesType, typename NodeAddrType>
class Matrix
{
public:
    enum class Direction
    {
        RIGHT,
        LEFT,
        DOWN,
        UP
    };

    Matrix(unsigned int x, unsigned int y) :
        cols(x),
        rows(y),
        matrixSize(x*y)
    {
        memory.reserve(matrixSize);
    }

    struct Node
    {
        NodeAddrType x = 0;
        NodeAddrType y = 0;
    };

    // get the offset of a node
    unsigned int getAddress(const Node& it) const
    {
        return (it.y*cols + it.x);
    }

    // set node's coordinates from an address
    bool setAddress(Node& it, unsigned int address) const
    {
        bool status = false;
        if(address < matrixSize)
        {
            std::div_t res = std::div((int)address, (int)cols);
            it.x = res.rem;
            it.y = res.quot;

            status = true;
        }

        return status;
    }

    // store a string of '0's and '1's as 0/1 integer data
    bool initFromString(const std::string& input)
    {
        bool status = false;
        if(input.size() == matrixSize)
        {
            std::transform(input.begin(), input.end(), memory.begin(), [](const char& c)
            {
                return (MatrixValueType)(c - '0');
            });
        }
        return status;
    }


    // the following checks if a node can "exist" spatially in the corresponding direction
    // and if it's safe to return a node from it
    bool existsInDirection(const Node& it, Direction direction) const
    {
        switch (direction)
        {
            case Direction::RIGHT:
                return((it.x < matrixSize - 1) && ((it.x + 1) % cols));
            case Direction::LEFT:
                return((it.x > 0) && (it.x % cols));
            case Direction::DOWN:
                return(getAddress(it) + cols < matrixSize);
            case Direction::UP:
                return(it.y > 0);
        };

        return false;
    }

    // the following returns a new node in the corresponding direction
    // they are not safe and should be called after checking bounds
    Node getAdjacent(const Node& it, Direction direction) const
    {
        Node ret = it;
        switch (direction)
        {
            case Direction::RIGHT:
                ++ret.x;
                break;
            case Direction::LEFT:
                --ret.x;
                break;
            case Direction::DOWN:
                ++ret.y;
                break;
            case Direction::UP:
                --ret.y;
                break;
        }

        return ret;
    }

    void exploreDirection(std::vector<Node>& edgeNodes,
                          std::vector<VisitedNodesType>& visitedNodes,
                          const Node& node,
                          Direction direction) const
    {
        if(existsInDirection(node, direction))
        {
            Node adjacentNode = getAdjacent(node, direction);
            unsigned int addr = getAddress(adjacentNode);

            // get the adjacent node and if not visited
            if(!visitedNodes[addr])
            {
                // mark as visited
                visitedNodes[addr] = 1;
                if(memory[addr])
                {
                    // if it has 1, place it to the back of the queue
                    edgeNodes.emplace_back(adjacentNode);
                }
            }
        }
    }

    // starting from a specific point expand using BFS
    // and visit all connected nodes forming a shape
    // here edgeNodes is passed from the caller to reduce memory allocations
    void expandShapeBFS(std::vector<Node>& edgeNodes,
                        std::vector<VisitedNodesType>& visitedNodes,
                        unsigned int startIndex) const
    {
        edgeNodes.clear();
        Node& startNode = edgeNodes.emplace_back();
        setAddress(startNode, startIndex);

        // expansionIndex marks the node that we are currently exploring
        size_t expansionIndex = 0;
        while(expansionIndex < edgeNodes.size())
        {
            // get a node from the front of the queue
            // explore its adjacent nodes if not visited
            // mark them as visited
            // and add them as edges to the back of the queue if marked with 1
            Node node = edgeNodes[expansionIndex++];

            exploreDirection(edgeNodes, visitedNodes, node, Direction::RIGHT);
            exploreDirection(edgeNodes, visitedNodes, node, Direction::LEFT);
            exploreDirection(edgeNodes, visitedNodes, node, Direction::DOWN);
            exploreDirection(edgeNodes, visitedNodes, node, Direction::UP);
        }
    }

    // find all shapes formed by connected 1s in the matrix
    unsigned int findNbShapes() const
    {

        // keep track of visited nodes, iterate trough all
        unsigned int nbShapes = 0;
        std::vector<VisitedNodesType> visitedNodes;
        std::vector<Node> edgeNodesWorkspace;
        edgeNodesWorkspace.reserve(matrixSize);
        visitedNodes.resize(matrixSize);

        for(unsigned int idx = 0; idx < visitedNodes.size(); ++idx)
        {

            if(!visitedNodes[idx]) // Haven't visited this node yet
            {
                visitedNodes[idx] = 1; // mark as visited
                if(memory[idx])
                {
                    // if marked 1 - its a new shape - do BFS expansion from it
                    expandShapeBFS(edgeNodesWorkspace, visitedNodes, idx);
                    ++nbShapes;
                }
            }
        }

        return nbShapes;
    }

protected:
    unsigned int cols = 0;
    unsigned int rows = 0;
    size_t matrixSize = 0;
    std::vector<MatrixValueType> memory;
};
