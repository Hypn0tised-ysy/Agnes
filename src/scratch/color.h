#pragma once

#include "agnes_math.h"

using color3 = vec3;

inline double Linear2sRGB(double linear_value) {
  linear_value = clamp(linear_value, 0.0, 1.0);
  if (linear_value <= 0.0031308) {
    return linear_value * 12.92;
  } else {
    return 1.055 * std::pow(linear_value, 1.0 / 2.4) - 0.055;
  }
}

inline double sRGB2Linear(double rgb_value) {
  rgb_value = clamp(rgb_value, 0.0, 1.0);
  if (rgb_value <= 0.04045) {
    return rgb_value / 12.92;
  } else {
    return std::pow((rgb_value + 0.055) / 1.055, 2.4);
  }
}

inline void WriteColor2File(FILE *fp, const color3 &color) {
  // gamma correction
  double r = Linear2sRGB(color.x);
  double g = Linear2sRGB(color.y);
  double b = Linear2sRGB(color.z);

  // scale to [0, 255]
  int ir = static_cast<int>(255.999 * r);
  int ig = static_cast<int>(255.999 * g);
  int ib = static_cast<int>(255.999 * b);

  fprintf(fp, "%d %d %d\n", ir, ig, ib);
}

inline void WriteColor2File_without_gamma_correction(FILE *fp,
                                                     const color3 &color) {
  double r = clamp(color.x, 0.0, 1.0);
  double g = clamp(color.y, 0.0, 1.0);
  double b = clamp(color.z, 0.0, 1.0);

  // scale to [0, 255]
  int ir = static_cast<int>(255.999 * r);
  int ig = static_cast<int>(255.999 * g);
  int ib = static_cast<int>(255.999 * b);

  fprintf(fp, "%d %d %d\n", ir, ig, ib);
}