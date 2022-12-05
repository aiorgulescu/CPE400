#include "MaxThroughput.hpp"

using namespace std;

/*
Constructor for the class. Initialize all the class members.
@param n Number of nodes
@param biss Number of bits
@return Nothing
*/
MaxThroughput::MaxThroughput(int n, int bits)
{
    numNodes = n;
    totalBits = bits;
    visited = new bool[numNodes];
    path = new int[numNodes];

    for (int i = 0; i < numNodes; i++)
    {
        visited[i] = false;
    }
}
/*
Destructor
@return Nothing
*/
MaxThroughput::~MaxThroughput() {}
/*
Load the file data that contains the adjacency matrix and other network data
@param fileName The name of the file to load
@return Nothing
*/
void MaxThroughput::loadData(string fileName)
{
    ifstream myFile(fileName);

    string line;

    if (!myFile)
    {
        cout << "Error opening file" << endl;
        return;
    }

    int vertA, vertB, bandwidth, queueDelay;

    while (!myFile.eof())
    {

        getline(myFile, line);
        if (myFile >> vertA >> vertB >> bandwidth >> queueDelay)
        {
            vector<int> currLine{vertA, vertB, bandwidth, queueDelay};
            paths.push_back(currLine);
        }
    }

    myFile.close();
}
/*
This function calculates the max throughput for the given network
@return Nothing
*/
void MaxThroughput::calculateThroughput()
{
    for (int i = 0; i < paths.size(); i++)
    {
        double delay = paths[i][3] * ((totalBits / paths[i][2]) - 1);

        double totalTimeToSendBits = (totalBits / paths[i][2]) + delay;

        double throughput = totalBits / totalTimeToSendBits;

        paths[i].push_back(int(throughput));

        adj[paths[i][0]][paths[i][1]] = paths[i][4];
    }
}
/*
Traverses the network of nodes and finds all the paths using breadth first search
@param src The source node to begin searching from
@param dest The destination node that we want to reach
@param index The current position in the network
@return Nothing
*/
void MaxThroughput::findAllPaths(int src, int dest, int index)
{
    visited[src] = true;
    path[index] = src;
    index++;

    if (src == dest)
    {
        vector<int> currPath;
        for (int i = 0; i < index; i++)
        {
            currPath.push_back(path[i]);
        }
        allPossiblePaths.push_back(currPath);
    }
    else
    {
        for (int i = 0; i < numNodes; i++)
        {
            if (!visited[i] && adj[src][i] > 0)
            {
                findAllPaths(i, dest, index);
            }
        }
    }

    index--;
    visited[src] = false;
}
/*
For a given path, find the throughput of the network on that path
@param path A vector of integers containing the nodes along the path
@reuturn int The throughput value of the path
*/
int MaxThroughput::findThroughputForPath(vector<int> path)
{
    int maxThroughput = INT32_MAX;

    for (int i = 0; i < path.size() - 1; i++)
    {
        maxThroughput = min(maxThroughput, adj[path[i]][path[i + 1]]);
        ;
    }

    return maxThroughput;
}
/*
Computes the optimal path for the network given the calculated throughput/path values. It then
prints the optimal path from source to destination node and max throughput.
@param fileName The name of the file for the network
@param src The source node to start from
@param dest The destination node to reach
@return Nothing
*/
void MaxThroughput::printOptimalPath(string fileName, int src, int dest)
{
    loadData(fileName);
    calculateThroughput();
    findAllPaths(src, dest, 0);

    vector<int> ans = allPossiblePaths[0];
    int currMaxThroughput = 0;

    for (int i = 0; i < allPossiblePaths.size(); i++)
    {
        int currThroughput = findThroughputForPath(allPossiblePaths[i]);

        if (currMaxThroughput < currThroughput)
        {
            currMaxThroughput = currThroughput;
            ans = allPossiblePaths[i];
        }
    }

    cout << "Optimal path to reach router " << dest << " from router " << src << ":" << endl;

    for (int i = 0; i < ans.size(); i++)
    {
        if (i != ans.size() - 1)
        {
            cout << ans[i] << " -> ";
        }
        else
        {
            cout << ans[i] << endl;
        }
    }
    cout << "Max throughput achieved: " << currMaxThroughput << " bits / second" << endl;
}