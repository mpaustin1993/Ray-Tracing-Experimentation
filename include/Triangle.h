#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

namespace Raytracer148 {
	class Triangle : public Shape {
	public:
		Triangle(Eigen::Vector3d &A, Eigen::Vector3d &B, Eigen::Vector3d &C) : A(A), B(B), C(C) {}

		//calculate Normal

		virtual void setNormal();

		virtual Eigen::Vector3d getNormal();

		//calculate distance from origin

		virtual double calcDistance();

		virtual HitRecord intersect(const Ray &ray);

	private:
		Eigen::Vector3d A;
		Eigen::Vector3d B;
		Eigen::Vector3d C;
		Eigen::Vector3d normal;
		double distance = 0;
	};
}

#endif
