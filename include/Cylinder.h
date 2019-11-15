#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

namespace Raytracer148 {
	class Cylinder : public Shape {

	public:

		//based on: http://www.hugi.scene.org/online/coding/hugi%2024%20-%20coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm

		//takes in a center vector, V which determines the axis, a color vector
		//a double radius, and the capPoint which is the limit for the top and bottom of the cylinder

		Cylinder(Eigen::Vector3d &C, Eigen::Vector3d &A, Eigen::Vector3d &color, double radius , double capPoint)
			: C(C), A(A), color(color), radius(radius), capPoint(capPoint) {}

		virtual HitRecord intersect(const Ray &ray);

	private:
		Eigen::Vector3d C;
		Eigen::Vector3d A;
		Eigen::Vector3d color;
		double radius;
		double capPoint;

	};

}

#endif
