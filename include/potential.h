#ifndef POTENTIAL_HH
#define POTENTIAL_HH

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <string>
#include <utility>
#include <fstream>
#include <chrono>
#include "boost/math/special_functions/jacobi_elliptic.hpp"

#define PI 3.141592654

class Potential
{
public:
    struct EllipticVariables
    {
        double sn;
        double cn;
        double dn;
        void destroy()
        {
            sn = 6969;
            cn = 6969;
            dn = 6969;
        }
        void print()
        {
            std::cout << sn << " " << cn << " " << dn << "\n";
        }
    };
    static EllipticVariables jacobiAmplitude(double q, double k);

public:
    static double inertiaFactor(double I)
    {
        return static_cast<double>(1.0 / (2.0 * I));
    }
    static double couplingFactor(int k, double th, double j)
    {
        if (k == 1)
            return j * cos(th * PI / 180.0);
        return j * sin(th * PI / 180.0);
    }
    static double AFct(double spin, double oddSpin, double a1, double a2, double theta);
    static double uFct(double spin, double oddSpin, double a1, double a2, double a3, double theta);
    static double kFct(double spin, double oddSpin, double a1, double a2, double a3, double theta);
    static double v0Fct(double spin, double oddspin, double a1, double a2, double theta);
    static double VRotor(double q, double spin, double oddSpin, double a1, double a2, double a3, double theta);
};
#endif // POTENTIAL_HH