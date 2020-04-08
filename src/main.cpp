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
    double V;
    double q;
    int minIdx;
    void destroy()
    {
        V = 6969;
        minIdx = 6969;
        q = 6969;
    }
};

void newline()
{
    std::cout << "\n";
}

void fileline(std::ofstream &gout)
{
    gout << "\n";
}

template <typename T>
void arrayPrint(std::vector<T> &v)
{
    for (auto id = 0; id < v.size(); id++)
    {
        std::cout << v.at(id) << " , ";
    }
    newline();
}

template <typename T>
int sameSize(std::vector<T> &v1, std::vector<T> &v2)
{
    size_t size1 = v1.size();
    size_t size2 = v2.size();
    if (size1 == size2)
        return 1;
    return 0;
}

//check if the data is the same within a symmetric array
template <typename T>
int sameData(std::vector<T> &v1, std::vector<T> &v2)
{
    if (!sameSize(v1, v2))
        return 0;
    for (auto id = 0; id < v1.size(); id++)
    {
        if (v1.at(id) != v2.at(id))
            return 0;
    }
    return 1;
}

//check if the data is the same within an antisymmetric array iteration
template <typename T>
int sameData_antiSymmetric(std::vector<T> &v1, std::vector<T> &v2)
{
    if (!sameSize(v1, v2))
        return 0;
    // std::cout << "**************************"
    //           << "\n";
    // std::cout << "IN EQUALITY TEST"
    //           << "\n";

    //quantity for checking if the values are similar or not
    double safetyDelta = 0.0001;
    for (auto id = 0; id < v1.size(); ++id)
    {
        auto reverseIdx = static_cast<int>(v1.size() - 1 - id);
        auto v1Elem = static_cast<double>(v1.at(id));
        auto v2Elem = static_cast<double>(v2.at(reverseIdx));
        auto delta = static_cast<double>(abs(v2Elem - v1Elem));
        if (delta > safetyDelta)
            return 0;
        // std::cout << id << " " << v1Elem << " " << v2Elem << " " << delta << "\n";
        // if (v1Elem == v2Elem)
        // return 0;
    }
    // std::cout << "**************************"
    //   << "\n";
    return 1;
}

//must return the minimum
MinSetDetails rotorPotential(double theta)
{
    //*******************************
    //build the MOI ordering
    const double I1 = 20;
    const double I2 = 20;
    const double I3 = 100;
    //*******************************

    //the constants for use in the potential calculations
    const double I = 45 / 2;
    const double j = 5.5;
    const double h = 0.1;
    auto A1 = Potential::inertiaFactor(I1);
    auto A2 = Potential::inertiaFactor(I2);
    auto A3 = Potential::inertiaFactor(I3);

    //build the backwards and forwards arrays
    std::vector<double> V_backwards;
    std::vector<double> V_forwards;
    //containers for storing the qvalues
    std::vector<double> q_backwards;
    std::vector<double> q_forwards;

    //check if the code is running correctly and all the real values are inserted into the arrays

    //backwards approach
    for (double q = -8.0; q <= 0.0; q += h)
    {
        q_backwards.emplace_back(q);
        auto back_V = Potential::VRotor(q, I, j, A1, A2, A3, theta);
        if (back_V != 6969)
        {
            V_backwards.emplace_back(back_V);
        }
    }

    //forwards approach
    for (double q = 0.0; q <= 8.0; q += h)
    {
        q_forwards.emplace_back(q);
        auto forwardV = Potential::VRotor(q, I, j, A1, A2, A3, theta);
        if (forwardV != 6969)
        {
            V_forwards.emplace_back(forwardV);
        }
    }
    // newline();
    // arrayPrint<double>(V_forwards);
    // arrayPrint<double>(V_backwards);
    // for (int id = 0; id < V_backwards.size(); ++id)
    // {
    //     auto v1Elem = V_backwards.at(id);
    //     auto v2Elem = V_forwards.at(static_cast<int>(V_backwards.size() - 1 - id));
    //     auto deltav2v1 = static_cast<double>(v2Elem - v1Elem);
    //     // std::cout << id << " " << V_backwards.at(id) << " " << V_forwards.at(static_cast<int>(V_backwards.size() - 1 - id)) << "\n";
    //     // std::cout << id << " " << v1Elem << " " << v2Elem << " " << deltav2v1 << "\n";
    // }
    //check if the arrays are consistent

    int errorChecker = 1;
    if (!sameData_antiSymmetric(V_backwards, V_forwards))
        errorChecker = 0;

    //if test passed then compute minimum of the Potential VRotor

    //hold the minimum value and the minimum position
    MinSetDetails result;

    Minimum minimum(V_forwards);
    if (minimum.okGo == 1 && errorChecker)
    {
        result.V = minimum.minVal;
        result.minIdx = minimum.minIndex;
        result.q = q_forwards.at(static_cast<int>(minimum.minIndex));
    }
    else
    {
        result.destroy();
    }
    return result;
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
    // gout << "l2= { ";
    // for (int i = 0; i < positions.size(); ++i)
    // {
    //     if (i == positions.size() - 1)
    //     {
    //         gout << "{ " << xdata.at(i) << " , " << positions.at(i) << "} };";
    //         fileline(gout);
    //     }
    //     else
    //     {
    //         gout << "{ " << xdata.at(i) << " , " << positions.at(i) << "}, ";
    //     }
    // }
}

// void generatePotential(std::vector<double> &Qstack, std::vector<double> &Vstack, std::vector<double> &Posstack)
// {
//     for (double theta = -180.0; theta <= 180.0; theta += 1.0)
//     {
//         Qstack.emplace_back(theta);
//         auto currentValue = rotorPotential(theta).value;
//         auto currentIndex = rotorPotential(theta).index;
//         if (theta == -90.0 || theta == 90.0)
//             Vstack.emplace_back(0.0);
//         else
//         {
//             if ((currentValue != 6969 && !isnan(currentValue)) && (currentIndex != 6969 && !isnan(currentIndex)))
//             {
//                 Posstack.emplace_back(currentIndex);
//                 Vstack.emplace_back(currentValue);
//             }
//         }
//     }
//     if ((Vstack.size() != Qstack.size()) && (Qstack.size() != Posstack.size()))
//         std::cout << "A IESIT O PULA CODUL"
//                   << "\n";
// }

void generateRotorPotential(std::vector<double> &qTable, std::vector<double> &thetaTable, std::vector<double> &vTable, std::vector<double> &IdxTable)
{
    for (double theta = -180.0; theta <= 180; theta += 1.0)
    {
        thetaTable.emplace_back(theta);
        auto result = rotorPotential(theta);
        if (result.V != 6969 && result.q != 6969 && result.minIdx != 6969)
        {
            vTable.emplace_back(result.V);
            IdxTable.emplace_back(result.minIdx);
            qTable.emplace_back(result.q);
        }
    }
}

void sandbox()
{
    // std::vector<int> v1 = {1, 3, 4, 5, 6};
    // std::vector<int> v2 = {1, 3, 4, 5, 6, 7};
    // auto x = sameSize(v1, v2);
    // auto y = sameData(v1, v2);
    // std::cout << x << " " << y << "\n";

    std::vector<double> qTable;
    std::vector<double> IdxTable;
    std::vector<double> vTable;
    std::vector<double> thetaTable;

    generateRotorPotential(qTable, thetaTable, vTable, IdxTable);
    if (sameSize(thetaTable, vTable))
        std::cout << "all good";
    newline();
    mathPrint(thetaTable, vTable, qTable);

    // std::vector<double> a, b;
    // for (int i = 0; i <= 11; ++i)
    // {
    //     a.emplace_back(i);
    //     b.emplace_back(i);
    // }
    // int p = b.size() - 1;
    // for (std::vector<double>::iterator it = b.begin(); it < b.end(); ++it)
    // {
    //     *it = p--;
    // }
    // for (int id = 0; id < a.size(); ++id)
    // {
    //     std::cout << a.at(id) << " " << b.at(a.size() - 1 - id) << "\n";
    // }
    // std::cout << sameData_antiSymmetric(a, b);
    // newline();
}

int main()
{
    std::vector<double> potential;
    std::vector<double> angles;
    std::vector<double> minpositions;
    sandbox();
}