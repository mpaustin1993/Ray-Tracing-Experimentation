#include "Scene.h"
#include <png.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <iostream>
#include <random>

using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {

        HitRecord r = shapes[i]->intersect(ray);

        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) 
		{

            result = r;
            foundSomething = true;

        }
    }
    return result;
}

// Shadow Casting

// Very similar to the closestHit function shown above

// makeShadow receives a Ray and cycles through created HitRecords:
// these created records cycle through a for loop checking to see if these 
// HitRecords collided the near or far surfaces of any shapes

// I experimented with comparing the r.t or surfaces of our 3D objects to different
// thresholds, if our HitRecord was above a threshold of 1.10, then we collided with a surface
// and needed to create a shadow

bool Scene::makeShadow(const Ray &ray) {

	HitRecord r;

	for (int i = 0; i < shapes.size(); i++) {		

		r = shapes[i]->intersect(ray);

		if (r.t > 1.10) {
			return true;
		}
	}

	return false;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]

Vector3d Scene::trace(const Ray &ray) {

    HitRecord r = closestHit(ray);

    Vector3d result;

	Vector3d norm = r.normal;
	
	// sets the RBG values of any unaltered pixels to be .25, a light grey
	// sets our background to be light grey

	result[0] = result[1] = result[2] = .25;	

    if (r.t < numeric_limits<double>::epsilon()) return result;

	// sets the colors of the returned result vectors to the colors of the shapes

	result[0] = r.color[0];
	result[1] = r.color[1];
	result[2] = r.color[2];    

	// Lighting was implemented similarly to what was done in HWK3

	// Ambient Lighting

	// creates Ambient lighting by setting an Ambient Constant of 0.5 and multiplying
	// this by the color vector of our HitRecord

	float ambientConst = 0.5;
	Vector3d ambient = ambientConst * r.color;	

	// Diffuse Lighting

	// creates Diffuse lighting by creating the Vector lightDir, getting the dot product
	// of the normal of our HitRecord, and multiplying our dot product by the color vector
	// of our Hit Record

	Vector3d lightDir = (lightPos - r.position).normalized();
	double dot = lightDir.dot(r.normal);

	if (dot < 0) dot = 0;

	Vector3d diffuse = dot * r.color;

	// Spectral Lighting

	// First I calculated the camera / view direction by normalizing the difference between our ray's origin & the current vector's position
	// Then I computed the reflection vector by creating a vector pointing towards the light (-lightDir) and multiplying by our already
	// calculated dot value & the normal of our HitRecord
	
	// Then I calculated our specular Value and specular Consant according to what I did originally in HWK3
	// I played with the last parameter of specularVal, changing it from 32 to 16, because it was creating unwanted
	// artifacts on my rendered sphere

	// Then I multipled our Hitrecord's color vector by our specular Constant & specular Value
		
	Vector3d viewD = (ray.origin - r.position).normalized();
	Vector3d reflectD = (-lightDir) - (2 * -dot * r.normal);
	float specularVal = pow(max(viewD.dot(reflectD), 0.0), 16);
	float specularConst = 0.3;
	Vector3d specular = specularConst * specularVal * r.color;

	// Applies our Ambient, Diffuse, and Spectral Lighting to each RGB value of our result vector

    result[0] = (ambient[0] + diffuse[0] + specular[0]) * r.color[0];
	result[1] = (ambient[1] + diffuse[1] + specular[1]) * r.color[1];
	result[2] = (ambient[2] + diffuse[2] + specular[2]) * r.color[2];

	Ray shadowRay;

	// Shadow Casting

	// I created a shadowRay and set it's origin to the position of the current HitRecord,
	// and it's direction to the current direction of the light

	// I then passed my shadowRay into the function makeShadow that returns a bool:
	// if makeShadow returns true, then it sets the RGB values of the current result
	// vector to be 0, 0, 0, coloring the image black and producing a shadow predominantly
	// across the cylinder

	shadowRay.origin = r.position;
	shadowRay.direction = lightDir;

	if (makeShadow(shadowRay)) {
		result[0] = 0;
		result[1] = 0;
		result[2] = 0;
	}	

	return result;
}

void Scene::render(Image &image) {

    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++) {

			Ray curRay;
			curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

			curRay.direction[0] = (x + 0.5) * pixelSize - 1;
			curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
			curRay.direction[2] = 1;

			//Reflective Surfaces

			// I couldn't figure out how to implement the proper solution but I tried something :)

			// First I obtained the RGB values of the current pixel based on its x, y coordinate

			double red, green, blue = 0;
			pixel_t *currPixel = image.pixelAt(x, y);
			red = (double)currPixel->red;
			green = (double)currPixel->green;
			blue = (double)currPixel->blue;

			Vector3d color;

			// Then I checked if that pixel's RGB values were 0 / NULL, indicating that it hadn't been rendered
			// in the image set

			if (red == 0 && green == 0 && blue == 0) {

				//if the pixel was NULL, I then rendered the image

				color = trace(curRay);
				image.setColor(x, y, color[0], color[1], color[2]);
			}

			// I then found a new y coordinate which is the value of the current y value subtracted from the max
			// height of the image, or the distance from the 'mirrored' pixel to the bottom of the image frame

			int oppY = size - y;

			// I made sure that the R value of the current color vector wasn't 0.25, or the default grey color of
			// the image background

			if (color[0] != 0.25 && oppY < size && oppY > (y+80)) {

				// I then colored a pixel below the formed shape with the color of the borrowed pixel's
				// color plus some grey shading, creating a reflected / blurry image

				image.setColor(x, oppY, color[0] + (.35), color[1] + (.35), color[2] + (.35));
			}


			/* && otherRed != red && otherGreen && green && otherBlue != blue */

			/*if (0 < oppY && oppY < size) {

				currPixel = image.pixelAt(x, oppY);
				otherRed = (double)currPixel->red;
				otherGreen = (double)currPixel->green;
				otherBlue = (double)currPixel->blue;

				if (color[0] != 0.25 && color[0] != 0 && otherRed != red || otherGreen != green || otherBlue != blue && oppY < size) {

					image.setColor(x, oppY, color[0] + .2, color[1] + .2, color[2] + .2);
				}
			}*/
			
        }
}
