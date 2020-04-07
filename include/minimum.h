#ifndef MINIMUM_HH
#define MINIMUM_HH

#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <ctime>
#include <string>
#include <utility>
#include <fstream>
#include <chrono>
#include <algorithm>

class Minimum
{
public:
    double minVal;
    int minIndex;
    double okGo = 0;
    //gets the index of the minimum element of an array
    int findMinimumPosition(std::vector<double> &source);
    //gets the  minimum element of an array
    double findMinimumValue(std::vector<double> &source);
    //checks if the two methods are working as intended
    int checkConsistency(std::vector<double> &source);

public:
    Minimum(std::vector<double> &source)
    {
        minIndex = findMinimumPosition(source);
        minVal = findMinimumValue(source);
        if (checkConsistency(source) == 1)
            okGo = 1;
    }
};

#endif // MINIMUM_HH