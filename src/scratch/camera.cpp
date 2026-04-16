/*
3d空间右手系
视口原点在左上角
*/

#include "vec.h"

class Camera {
public:
  Camera() {}
  Camera() {
  }

private:
  point3 origin;
  point3 upper_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 right, up, forward;

  double focal_length;
};