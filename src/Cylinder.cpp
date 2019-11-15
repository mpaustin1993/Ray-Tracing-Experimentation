#include "Cylinder.h"
#include <limits>

using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Cylinder::intersect(const Ray &ray) {
	HitRecord result;
	result.t = -1;

	//similar to the sphere: took in the ray direction and set it to a vector D
	//created vector C which is the origin of the ray minus the center of the cylinder

	Vector3d D = ray.direction;
	Vector3d E = ray.origin - C;

	//created all dot products for our vector V, D, and C

	double DD = D.dot(D);
	double DV = D.dot(A);
	double DX = D.dot(E);
	double XV = E.dot(A);
	double XX = E.dot(E);	

	// equations derived from the followed website: http://www.hugi.scene.org/online/coding/hugi%2024%20-%20coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
	// calculated variables for forming our cylinder based on our dot products

	double at = DD - DV * DV;
	double bt = 2 * (DX - DV * XV);
	double ct = XX - XV * XV - radius * radius;

	// heavily borrowed from Sphere.h

	double discriminant = bt * bt - 4 * at * ct;

	if (discriminant < numeric_limits<double>::epsilon()) return result;

	double t0 = (-bt - sqrt(discriminant)) / (2 * at);
	double t1 = (-bt + sqrt(discriminant)) / (2 * at);

	if (t1 < numeric_limits<double>::epsilon()) return result; 

	if (t0 > numeric_limits<double>::epsilon()) result.t = t0; 
	else result.t = t1;

	// calculated the top cap-point of the cylinder: where the top of the cylinder is going to stop forming
	// set the bottom cap-point of the cylinder to be -1, where our image's surface / plane sits

	double m = DV * result.t + XV;

	if (m < -1 || m > capPoint) {
		result.t = -XV / DV;
	}

	// set our cylinder's color to colors input into main.cpp

	result.color[0] = color[0];
	result.color[1] = color[1];
	result.color[2] = color[2];

	// taken from our Sphere.H

	result.position = ray.origin + result.t * ray.direction;

	// calculates the normal of our vector based on our V & top cap-point

	result.normal = (result.position - C - A*m).normalized();

	return result;
}