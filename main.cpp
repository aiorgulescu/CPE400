#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "MaxThroughput.h"

using namespace std;

int main() {

    MaxThroughput test(4, 200);

    test.printOptimalPath("network.txt", 0, 3);

    return 0;
}
