#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/MaxThroughput.hpp"

using namespace std;

int main()
{

    MaxThroughput simulation(4, 200);

    try
    {
        simulation.printOptimalPath("../data/network.txt", 0, 3);
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}
