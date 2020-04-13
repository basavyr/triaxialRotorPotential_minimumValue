#include "../include/minimum.h"

int Minimum::findMinimumPosition(std::vector<double> &source)
{
    // std::cout << "entered in the minimum position method"<< "\n";
    auto first = source.begin();
    auto last = source.end();
    std::vector<double>::iterator index = std::min_element(first, last);
    auto result = std::distance(first, index);
    // std::cout << "exit from the minimum position method OK"<< "\n";
    // std::cout << "the result return by the position minimum is" << result << "\n;";
    return static_cast<int>(result);
}

double Minimum::findMinimumValue_Debug(std::vector<double> &source)
{
    auto maxval = 98765432100.123;
    if (source.size())
    {
        //local minimum for finding the array min value
        for (auto id = 0; id < source.size(); ++id)
        {
            if (source.at(id) <= maxval)
            {
                maxval = source.at(id);
            }
        }
    }
    return maxval;
}

double Minimum::findMinimumValue(std::vector<double> &source)
{
    std::cout << "ENTER in the minimum value finder method "
              << "\n";
    std::cout << "Size of array is " << source.size() << "\n";
    if (source.size() == 0)
    {
        std::cout << "The array is empty so the size is increased by one for safety measure"
                  << "\n";
        source.emplace_back(6969);
    }
    auto first = source.begin();
    // std::cout << "passed"
    //           << "\n ";
    auto last = source.end();
    // std::cout << "passed"
    //           << "\n ";
    // std::cout << "passed"
    //           << "\n ";
    //minvalue is the first element
    auto minmaxPair = std::minmax_element(first, last);
    auto minvalue = *minmaxPair.first;
    std::cout << "The result returned by the minimum value finder is " << minvalue << "\n";
    std::cout << "Exit from the minimum value finder method OK"
              << "\n";
    return minvalue;
}

int Minimum::checkConsistency(std::vector<double> &source)
{
    if (source.size())
    {
        std::cout << "Constructor is checking the consistency of the object"
                  << "\n";
        if (minVal == source.at(minIndex))
        {
            std::cout << "Consistency was checked with status 1"
                      << "\n";
            std::cout << "Minimum is " << minVal << " and the element at position idx= " << minIndex << ", is = " << source.at(minIndex) << "\n";
            std::cout << "Checking if the positions in the arrays are ok"
                      << "\n";
            //backwards
            auto q_Calculated_Back = -8.0 + minIndex * 0.1;
            //forwards
            auto q_Calculated_Forwards = 0.0 + minIndex * 0.01;
            // std::cout << "calculated q from position of minIdx is " << q_Calculated_Back << "\n";
            std::cout << "calculated q from position of minIdx is" << q_Calculated_Forwards << "\n";
            return 1;
        }
    }
    else
    {
        std::cout << "Array is empty, so no minimum calculations can be made by the class...";
        std::cout << "\n";
    }
    return 0;
}