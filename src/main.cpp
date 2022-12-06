#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../include/MaxThroughput.hpp"

using namespace std;

int main()
{

    MaxThroughput simulation(4, 200);

    simulation.printOptimalPath("../data/network.txt", 0, 3);

    return 0;
}
