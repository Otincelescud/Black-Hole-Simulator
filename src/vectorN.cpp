#include "vectorN.h"

// Default constructor (zero vector)
template<typename T, std::size_t N> VectorN<T, N>::VectorN() = default;

// Constructor from initializer list
template<typename T, std::size_t N> VectorN<T, N>::VectorN(std::initializer_list<T> list) {
    if (list.size() != N)
        throw std::invalid_argument("Initializer list size does not match vector dimension.");
    std::copy(list.begin(), list.end(), data.begin());
}

// Access operator
template<typename T, std::size_t N> T& VectorN<T, N>::operator[](std::size_t idx) { return data[idx]; }
template<typename T, std::size_t N> const T& VectorN<T, N>::operator[](std::size_t idx) const { return data[idx]; }

// Addition
template<typename T, std::size_t N> VectorN<T, N> VectorN<T, N>::operator+(const VectorN<T, N>& other) const {
    VectorN result;
    for (std::size_t i = 0; i < N; ++i)
        result[i] = data[i] + other[i];
    return result;
}

// Subtraction
template<typename T, std::size_t N> VectorN<T, N> VectorN<T, N>::operator-(const VectorN<T, N>& other) const {
    VectorN result;
    for (std::size_t i = 0; i < N; ++i)
        result[i] = data[i] - other[i];
    return result;
}

// Scalar multiplication
template<typename T, std::size_t N> VectorN<T, N> VectorN<T, N>::operator*(T scalar) const {
    VectorN result;
    for (std::size_t i = 0; i < N; ++i)
        result[i] = data[i] * scalar;
    return result;
}

// Scalar division
template<typename T, std::size_t N> VectorN<T, N> VectorN<T, N>::operator/(T scalar) const {
    VectorN result;
    for (std::size_t i = 0; i < N; ++i)
        result[i] = data[i] / scalar;
    return result;
}

// Dot product
template<typename T, std::size_t N> T VectorN<T, N>::dot(const VectorN<T, N>& other) const {
    T result = T();
    for (std::size_t i = 0; i < N; ++i)
        result += data[i] * other[i];
    return result;
}

// Magnitude (Euclidean norm)
template<typename T, std::size_t N> T VectorN<T, N>::norm() const {
    return std::sqrt(this->dot(*this));
}

// Normalize
template<typename T, std::size_t N> VectorN<T, N> VectorN<T, N>::normalized() const {
    T n = norm();
    if (n == T())
        throw std::runtime_error("Cannot normalize zero vector.");
    return *this / n;
}

// Scalar multiplication from left
template<typename T, std::size_t N> VectorN<T, N> operator*(T scalar, const VectorN<T, N>& vec) {
    return vec * scalar;
}

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const VectorN<T, N>& vec) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << vec[i];
        if (i != N - 1) os << ", ";
    }
    os << "]";
    return os;
}

template class VectorN<float, 2>;
template class VectorN<float, 3>;
template VectorN<float, 2> operator*(float scalar, const VectorN<float, 2>& vec);
template VectorN<float, 3> operator*(float scalar, const VectorN<float, 3>& vec);
template std::ostream& operator<<(std::ostream& os, const VectorN<float, 2>& vec);
template std::ostream& operator<<(std::ostream& os, const VectorN<float, 3>& vec);