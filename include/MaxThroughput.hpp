#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "../include/Node.hpp"

#define MAX_SIZE 50

class MaxThroughput
{
public:
    MaxThroughput(int, int);
    ~MaxThroughput();

    void loadData(std::string);
    void calculateThroughput();
    void findAllPaths(int, int, int);
    int findThroughputForPath(std::vector<int>);
    void printOptimalPath(std::string, int, int);

private:
    int numNodes;
    bool *visited;
    int *path;
    int adj[MAX_SIZE][MAX_SIZE];
    std::vector<Node> paths;
    std::vector<std::vector<int> > allPossiblePaths;
    int totalBits;
};