#ifndef VEC3_H
#define VEC3_H

#include "common.h"
#include "vec_math.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>

double constexpr AvoidDivideByZero = 1e-160;
class vec3 {
public:
  union {
    struct {
      double x;
      double y;
      double z;
    };
    struct {
      double r;
      double g;
      double b;
    };
    double element[3];
  };
  vec3() : element{0.0, 0.0, 0.0} {};
  vec3(double _x, double _y, double _z) : element{_x, _y, _z} {};

  double norm() const { return vec<3, double>(x, y, z).norm(); };
  double norm_square() const { return vec<3, double>(x, y, z).norm_square(); }

  bool nearZero() { return vec<3, double>(x, y, z).nearZero(); }

  static vec3 generate_random_vector() { // 生成[0,1]^3空间内的随机向量
    auto v = vec3d::generate_random_vector();
    return vec3(v[0], v[1], v[2]);
  }
  static vec3 generate_random_vector(double min, double max) {
    auto v = vec3d::generate_random_vector(min, max);
    return vec3(v[0], v[1], v[2]);
  }
  static vec3 generate_random_vector_onUnitDisk() {
    while (true) {
      auto genericRandom = vec3d::generate_random_vector(-1.0, 1.0);
      vec3 randomVector(genericRandom[0], genericRandom[1], genericRandom[2]);
      if (randomVector.norm_square() <= 1.0)
        return randomVector;
    }
  }

  double operator[](int ith_element) const {
    assert(0 <= ith_element && ith_element <= 2);
    return element[ith_element];
  }
  double &operator[](int ith_element) {
    assert(0 <= ith_element && ith_element <= 2);
    return element[ith_element];
  }

  vec3 operator-() const {
    auto v = -vec3d(x, y, z);
    return vec3(v[0], v[1], v[2]);
  }

  vec3 &operator+=(vec3 const &vectorToAdd) {
    auto sum = vec3d(x, y, z) + vec3d(vectorToAdd.x, vectorToAdd.y, vectorToAdd.z);
    x = sum[0];
    y = sum[1];
    z = sum[2];
    return *this;
  }

  vec3 &operator*=(double factor) {
    auto scaled = vec3d(x, y, z) * factor;
    x = scaled[0];
    y = scaled[1];
    z = scaled[2];
    return *this;
  }

  vec3 &operator/=(double divisor) {
    auto divided = vec3d(x, y, z) / divisor;
    x = divided[0];
    y = divided[1];
    z = divided[2];
    return *this;
  }

  // debug
  bool hasNaN() const { return vec3d(x, y, z).hasNaN(); }
};

namespace vec3_detail {
using generic_vec3 = vec3d;

inline generic_vec3 to_generic(vec3 const &v) {
  return generic_vec3(v.x, v.y, v.z);
}

inline vec3 from_generic(generic_vec3 const &v) {
  return vec3(v[0], v[1], v[2]);
}
} // namespace vec3_detail

using point3 = Point<double, 3>;

inline Point<double, 3>::Point(vec3 const &v) : element{v.x, v.y, v.z} {}

inline Point<double, 3>::operator vec3() const { return vec3(x, y, z); }

std::ostream &operator<<(std::ostream &out, vec3 const &vector) {
  out << vec3_detail::to_generic(vector);
  return out;
}

vec3 operator+(vec3 const &leftVector, vec3 const &rightVector) {
  return vec3_detail::from_generic(vec3_detail::to_generic(leftVector) +
                                   vec3_detail::to_generic(rightVector));
}

vec3 operator-(vec3 const &leftVector, vec3 const &rightVector) {
  return vec3_detail::from_generic(vec3_detail::to_generic(leftVector) -
                                   vec3_detail::to_generic(rightVector));
}

vec3 cwiseProduct(vec3 const &leftVector, vec3 const &rightVector) {
  return vec3_detail::from_generic(cwiseProduct(vec3_detail::to_generic(leftVector),
                                                vec3_detail::to_generic(rightVector)));
}

vec3 operator*(double factor, vec3 const &vector) {
  return vec3_detail::from_generic(factor * vec3_detail::to_generic(vector));
}

vec3 operator*(vec3 const &vector, double factor) { return factor * vector; }

vec3 operator/(vec3 const &vector, double divisor) {
  return (1 / divisor) * vector;
}

double dotProduct(vec3 const &leftVector, vec3 const &rightVector) {
  return dotProduct(vec3_detail::to_generic(leftVector),
                    vec3_detail::to_generic(rightVector));
}

double operator*(vec3 const &leftVector, vec3 const &rightVector) {
  return dotProduct(leftVector, rightVector);
}

vec3 crossProduct(vec3 const &leftVector, vec3 const &rightVector) {
  return vec3_detail::from_generic(
      crossProduct(vec3_detail::to_generic(leftVector),
                   vec3_detail::to_generic(rightVector)));
}

vec3 unit_vector(vec3 const &vector) {
  return vec3_detail::from_generic(unit_vector(vec3_detail::to_generic(vector)));
}

vec3 generate_random_diffused_unitVector() {
  return vec3_detail::from_generic(generate_random_diffused_unitVector<double>());
}

vec3 generate_random_vector(double min, double max) {
  return vec3_detail::from_generic(generate_random_vector<3, double>(min, max));
}

vec3 generate_random_diffused_unitVector_onHemisphere(
    vec3 const &normalAgainstRay) {
  return vec3_detail::from_generic(generate_random_diffused_unitVector_onHemisphere(
      vec3_detail::to_generic(normalAgainstRay)));
}

vec3 project(vec3 const &a, vec3 const &ontoB) {
  return vec3_detail::from_generic(
      project(vec3_detail::to_generic(a), vec3_detail::to_generic(ontoB)));
}

vec3 reflect(vec3 const &incidentRay, vec3 const &normal) {
  return vec3_detail::from_generic(
      reflect(vec3_detail::to_generic(incidentRay), vec3_detail::to_generic(normal)));
}

vec3 refract(vec3 const &incidentDirection, vec3 const &normal,
             double etaIncidentOverEtaRefract) {
  return vec3_detail::from_generic(refract(vec3_detail::to_generic(incidentDirection),
                                           vec3_detail::to_generic(normal),
                                           etaIncidentOverEtaRefract));
}

vec3 random_cosine_direction() {
  return vec3_detail::from_generic(random_cosine_direction<double>());
}

#endif