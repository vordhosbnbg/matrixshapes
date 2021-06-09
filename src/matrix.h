#pragma once

#include <array>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <list>
#include <deque>

template<class T>
class Matrix
{
public:
    Matrix(unsigned int x, unsigned int y) :
        cols(x),
        rows(y),
        matrixSize(x*y)
    {
        memory.reserve(matrixSize);
    }

    struct Node
    {
        unsigned int x = 0;
        unsigned int y = 0;

    };

    unsigned int getAddress(const Node& it) const
    {
        return (it.y*cols + it.x);
    }

    bool setAddress(Node& it, unsigned int address) const
    {
        bool status = false;
        if(address < matrixSize)
        {
            std::ldiv_t res = std::div((long)address, (long)cols);
            it.x = res.rem;
            it.y = res.quot;

            status = true;
        }

        return status;
    }


    bool initFromString(const std::string& input)
    {
        bool status = false;
        if(input.size() == matrixSize)
        {
            std::transform(input.begin(), input.end(), memory.begin(), [](const char& c)
            {
                return (T)(c - '0');
            });
        }
        return status;
    }


    bool hasUp(const Node& it) const
    {
        return(it.y > 0);
    }

    bool hasDown(const Node& it) const
    {
        return(getAddress(it) + cols < matrixSize);
    }

    bool hasLeft(const Node& it) const
    {
        return((it.x > 0) && (it.x % cols));
    }

    bool hasRight(const Node& it) const
    {
        return((it.x < matrixSize - 1) && ((it.x + 1) % cols));
    }

    Node getRight(const Node& it) const
    {
        Node ret = it;
        ++ret.x;
        return ret;
    }

    Node getLeft(const Node& it) const
    {
        Node ret = it;
        --ret.x;
        return ret;
    }

    Node getUp(const Node& it) const
    {
        Node ret = it;
        --ret.y;
        return ret;
    }

    Node getDown(const Node& it) const
    {
        Node ret = it;
        ++ret.y;
        return ret;
    }

    void expandShapeBFS(std::vector<unsigned char>& visitedNodes, unsigned int startIndex, unsigned int shapeId) const
    {
        std::deque<Node> edgeNodes;
        Node& startNode = edgeNodes.emplace_back();
        setAddress(startNode, startIndex);

        while(!edgeNodes.empty())
        {
            // pop a node from the front of the queue
            // explore its adjacent nodes if not visited
            // mark them as visited
            // and add them as edges to the back of the queue if marked with 1
            Node& node = edgeNodes.front();

            if(hasRight(node))
            {
                Node right = getRight(node);
                unsigned int addr = getAddress(right);
                if(!visitedNodes[addr])
                {
                    visitedNodes[addr] = 1;
                    if(memory[addr])
                    {
                        edgeNodes.emplace_back(right);
                    }
                }
            }
            if(hasLeft(node))
            {
                Node left = getLeft(node);
                unsigned int addr = getAddress(left);
                if(!visitedNodes[addr])
                {
                    visitedNodes[addr] = 1;
                    if(memory[addr])
                    {
                        edgeNodes.emplace_back(left);
                    }
                }
            }
            if(hasDown(node))
            {
                Node down = getDown(node);
                unsigned int addr = getAddress(down);
                if(!visitedNodes[addr])
                {
                    visitedNodes[addr] = 1;
                    if(memory[addr])
                    {
                        edgeNodes.emplace_back(down);
                    }
                }
            }
            if(hasUp(node))
            {
                Node up = getUp(node);
                unsigned int addr = getAddress(up);
                if(!visitedNodes[addr])
                {
                    visitedNodes[addr] = 1;
                    if(memory[addr])
                    {
                        edgeNodes.emplace_back(up);
                    }
                }
            }
            edgeNodes.pop_front();
        }
    }

    unsigned int findNbShapes() const
    {
        unsigned int nbShapes = 0;
        std::vector<unsigned char> visitedNodes;
        visitedNodes.resize(matrixSize);

        for(unsigned int idx = 0; idx < visitedNodes.size(); ++idx)
        {

            if(!visitedNodes[idx]) // Haven't visited this node yet
            {
                visitedNodes[idx] = 1; // mark as visited
                if(memory[idx])
                {
                    // if marked 1 - new shape BFS expansion starts from it
                    expandShapeBFS(visitedNodes, idx, ++nbShapes);
                }
            }
        }

        return nbShapes;
    }

    T& at(unsigned int x, unsigned int y)
    {
        return memory[y*cols + x];
    }

    T& at(const Node& it)
    {
        return at(it.x, it.y);
    }

protected:
    unsigned int cols = 0;
    unsigned int rows = 0;
    size_t matrixSize = 0;
    std::vector<T> memory;
};
