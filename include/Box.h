#ifndef BOX_H
#define BOX_H

#include "Shape.h"

namespace Raytracer148 {
	class Box : public Shape {

		public:
			Box(Eigen::Vector3d &min, Eigen::Vector3d &max) : min(min), max(max) {}

			virtual HitRecord intersect(const Ray &ray);

		private:
			Eigen::Vector3d min;
			Eigen::Vector3d max;
			
		};

	
}

#endif
