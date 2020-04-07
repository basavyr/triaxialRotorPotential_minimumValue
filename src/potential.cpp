#include "../include/potential.h"

double Potential::AFct(double spin, double oddSpin, double a1, double a2, double theta)
{
    auto j2_Component = oddSpin * sin(theta * PI / 180.0);
    auto result = a2 * (1.0 - j2_Component / spin) - a1;
    if (!isnan(result))
        return result;
    return 6969;
}

double Potential::uFct(double spin, double oddSpin, double a1, double a2, double a3, double theta)
{
    auto result = static_cast<double>((a3 - a1) / AFct(spin, oddSpin, a1, a2, theta));
    if (!isnan(result))
        return result;
    return 6969;
}

double Potential::v0Fct(double spin, double oddSpin, double a1, double a2, double theta)
{
    auto j1_Component = oddSpin * cos(theta * PI / 180.0);
    auto result = -1.0 * static_cast<double>((a1 * j1_Component) / AFct(spin, oddSpin, a1, a2, theta));
    if (!isnan(result))
        return result;
    return 6969;
}

double Potential::kFct(double spin, double oddSpin, double a1, double a2, double a3, double theta)
{
    auto result = sqrt(Potential::uFct(spin, oddSpin, a1, a2, a3, theta));
    if (!isnan(result))
        return result;
    return 6969;
}

double Potential::VRotor(double q, double spin, double oddSpin, double a1, double a2, double a3, double theta)
{
    auto I = spin;
    auto k = Potential::kFct(I, oddSpin, a1, a2, a3, theta);
    if (k == 6969)
        return 6969;
    auto v0 = Potential::v0Fct(I, oddSpin, a1, a2, theta);
    if (v0 == 6969)
        return 6969;
    auto JA = jacobiAmplitude(q, k);
    auto RotorPotential = (I * (I + 1.0) * pow(k, 2) + pow(v0, 2)) * pow(JA.sn, 2) + (2.0 * I + 1.0) * v0 * JA.cn * JA.dn;
    if (!isnan(RotorPotential))
        return RotorPotential;
    return 6969;
}

//Calculate the elliptic variables via boost library
//Compute the JacobiAmplitude and then find sn,cn,dn
Potential::EllipticVariables Potential::jacobiAmplitude(double q, double k)
{
    auto result = new Potential::EllipticVariables;
    //the variable q is on the second spot
    //the complex number k  (constant) is the first argument
    result->sn = boost::math::jacobi_sn(k, q);
    result->cn = boost::math::jacobi_cn(k, q);
    result->dn = boost::math::jacobi_dn(k, q);
    if (!isnan(result->sn) && !isnan(result->cn) && !isnan(result->dn))
        return *result;
    result->destroy();
    return *result;
}