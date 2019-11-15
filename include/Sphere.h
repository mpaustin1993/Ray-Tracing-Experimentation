#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148 {
class Sphere : public Shape {
public:

	// all I added is that the Sphere nows takes in a color vector to set the color

    Sphere(Eigen::Vector3d &center, Eigen::Vector3d &color, double radius) : c(center), color(color), r(radius) {}

    virtual HitRecord intersect(const Ray &ray);

private:
    Eigen::Vector3d c;
	Eigen::Vector3d color;
    double r;
};
}

#endif
