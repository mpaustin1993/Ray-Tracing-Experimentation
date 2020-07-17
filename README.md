# tracing-with-ray
4th Homework Assignment for Interactive Computer Graphics

I used Microsoft Visual Studio 2017 and needed to download the eigen3.3.7 library and unpack it into my HWK4 folder. In Microsoft VS 2017, I created Include links to eigen3.3.7, and to the include folder in the COSC4370 (Hwk 4) folder. This homework can be compiled via the debugger in Visual Studio 2017 - compiling should produce a blue cylinder and a green cube. Both the cylinder and cube should have different colors, phong shading, the sphere should cast a shadow on the cylinder, and they should be both reflected onto the bottom of the image frame.

First, I had to decide which 3D object to render: I greatly struggled with rendering a cube and a triangle, so I finally settled upon a cylinder, which was much easier. I created the cylinder and then phong shaded the sphere and cylinder by implementing the ideas and concepts that I used to complete HWK3: spectral shading was difficult to implement since it was hard to translate the functions of OpenGL to Eigen functions.

Then, I implemented shadow casting by testing HitRecords and collisions of our light rays to shapes throughout the image set: I initially had some trouble with artifacts / black dots being rendered on the sphere, but then I reduced them by playing with the spectral lighting settings and increasing the threshold that the t value of the HitRecords was compared to.

I couldn't successfully implement the reflective surfaces, so I implemented something that I hope will suffice: I rendered the mirrored pixels of each shape by lighting up and grey shading a pixel with a y-value offset, providing the appearance of the objects being mirrored across a reflective pool / surface. Please let me know if you have any questions.

Please let me know if you have any problems compiling or displaying any of my images.
