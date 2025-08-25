#ifndef UTILS_H
#define UTILS_H

#include "vectorN.h"

constexpr float pi = 3.14159265358979323846f;

// Polar to Cartesian conversion
VectorN<float, 2> polar_to_cartesian(const VectorN<float, 2>& polar, float w, float h);

// Cartesian to Polar conversion
VectorN<float, 2> cartesian_to_polar(const VectorN<float, 2>& cartesian, float w, float h);

#endif // UTILS_H