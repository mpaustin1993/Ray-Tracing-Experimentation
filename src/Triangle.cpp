#include "Triangle.h"
#include <iostream>
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

void Triangle::setNormal() {

	//calculating CA
	Eigen::Vector3d CA;
	CA[0] = C[0] - A[0];
	CA[1] = C[1] - A[1];
	CA[2] = C[2] - A[2];

	//calcuating BA
	Eigen::Vector3d BA;
	BA[0] = B[0] - A[0];
	BA[1] = B[1] - A[1];
	BA[2] = B[2] - A[2];

	normal = CA.cross(BA).normalized();
}

Eigen::Vector3d Triangle::getNormal() {
	return normal;
}

//distance that plane is from the origin

double Triangle::calcDistance() {
	setNormal();
	distance = normal.dot(A);
	return distance;
};


//normal of any point of intersection: normal of plane

HitRecord Triangle::intersect(const Ray &ray) {
	HitRecord result;
//	result.t = -1;

	Eigen::Vector3d direction = ray.direction;
	Eigen::Vector3d origin = ray.origin;

	double a = direction.dot(normal);

	normal = getNormal();
	distance = calcDistance();

	if (a == 0) {
		//ray is parallel to Triangle
		return result;
	}

	//returns distance to plane that triangle lies in
	//need to determine if inside or outside plane

	else {
		double b = normal.dot(origin + normal);
		double distance2plane = (-1 * b / a);

		//Q is the point of intersection
		//Q = distance2plane along ray direction + origin of ray

		double Qx = (direction[0] * distance2plane) + origin[0];
		double Qy = (direction[1] * distance2plane) + origin[1];
		double Qz = (direction[2] * distance2plane) + origin[2];

		Eigen::Vector3d Q;
		Q[0] = Qx;
		Q[1] = Qy;
		Q[2] = Qz;

		// (CA*QA) * normal >= 0

		//calculating CA
		Eigen::Vector3d CA;
		CA[0] = C[0] - A[0];
		CA[1] = C[1] - A[1];
		CA[2] = C[2] - A[2];

		//calcuating QA
		Eigen::Vector3d QA;
		QA[0] = Q[0] - A[0];
		QA[1] = Q[1] - A[1];
		QA[2] = Q[2] - A[2];

		double test1 = (CA.cross(QA)).dot(normal);

		// (BC*QC) * normal >= 0

		//calculating BC
		Eigen::Vector3d BC;
		BC[0] = B[0] - C[0];
		BC[1] = B[1] - C[1];
		BC[2] = B[2] - C[2];

		//calcuating QC
		Eigen::Vector3d QC;
		QC[0] = Q[0] - C[0];
		QC[1] = Q[1] - C[1];
		QC[2] = Q[2] - C[2];

		double test2 = (BC.cross(QC)).dot(normal);

		// (AB*QB) * normal >= 0

		//calculating AB
		Eigen::Vector3d AB;
		AB[0] = A[0] - B[0];
		AB[1] = A[1] - B[1];
		AB[2] = A[2] - B[2];

		//calcuating QB
		Eigen::Vector3d QB;
		QB[0] = Q[0] - B[0];
		QB[1] = Q[1] - B[1];
		QB[2] = Q[2] - B[2];

		double test3 = (AB.cross(QB)).dot(normal);		
				
		if (test1 >= 0 && test2 >= 0 && test3 >=0) {

			/*cout << "Test1: " << test1 << endl;
			cout << "Test2: " << test2 << endl;
			cout << "Test3: " << test3 << endl;*/

			//inside triangle
			//result.position[0] = result.position[0] * -(b / a);
			//result.position[1] = result.position[1] * -(b / a);
			//result.position[2] = result.position[2] * -(b / a);

			double value = b / a;

			//result.position = ray.origin + r * ray.direction;
			//result.normal = (result.position - c).normalized();

			return result;

		}
		else {
			//outside triangle
			return result;
		}

	}
	
}