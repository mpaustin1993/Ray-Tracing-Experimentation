#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>
#include <random>

namespace Raytracer148 {
struct Ray {
  Eigen::Vector3d origin, direction;

};

class Shape;

struct HitRecord {

  //created new Vector3d color to set color of shape

  Eigen::Vector3d position, normal, color;
  double t;
};

class Shape {
public:
  virtual ~Shape(){}
  virtual HitRecord intersect(const Ray &ray) = 0;
};

}

#endif
