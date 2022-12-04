#include "MaxThroughput.h"

MaxThroughput::MaxThroughput(int n, int bits){
    numNodes = n;
    totalBits = bits;
    visited = new bool[numNodes];
    path = new int[numNodes];

    for (int i = 0; i < numNodes; i++)
    {
        visited[i] = false;
    }
}

MaxThroughput::~MaxThroughput() {}

void MaxThroughput::loadData(string fileName) {
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

void MaxThroughput::calculateThroughput() {
    for (int i = 0; i < paths.size(); i++)
    {
       double delay = paths[i][3] * ((totalBits / paths[i][2]) - 1);

       double totalTimeToSendBits = (totalBits / paths[i][2]) + delay;

       double throughput = totalBits / totalTimeToSendBits;

       paths[i].push_back(int(throughput));

       adj[paths[i][0]][paths[i][1]] = paths[i][4];
       
    }
}

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

int MaxThroughput::findThroughputForPath(vector<int> path)
{
    int maxThroughput = INT32_MAX;

    for (int i = 0; i < path.size() - 1; i++ )
    {
        maxThroughput = min(maxThroughput, adj[path[i]][path[i+1]]);;
    }

    return maxThroughput;
}

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
            cout << ans[i] <<endl;
        }
        
    }
    cout << "Max throughput achieved: " << currMaxThroughput << " bits / second" << endl;
}