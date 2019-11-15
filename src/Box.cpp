#include "Box.h"
#include <limits>
#include <iostream>

using namespace Raytracer148;
using namespace Eigen;
using namespace std;

/* Simple slab-based unit cube intersection. i.e., a box is the intersection of
 * 6 planes, and we find which of these planes, if any, has the closest
 * intersection point.
 */

HitRecord Box::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;

	const Vector3d origin = ray.origin;
	const Vector3d direction = ray.direction;

	float originX = origin[0];
	float originY = origin[1];
	float originZ = origin[2];
	float dirX = direction[0];
	float dirY = direction[1];
	float dirZ = direction[2];

	float tmin = (min[0] - originX) / dirX;
	float tmax = (max[0] - originX) / dirX;

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (min[1] - originY) / dirY;
	float tymax = (max[1] - originY) / dirY;

	if (tymin > tymax) swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return result;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (min[2] - originZ) / dirZ;
	float tzmax = (max[2] - originZ) / dirZ;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return result;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	result.position = ray.origin + tmax * ray.direction;
	result.normal = (result.position - min).normalized();

	return result;
}
	



