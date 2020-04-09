#include "../include/minimum.h"

int Minimum::findMinimumPosition(std::vector<double> &source)
{
    std::cout << "entered in the minimum position method"
              << "\n";
    auto first = source.begin();
    auto last = source.end();
    std::vector<double>::iterator index = std::min_element(first, last);
    auto result = std::distance(first, index);
    std::cout << "exit from the minimum position method OK"
              << "\n";
    std::cout << "the result return by the position minimum is" << result << "\n;";
    return static_cast<int>(result);
}

double Minimum::findMinimumValue(std::vector<double> &source)
{
    std::cout << "ENTER in the minimum value finder method "
              << "\n";
    std::cout << "size of array is" << source.size() << "\n";
    if (source.size() == 0)
    {
        std::cout << "the array is empty so the size is increased by one for safety measure";
        source.emplace_back(6969);
    }
    auto first = source.begin();
    std::cout << "passed"
              << "\n ";
    auto last = source.end();
    std::cout << "passed"
              << "\n ";
    auto minmaxPair = std::minmax_element(first, last);
    std::cout << "passed"
              << "\n ";
    //minvalue is the first element
    auto minvalue = *minmaxPair.first;
    std::cout << "passed"
              << "\n ";
    // std::cout << "the result return by the minimum value finder is" << minvalue << "\n;";
    std::cout << "exit from the minimum value finder method OK"
              << "\n";
    return 1;
}

int Minimum::checkConsistency(std::vector<double> &source)
{
    if (minVal == source.at(minIndex))
    {
        std::cout << "CHECK THE CONSISTENCY in the minimum class"
                  << "\n";
        return 1;
    }
    return 0;
}