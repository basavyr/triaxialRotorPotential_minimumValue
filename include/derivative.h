// #ifndef POTENTIAL_HH
#define POTENTIAL_HH

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <string>
#include <utility>
#include <fstream>
#include <chrono>

//creating test functions for derivative calculations
class Functions
{
public:
    //create the function f(x)=x^2
    template <typename fType, typename argType>
    static fType power2(argType x)
    {
        auto result = static_cast<fType>(pow(x, 2));
        return result;
    }
    //create the function f(x)=a+sin(x)
    //the function has an additional argument besides x, which is a constant
    template <typename fType, typename argType>
    static fType sinx(argType x, argType a)
    {
        auto xDeg = static_cast<argType>(x * PI / 180.0);
        auto result = static_cast<fType>(a + sin(xDeg));
        return result;
    }
};

//one-sided differencing formulas
//forward differencing
class Forward_Differencing_Method
{
public:
    template <typename fName, typename fType>
    fType operator()(fName function, fType arg, fType step) const
    {
        return static_cast<fType>((function(arg + step) - function(arg)) / step);
    }
};

//one-sided differencing formulas
//backward differencing
class Backward_Differencing_Method
{
public:
    template <typename fName, typename fType>
    fType operator()(fName function, fType arg, fType step) const
    {
        return static_cast<fType>((function(arg) - function(arg - step)) / step);
    }
};

class Centered_Differencing_Method
{
public:
    template <typename fName, typename fType>
    fType operator()(fName function, fType arg, fType step) const
    {
        return static_cast<fType>((function(arg + step) - function(arg - step) / (2.0 * step)));
    }
};

class Richardson_Extrapolation_Method
{
public:
    template <typename fName, typename fType>
    fType operator()(fName function, fType arg, fType step) const
    {
        auto minus_fh = -function(arg + 2.0 * step);
        auto eight_fh = function(arg + step);
        auto minusEight_fh = -8.0 * function(arg - step);
        auto fh = function(arg - 2.0 * step);
        return static_cast<fType>(((minus_fh + eight_fh + minusEight_fh + fh) / (12.0 * step)));
    }
};

class Derivative
{
public:
    template <typename Function, typename FunctionType, typename Method>
    FunctionType calculateDerivative(Function function, FunctionType step, Method method, std::vector<FunctionType> &diffArray)
    {
        for (auto q = 0.0; q <= 8.0; q += step)
        {
            auto dVdq = method(function, q, step);
            diffArray.emplace_back(dVdq);
        }
    }
};

// #endif // POTENTIAL_HH