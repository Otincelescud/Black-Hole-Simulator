#ifndef VECTORN_H
#define VECTORN_H

#include <array>
#include <cmath>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <ostream>

template <typename T, std::size_t N>
class VectorN {
public:

    // Default constructor (zero vector)
    VectorN();

    // Constructor from initializer list
    VectorN(std::initializer_list<T> list);

    // Access operator
    T& operator[](std::size_t idx);
    const T& operator[](std::size_t idx) const;

    // Addition
    VectorN operator+(const VectorN& other) const;

    // Subtraction
    VectorN operator-(const VectorN& other) const;

    // Scalar multiplication
    VectorN operator*(T scalar) const;

    // Scalar division
    VectorN operator/(T scalar) const;

    // Dot product
    T dot(const VectorN& other) const;

    // Magnitude (Euclidean norm)
    T norm() const;

    // Normalize
    VectorN normalized() const;

private:
    std::array<T, N> data{};
};

// Scalar multiplication from left
template <typename T, std::size_t N>
VectorN<T, N> operator*(T scalar, const VectorN<T, N>& vec);


template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const VectorN<T, N>& vec);

#endif // VECTORN_H