#include "utils.h"

// Polar to Cartesian conversion
VectorN<float, 2> polar_to_cartesian(const VectorN<float, 2>& polar, float w, float h) { return VectorN<float, 2>{polar[0]*w/(pi*2), polar[1]*h/pi}; }
VectorN<float, 2> cartesian_to_polar(const VectorN<float, 2>& cartesian, float w, float h) { return VectorN<float, 2>{cartesian[0]*(pi*2)/w, cartesian[1]*pi/h}; }

