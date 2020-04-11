#include <iostream>
// #include <cmath>
// #include <vector>
// #include <ctime>
#include <string>
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
void mathPrintToFile(std::ofstream &outstream, std::vector<T> &array)
{
    outstream << "f1= { ";
    for (auto id = 0; id < array.size(); ++id)
    {
        if (id == array.size() - 1)
        {
            outstream << array.at(id) << " };";
        }
        else
        {
            outstream << array.at(id) << " , ";
        }
    }
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

void writeToFile(std::ofstream &outstream, const std::string &name)
{
    outstream << name;
    outstream << "\n";
}

//check if the data is the same within an antisymmetric array iteration
template <typename T>
int sameData_antiSymmetric(std::vector<T> &v1, std::vector<T> &v2)
{
    if (!sameSize(v1, v2))
    {
        return 0;
    }
    // std::cout << "**************************"
    //           << "\n";
    // std::cout << "IN EQUALITY TEST"
    //           << "\n";

    //quantity for checking if the values are similar or not
    double safetyDelta = 0.0001;
    for (auto id = 0; id < v1.size(); ++id)
    {
        // std::cout << "in sameData_antiSymmetric FOR"<< "\n";
        auto reverseIdx = static_cast<int>(v1.size() - 1 - id);
        auto v1Elem = static_cast<double>(v1.at(id));
        auto v2Elem = static_cast<double>(v2.at(reverseIdx));

        // std::cout << "arrrays: " << v1.size() << " " << v2.size() << " " << reverseIdx << "\n";

        // std::cout << "elements of the arrays"<< "\n";
        // std::cout << v1Elem << " " << v2Elem << "\n";

        auto delta = static_cast<double>(abs(v2Elem - v1Elem));
        if (delta > safetyDelta)
        {
            // std::cout << "CATCH FOR DIFFERENT ELEMENTS" << '\n';
            return 0;
        }
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

    // std::cout << "in main rotor method for theta = " << theta << "\n";
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
        // std::cout << "in backwards for " << q<< "\n";
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
        // std::cout << "in forwards for " << q<< "\n";
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

    // std::cout << "BEFORE checking if the arrays are identical"<< "\n";
    int errorChecker = 1;
    if (!sameData_antiSymmetric(V_backwards, V_forwards))
    {
        errorChecker = 0;
        // std::cout << "POTENTIAL METHOD MUST STOP"<< "\n";
    }

    //if test passed then compute minimum of the Potential VRotor

    //hold the minimum value and the minimum position
    MinSetDetails result;

    // std::cout << "AFTER checking if the arrays are identical"<< "\n";
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
        // std::cout << "potential method indeed stopped"<< "\n";
    }
    return result;
    // std::cout << "end of potential method"<< "\n";
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
//         std::cout << "The algorithm did not finish with success"
//                   << "\n";
// }

//forward iteration for the minimum potential of V(q) as function of theta
MinSetDetails Debug_rotorPotential(double theta)
{
    const double I = 45.0 / 2.0;
    const double j = 11.0 / 2.0;
    const double h = 0.01;

    //define the value for the moments of inertia
    //the values are not associated to any of the principal axes
    //they just represent the triplet to be used in value assignment to each of the MOIs

    //*******************
    const double smallAxis = 20;
    const double intermediateAxis = 40;
    const double largeAxis = 100;

    double I1, I2, I3;
    enum Orderings
    {
        i1i2i3,
        i1i3i2,
        i2i1i3,
        i2i3i1,
        i3i1i2,
        i3i2i1
    };

    //****************************
    //select the ordering for the moments of inertia
    Orderings order = i2i3i1;
    //****************************

    std::cout << "The MOI ordering is:"
              << "\n";

    switch (order)
    {
    case i1i2i3:
        I1 = largeAxis;
        I2 = intermediateAxis;
        I3 = smallAxis;
        std::cout << "I1 > I2 > I3 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i1i3i2:
        I1 = largeAxis;
        I2 = smallAxis;
        I3 = intermediateAxis;
        std::cout << "I1 > I3 > I2 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i2i1i3:
        I1 = intermediateAxis;
        I2 = largeAxis;
        I3 = smallAxis;
        std::cout << "I2 > I1 > I3 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i2i3i1:
        I1 = smallAxis;
        I2 = largeAxis;
        I3 = intermediateAxis;
        std::cout << "I2 > I3 > I1 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i3i1i2:
        I1 = intermediateAxis;
        I2 = smallAxis;
        I3 = largeAxis;
        std::cout << "I3 > I1 > I2 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i3i2i1:
        I1 = smallAxis;
        I2 = intermediateAxis;
        I3 = largeAxis;
        std::cout << "I3 > I2 > I1 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;

    default:
        std::cout << "Selection for the MOIs ordering"
                  << "\n";
        break;
    }
    auto A1 = Potential::inertiaFactor(I1);
    auto A2 = Potential::inertiaFactor(I2);
    auto A3 = Potential::inertiaFactor(I3);

    std::cout << "The inertia factors are: A1= " << A1 << ", A2= " << A2 << ", A3= " << A3 << "\n";

    //VARIABLE FOR STORING THE RESULTS
    MinSetDetails result;

    std::vector<double> qTable;
    std::vector<double> vTable;
    std::vector<double> vTable_REAL_ONLY;
    std::cout << "Generating the potential"
              << "\n";
    int iteration = 0;
    for (double q = 0; q <= 8.0; q += h)
    {
        auto V = static_cast<double>(Potential::VRotor(q, I, j, A1, A2, A3, theta));
        // std::cout << iteration << " " << q << " " << V << "\n";
        qTable.emplace_back(q);
        vTable.emplace_back(V);
        iteration++;
        if (V != 6969)
            vTable_REAL_ONLY.emplace_back(V);
    }
    std::cout << "Generating potential has finished..."
              << "\n";
    std::cout << "Size of full potential is: " << vTable.size() << "\n";
    std::cout << "Size of the real potential is: " << vTable_REAL_ONLY.size() << "\n";
    //call the Minimum class to calculate the minimum of the array
    std::cout << "Initialize the Minimum class with the default constructor"
              << "\n";
    std::cout << "***************************\n";
    Minimum mininum(vTable_REAL_ONLY);
    std::cout << "Exit the Minimum class object"
              << "\n";
    std::cout << "***************************\n";
    if (mininum.okGo == 1)
    {
        std::cout << "The position of the minimum coincides with the index of the minimum value in array";
        newline();
    }

    std::ofstream gout;
    gout.open("../sources/potential.dat", std::ios::trunc);

    mathPrintToFile(gout, vTable_REAL_ONLY);
    result.V = mininum.minVal;
    result.minIdx = mininum.minIndex;
    result.q = qTable.at(mininum.minIndex);
    return result;
}

//backwards calculation of the minimum potential V(q) for comparison with the standard forwad iteration
MinSetDetails Debug_rotorPotential_Backwards(double theta)
{
    const double I = 45.0 / 2.0;
    const double j = 11.0 / 2.0;
    const double h = 0.1;

    //define the value for the moments of inertia
    //the values are not associated to any of the principal axes
    //they just represent the triplet to be used in value assignment to each of the MOIs

    //*******************
    const double smallAxis = 20;
    const double intermediateAxis = 40;
    const double largeAxis = 100;

    double I1, I2, I3;
    enum Orderings
    {
        i1i2i3,
        i1i3i2,
        i2i1i3,
        i2i3i1,
        i3i1i2,
        i3i2i1
    };

    //****************************
    //select the ordering for the moments of inertia
    Orderings order = i1i2i3;
    //****************************

    std::cout << "The MOI ordering is:"
              << "\n";

    switch (order)
    {
    case i1i2i3:
        I1 = largeAxis;
        I2 = intermediateAxis;
        I3 = smallAxis;
        std::cout << "I1 > I2 > I3 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i1i3i2:
        I1 = largeAxis;
        I2 = smallAxis;
        I3 = intermediateAxis;
        std::cout << "I1 > I3 > I2 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i2i1i3:
        I1 = intermediateAxis;
        I2 = largeAxis;
        I3 = smallAxis;
        std::cout << "I2 > I1 > I3 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i2i3i1:
        I1 = smallAxis;
        I2 = largeAxis;
        I3 = intermediateAxis;
        std::cout << "I2 > I3 > I1 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i3i1i2:
        I1 = intermediateAxis;
        I2 = smallAxis;
        I3 = largeAxis;
        std::cout << "I3 > I1 > I2 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;
    case i3i2i1:
        I1 = smallAxis;
        I2 = intermediateAxis;
        I3 = largeAxis;
        std::cout << "I3 > I2 > I1 => " << I1 << " " << I2 << " " << I3 << "\n";
        break;

    default:
        std::cout << "Selection for the MOIs ordering"
                  << "\n";
        break;
    }
    auto A1 = Potential::inertiaFactor(I1);
    auto A2 = Potential::inertiaFactor(I2);
    auto A3 = Potential::inertiaFactor(I3);

    std::cout << "The inertia factors are: A1= " << A1 << ", A2= " << A2 << ", A3= " << A3 << "\n";

    //VARIABLE FOR STORING THE RESULTS
    MinSetDetails result;

    std::vector<double> qTable_Backwards;
    std::vector<double> vTable_Backwards;
    std::vector<double> vTable_REAL_ONLY_Backwards;
    std::cout << "Generating the potential"
              << "\n";
    int iteration = 0;
    for (double q = -8; q <= 0.0; q += h)
    {
        auto V = static_cast<double>(Potential::VRotor(q, I, j, A1, A2, A3, theta));
        std::cout << iteration << " " << q << " " << V << "\n";
        qTable_Backwards.emplace_back(q);
        vTable_Backwards.emplace_back(V);
        iteration++;
        if (V != 6969)
            vTable_REAL_ONLY_Backwards.emplace_back(V);
    }
    std::cout << "Generating potential has finished..."
              << "\n";
    std::cout << "Size of full potential is: " << vTable_Backwards.size() << "\n";
    std::cout << "Size of the real potential is: " << vTable_REAL_ONLY_Backwards.size() << "\n";
    if (vTable_Backwards.size() == vTable_REAL_ONLY_Backwards.size())
        std::cout << "The MOIs ordering provides real values for V(q)"
                  << "\n";

    //call the Minimum class to calculate the minimum of the array
    std::cout << "Initialize the Minimum class with the default constructor"
              << "\n";
    std::cout << "***************************\n";
    Minimum mininum(vTable_REAL_ONLY_Backwards);
    std::cout << "Exit the Minimum class object"
              << "\n";
    std::cout << "***************************\n";
    if (mininum.okGo == 1)
    {
        std::cout << "The position of the minimum coincides with the index of the minimum value in array";
        newline();
    }

    std::ofstream gout;
    gout.open("../sources/potential.dat", std::ios::trunc);

    mathPrintToFile(gout, vTable_REAL_ONLY_Backwards);
    result.V = mininum.minVal;
    result.minIdx = mininum.minIndex;
    result.q = vTable_REAL_ONLY_Backwards.at(result.minIdx);
    return result;
}

void generateRotorPotential(std::vector<double> &qTable, std::vector<double> &thetaTable, std::vector<double> &vTable, std::vector<double> &IdxTable)
{
    for (double theta = -180.0; theta <= 180; theta += 1.0)
    {
        std::cout << "increased theta... " << theta << "\n";
        thetaTable.emplace_back(theta);
        // std::cout << "in array generator: BEFORE ROTOR METHOD"<< "\n";
        auto result = rotorPotential(theta);
        // std::cout << "in array generator: AFTER ROTOR METHOD"<< "\n";
        // if (result.V != 6969 && result.q != 6969 && result.minIdx != 6969)
        {
            // std::cout << "in array generator..." << theta << "\n";
            vTable.emplace_back(result.V);
            IdxTable.emplace_back(result.minIdx);
            qTable.emplace_back(result.q);
        }
    }
}

void fileSandbox(std::ofstream &gout)
{

    gout << "Started to write to the file"
         << "\n";
    gout << "End of stream of the 1ST Sandbox";
    gout << "\n";
}

void fileSandbox2(std::ofstream &gout)
{

    gout << "Started to write to the file"
         << "\n";
    gout << "End of stream of the 2ND Sandbox";
}

//generate the rotor potential within a blind-to-fail test

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

    // generateRotorPotential(qTable, thetaTable, vTable, IdxTable);
    auto x = Debug_rotorPotential(179);
    // mathPrint(thetaTable, vTable, qTable);

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
    //prepare the file to write the results on

    //solve the backwards potential
    // auto x = Debug_rotorPotential(180);
    // std::cout << "****************"<< "\n";
    // std::cout << "BACKWARD METHOD\n";
    // auto x = Debug_rotorPotential_Backwards(180);
    // std::cout << x.V;
    // std::cout << "\n";

    //solve the forwards potential
    std::cout << "****************"
              << "\n";
    std::cout << "FORWARD METHOD\n";
    auto y = Debug_rotorPotential(180);
    std::cout << y.V << " " << y.minIdx << " " << y.q << "\n";
    std::cout << "\n";
    std::cout << "****************"
              << "\n";

    std::vector<double> potential;
    std::vector<double> angles;
    std::vector<double> minpositions;
}