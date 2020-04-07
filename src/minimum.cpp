#include "../include/minimum.h"

int Minimum::findMinimumPosition(std::vector<double> &source)
{
    auto first = source.begin();
    auto last = source.end();
    std::vector<double>::iterator index = std::min_element(first, last);
    auto result = std::distance(first, index);
    return static_cast<int>(result);
}

double Minimum::findMinimumValue(std::vector<double> &source)
{
    auto first = source.begin();
    auto last = source.end();
    auto minmaxPair = std::minmax_element(first, last);
    //minvalue is the first element
    auto minvalue = *minmaxPair.first;
    return minvalue;
}

int Minimum::checkConsistency(std::vector<double> &source)
{
    if (minVal == source.at(minIndex))
        return 1;
    return 0;
}