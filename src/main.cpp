// #include <iostream>
// #include <cmath>
// #include <vector>
// #include <ctime>
// #include <string>
// #include <utility>
// #include <fstream>
// #include <chrono>

#include "../include/potential.h"
#include "../include/derivative.h"
#include "../include/minimum.h"

struct MinSetDetails
{
    double value;
    int index;
    void destroy()
    {
        value = 6969;
        index = 6969;
    }
};

void newline()
{
    std::cout << "\n";
}

float myfunction(float x)
{
    return static_cast<float>(pow(x, 2));
}

MinSetDetails rotorPotential(double theta)
{
    const double I = 45 / 2;
    const double I1 = 20;
    const double I2 = 40;
    const double I3 = 100;
    const double j = 5.5;
    const double h = 0.1;
    auto A1 = Potential::inertiaFactor(I1);
    auto A2 = Potential::inertiaFactor(I2);
    auto A3 = Potential::inertiaFactor(I3);
    std::vector<double> potentialStack;
    int errorChecker = 0;
    MinSetDetails result;
    for (double q = 0.0; q <= 8.0 && !errorChecker; q += h)
    {
        auto V = Potential::VRotor(q, I, j, A1, A2, A3, theta);
        if (V == 6969)
        {
            q = 100.0;
            errorChecker = 1;
            result.destroy();
        }
        else
        {
            potentialStack.emplace_back(V);
        }
    }
    if (errorChecker)
    {
        result.destroy();
    }
    Minimum minset(potentialStack);
    result.index = minset.minIndex;
    result.value = minset.minVal;
    return result;
}

void fileline(std::ofstream &gout)
{
    gout << "\n";
}

void mathPrint(std::vector<double> &xdata, std::vector<double> &array, std::vector<double> &positions)
{
    std::ofstream gout("../sources/out.dat");
    gout << "l1= { ";
    for (int i = 0; i < array.size(); ++i)
    {
        if (i == array.size() - 1)
        {
            gout << "{ " << xdata.at(i) << " , " << array.at(i) << "} };";
            fileline(gout);
        }
        else
        {
            gout << "{ " << xdata.at(i) << " , " << array.at(i) << "}, ";
        }
    }
    gout << "l2= { ";
    for (int i = 0; i < positions.size(); ++i)
    {
        if (i == positions.size() - 1)
        {
            gout << "{ " << xdata.at(i) << " , " << positions.at(i) << "} };";
            fileline(gout);
        }
        else
        {
            gout << "{ " << xdata.at(i) << " , " << positions.at(i) << "}, ";
        }
    }
}

void generatePotential(std::vector<double> &Qstack, std::vector<double> &Vstack, std::vector<double> &Posstack)
{
    for (double theta = -180.0; theta <= 180.0; theta += 1.0)
    {
        Qstack.emplace_back(theta);
        auto currentValue = rotorPotential(theta).value;
        auto currentIndex = rotorPotential(theta).index;
        if (theta == -90.0 || theta == 90.0)
            Vstack.emplace_back(0.0);
        else
        {
            if ((currentValue != 6969 && !isnan(currentValue)) && (currentIndex != 6969 && !isnan(currentIndex)))
            {
                Posstack.emplace_back(currentIndex);
                Vstack.emplace_back(currentValue);
            }
        }
    }
    if ((Vstack.size() != Qstack.size()) && (Qstack.size() != Posstack.size()))
        std::cout << "A IESIT O PULA CODUL"
                  << "\n";
}

int main()
{
    std::vector<double> potential;
    std::vector<double> angles;
    std::vector<double> minpositions;
    generatePotential(angles, potential, minpositions);
    // mathPrint(angles, potential);
    mathPrint(angles, potential, minpositions);

    // //test
    // std::vector<double> test = {10, 29, 30, 9};
    // Minimum testx(test);
    // std::cout << testx.minIndex << " " << testx.minVal;
}