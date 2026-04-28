#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <type_traits>

#include "common.h"

constexpr double AvoidDivideByZeroVecMath = 1e-160;

class vec3;

// 模板参数分别为：派生类 维度 数据类型
// CRTP基类
template <typename Derived, size_t N, typename T = double> class vec_crtp_base {
public:
  static constexpr size_t nDimensions = N;
  using value_type = T;

  vec_crtp_base() = default;

  T x() const {
    static_assert(N >= 1, "x() requires at least 1 dimension");
    return derived_const()[0];
  }
  T y() const {
    static_assert(N >= 2, "y() requires at least 2 dimensions");
    return derived_const()[1];
  }
  T z() const {
    static_assert(N >= 3, "z() requires at least 3 dimensions");
    return derived_const()[2];
  }

  T r() const { return x(); }
  T g() const { return y(); }
  T b() const { return z(); }

  T &x() {
    static_assert(N >= 1, "x() requires at least 1 dimension");
    return derived()[0];
  }
  T &y() {
    static_assert(N >= 2, "y() requires at least 2 dimensions");
    return derived()[1];
  }
  T &z() {
    static_assert(N >= 3, "z() requires at least 3 dimensions");
    return derived()[2];
  }

  T &r() { return x(); }
  T &g() { return y(); }
  T &b() { return z(); }

  T norm_square() const {
    T sum = T(0);
    for (size_t i = 0; i < N; ++i) {
      sum += derived_const()[i] * derived_const()[i];
    }
    return sum;
  }

  T norm() const { return std::sqrt(norm_square()); }

  bool nearZero() const {
    constexpr T epsilon = static_cast<T>(1e-8);
    for (size_t i = 0; i < N; ++i) {
      if (std::fabs(derived_const()[i]) >= epsilon) {
        return false;
      }
    }
    return true;
  }

  bool hasNaN() const {
    for (size_t i = 0; i < N; ++i) {
      if (std::isnan(derived_const()[i])) {
        return true;
      }
    }
    return false;
  }

  Derived operator-() const {
    Derived result;
    for (size_t i = 0; i < N; ++i) {
      result[i] = -derived_const()[i];
    }
    return result;
  }

  Derived &operator+=(const Derived &rhs) {
    for (size_t i = 0; i < N; ++i) {
      derived()[i] += rhs[i];
    }
    return derived();
  }

  Derived &operator*=(T factor) {
    for (size_t i = 0; i < N; ++i) {
      derived()[i] *= factor;
    }
    return derived();
  }

  Derived &operator/=(T divisor) { return (*this) *= (T(1) / divisor); }

  static Derived generate_random_vector() {
    Derived out;
    for (size_t i = 0; i < N; ++i) {
      out[i] = static_cast<T>(random_double());
    }
    return out;
  }

  static Derived generate_random_vector(T min, T max) {
    Derived out;
    for (size_t i = 0; i < N; ++i) {
      out[i] = static_cast<T>(random_double(min, max));
    }
    return out;
  }

private:
  Derived &derived() { return static_cast<Derived &>(*this); }
  const Derived &derived_const() const {
    return static_cast<const Derived &>(*this);
  }
};

template <size_t N, typename T = double>
class vec : public vec_crtp_base<vec<N, T>, N, T> {
public:
  vec() { element.fill(T(0)); }

  template <typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
  explicit vec(Args... args) : element{static_cast<T>(args)...} {}

  vec(std::initializer_list<T> init) {
    assert(init.size() == N);
    std::copy(init.begin(), init.end(), element.begin());
  }

  T operator[](size_t i) const {
    assert(i < N);
    return element[i];
  }

  T &operator[](size_t i) {
    assert(i < N);
    return element[i];
  }

private:
  std::array<T, N> element;
};

template <typename T> class vec<2, T> : public vec_crtp_base<vec<2, T>, 2, T> {
public:
  union {
    struct {
      T x;
      T y;
    };
    struct {
      T r;
      T g;
    };
    T element[2];
  };

  vec() : element{T(0), T(0)} {}
  vec(T _x, T _y) : element{_x, _y} {}

  T operator[](size_t i) const {
    assert(i < 2);
    return element[i];
  }

  T &operator[](size_t i) {
    assert(i < 2);
    return element[i];
  }
};

template <typename T> class vec<3, T> : public vec_crtp_base<vec<3, T>, 3, T> {
public:
  union {
    struct {
      T x;
      T y;
      T z;
    };
    struct {
      T r;
      T g;
      T b;
    };
    T element[3];
  };

  vec() : element{T(0), T(0), T(0)} {}
  vec(T _x, T _y, T _z) : element{_x, _y, _z} {}

  T operator[](size_t i) const {
    assert(i < 3);
    return element[i];
  }

  T &operator[](size_t i) {
    assert(i < 3);
    return element[i];
  }
};

template <size_t N, typename T>
std::ostream &operator<<(std::ostream &out, const vec<N, T> &v) {
  for (size_t i = 0; i < N; ++i) {
    if (i != 0) {
      out << ' ';
    }
    out << v[i];
  }
  return out;
}

template <size_t N, typename T>
vec<N, T> operator+(const vec<N, T> &a, const vec<N, T> &b) {
  vec<N, T> out;
  for (size_t i = 0; i < N; ++i) {
    out[i] = a[i] + b[i];
  }
  return out;
}

template <size_t N, typename T>
vec<N, T> operator-(const vec<N, T> &a, const vec<N, T> &b) {
  vec<N, T> out;
  for (size_t i = 0; i < N; ++i) {
    out[i] = a[i] - b[i];
  }
  return out;
}

template <size_t N, typename T>
vec<N, T> cwiseProduct(const vec<N, T> &a, const vec<N, T> &b) {
  vec<N, T> out;
  for (size_t i = 0; i < N; ++i) {
    out[i] = a[i] * b[i];
  }
  return out;
}

template <size_t N, typename T>
vec<N, T> operator*(T factor, const vec<N, T> &v) {
  vec<N, T> out;
  for (size_t i = 0; i < N; ++i) {
    out[i] = factor * v[i];
  }
  return out;
}

template <size_t N, typename T>
vec<N, T> operator*(const vec<N, T> &v, T factor) {
  return factor * v;
}

template <size_t N, typename T>
vec<N, T> operator/(const vec<N, T> &v, T divisor) {
  return (T(1) / divisor) * v;
}

template <size_t N, typename T>
T dotProduct(const vec<N, T> &a, const vec<N, T> &b) {
  T out = T(0);
  for (size_t i = 0; i < N; ++i) {
    out += a[i] * b[i];
  }
  return out;
}

template <size_t N, typename T>
T operator*(const vec<N, T> &a, const vec<N, T> &b) {
  return dotProduct(a, b);
}

template <typename T>
vec<3, T> crossProduct(const vec<3, T> &a, const vec<3, T> &b) {
  return vec<3, T>(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
                   a[0] * b[1] - a[1] * b[0]);
}

template <size_t N, typename T> vec<N, T> unit_vector(const vec<N, T> &v) {
  return v / v.norm();
}

template <typename T> vec<3, T> generate_random_diffused_unitVector() {
  while (true) {
    auto randomV = vec<3, T>::generate_random_vector(T(-1), T(1));
    T norm2 = randomV.norm_square();
    if (norm2 > static_cast<T>(AvoidDivideByZeroVecMath) && norm2 <= T(1)) {
      return randomV / std::sqrt(norm2);
    }
  }
}

template <size_t N, typename T> vec<N, T> generate_random_vector(T min, T max) {
  return vec<N, T>::generate_random_vector(min, max);
}

template <typename T>
vec<3, T>
generate_random_diffused_unitVector_onHemisphere(const vec<3, T> &normal) {
  auto randomV = generate_random_diffused_unitVector<T>();
  return (randomV * normal > T(0)) ? randomV : -randomV;
}

template <size_t N, typename T>
vec<N, T> project(const vec<N, T> &a, const vec<N, T> &ontoB) {
  return (a * ontoB / ontoB.norm_square()) * ontoB;
}

template <size_t N, typename T>
vec<N, T> reflect(const vec<N, T> &incidentRay, const vec<N, T> &normal) {
  return incidentRay - T(2) * project(incidentRay, normal);
}

template <typename T>
vec<3, T> refract(const vec<3, T> &incidentDirection, const vec<3, T> &normal,
                  T etaIncidentOverEtaRefract) {
  auto a = unit_vector(incidentDirection);
  auto n = unit_vector(normal);
  T cos_theta = std::fmin(-(a * n), T(1));

  auto refract_n_perpendicular =
      etaIncidentOverEtaRefract * (a + cos_theta * n);
  auto refract_n_parallel =
      -std::sqrt(std::fabs(T(1) - refract_n_perpendicular.norm_square())) * n;
  return refract_n_parallel + refract_n_perpendicular;
}

template <typename T> vec<3, T> random_cosine_direction() {
  // generate distribution: p(omega)=cos(theta)/pi
  T r1 = static_cast<T>(random_double());
  T r2 = static_cast<T>(random_double());

  T phi = T(2) * static_cast<T>(PI) * r1;
  T x = std::cos(phi) * std::sqrt(r2);
  T y = std::sin(phi) * std::sqrt(r2);
  T z = std::sqrt(T(1) - r2);

  return vec<3, T>(x, y, z);
}

template <typename T = double> using vec2 = vec<2, T>;
template <typename T = double> using vec3t = vec<3, T>;

template <typename T = double, size_t N = 3>
class Point : public vec_crtp_base<Point<T, N>, N, T> {
public:
  Point() { element.fill(T(0)); }

  template <typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
  explicit Point(Args... args) : element{static_cast<T>(args)...} {}

  Point(std::initializer_list<T> init) {
    assert(init.size() == N);
    std::copy(init.begin(), init.end(), element.begin());
  }

  T operator[](size_t i) const {
    assert(i < N);
    return element[i];
  }

  T &operator[](size_t i) {
    assert(i < N);
    return element[i];
  }

private:
  std::array<T, N> element;
};

template <typename T> class Point<T, 2> : public vec_crtp_base<Point<T, 2>, 2, T> {
public:
  union {
    struct {
      T x;
      T y;
    };
    struct {
      T r;
      T g;
    };
    T element[2];
  };

  Point() : element{T(0), T(0)} {}
  Point(T _x, T _y) : element{_x, _y} {}

  T operator[](size_t i) const {
    assert(i < 2);
    return element[i];
  }

  T &operator[](size_t i) {
    assert(i < 2);
    return element[i];
  }
};

template <typename T> class Point<T, 3> : public vec_crtp_base<Point<T, 3>, 3, T> {
public:
  union {
    struct {
      T x;
      T y;
      T z;
    };
    struct {
      T r;
      T g;
      T b;
    };
    T element[3];
  };

  Point() : element{T(0), T(0), T(0)} {}
  Point(T _x, T _y, T _z) : element{_x, _y, _z} {}
  Point(vec3 const &v);

  operator vec3() const;

  T operator[](size_t i) const {
    assert(i < 3);
    return element[i];
  }

  T &operator[](size_t i) {
    assert(i < 3);
    return element[i];
  }
};

// vec3是vec3t<double>，兼容问题就不改了
using vec2d = vec2<double>;
using vec2f = vec2<float>;
using vec2i = vec2<int>;
using vec3d = vec3t<double>;
using vec3f = vec3t<float>;
using vec3i = vec3t<int>;