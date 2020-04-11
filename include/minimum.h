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
    double findMinimumValue_Debug(std::vector<double> &source);

public:
    Minimum(std::vector<double> &source)
    {
        std::cout << "In Minimum Class Constructor"
                  << "\n";

        //find the position of the minimum
        minIndex = findMinimumPosition(source);
        std::cout << "Index of the minimum element of the array=" << minIndex << "\n";

        //find the actual minimum
        minVal = findMinimumValue_Debug(source);
        std::cout << "Minimum value of the array= " << minVal << "\n";

        //check if the minimum was calculated correctly
        if (checkConsistency(source) == 1)
            okGo = 1;
        std::cout << "the OK_GO= " << okGo << "\n";
    }
};

#endif // MINIMUM_HH