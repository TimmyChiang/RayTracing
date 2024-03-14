#ifndef MATH_CONST_H
#define MATH_CONST_H

#include <cmath>
#include <limits>

const double INF = std::numeric_limits<double>::infinity();
const double PI = acos(-1.0);

inline double degree_to_radius(double degrees) {
    return degrees * PI / 180.0;
}

#endif