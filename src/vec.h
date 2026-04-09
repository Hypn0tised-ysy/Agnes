#pragma once

#include <cassert>
#include <cmath>
#include <ostream>
class vec3 {
public:
  union {
    struct {
      double x, y, z;
    };
    struct {
      double r, g, b;
    };
    struct {
      double u, v, w;
    };
    double data[3];
  };

  vec3() : x(0), y(0), z(0) {}
  vec3(double x, double y, double z) : x(x), y(y), z(z) {}

  bool is_index_valid(int index) const { return index >= 0 && index < 3; }

  double operator[](int index) const {
    assert(is_index_valid(index));
    return data[index];
  }
  double &operator[](int index) {
    assert(is_index_valid(index));
    return data[index];
  }

  void operator+=(const vec3 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
  }

  void operator-=(const vec3 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
  }

  void operator*=(double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
  }

  void operator/=(double scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
  }

  double length() const { return std::sqrt(x * x + y * y + z * z); }
  double length_squared() const { return x * x + y * y + z * z; }
};

using point3 = vec3;

inline vec3 operator+(const vec3 &a, const vec3 &b) {
  return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline vec3 operator-(const vec3 &a, const vec3 &b) {
  return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline std::ostream &operator<<(std::ostream &os, const vec3 &v) {
  os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")\n";
  return os;
}

// 不重载*防止歧义
inline vec3 cwise_product(const vec3 &a, const vec3 &b) {
  return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline vec3 cross_product(const vec3 &a, const vec3 &b) {
  return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

inline double dot_product(const vec3 &a, const vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 unit_vector(const vec3 &v) {
  double len = v.length();
  return vec3(v.x / len, v.y / len, v.z / len);
}
