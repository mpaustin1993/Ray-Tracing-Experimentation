#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Cylinder.h"

using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;

    Vector3d center;
	
	// Creation of blue cylinder

    center[0] = -2.5;
    center[1] = 0;
    center[2] = 4.5;

	// Vector scaled in the y direction

	Vector3d V;

	V[0] = 0;
	V[1] = 1;
	V[2] = 0;

	// Sets the intial color values of the cylinder

	Vector3d color;

	color[0] = .25;
	color[1] = .50;
	color[2] = .75;

	scene.addShape(new Cylinder(center, V, color, 1, 1.5));

	// Creation of green sphere

	center[0] = .6;
	center[1] = 1.2;
	center[2] = 2.4;

	// Sets the intial color values of the sphere
	
	color[0] = 0;
	color[1] = .80;
	color[2] = .40;

    scene.addShape(new Sphere(center, color, .75));	

    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
