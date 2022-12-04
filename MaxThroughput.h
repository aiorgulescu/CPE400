#ifndef MAX_THROUGHPUT_H
#define MAX_THROUGHPUT_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#define MAX_SIZE 50

class MaxThroughput {
    private:
        int numNodes;
        bool *visited;
        int *path;
        int adj[MAX_SIZE][MAX_SIZE] = {0};
        vector<vector<int>> paths;
        vector<vector<int>> allPossiblePaths;
        int totalBits;

    public:
    MaxThroughput(int, int);
    ~MaxThroughput();

    void loadData(string);
    void calculateThroughput();
    void findAllPaths(int, int, int);
    int findThroughputForPath(vector<int>);
    void printOptimalPath(string, int, int);

};


#endif


