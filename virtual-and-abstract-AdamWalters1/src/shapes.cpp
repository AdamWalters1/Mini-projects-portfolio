#include "threeDShape.h"
#include <iostream>
using namespace std;
// Sphere class constructor
// @param r: radius of the sphere
Sphere::Sphere(double r) : radius(r) {}

// Method to calculate the volume of a Sphere
// @return: volume of the sphere
double Sphere::volume() const {
    return (4.0/3.0)*M_PI*radius*radius*radius;
}

// Method to calculate the surface area of a Sphere
// @return: surface area of the sphere
double Sphere::surfaceArea() const {
    return 4.0*M_PI*radius*radius;
}

// Pyramid class constructor
// @param bw: base width of the pyramid
// @param bl: base length of the pyramid
// @param h: height of the pyramid
Pyramid::Pyramid(double w, double l, double h) : baseWidth(w),baseLength(l),height(h) {}

// Method to calculate the volume of a Pyramid
// @return: volume of the pyramid
double Pyramid::volume() const {
    return (1.0/3.0)*baseWidth*baseLength*height;
}

// Method to calculate the surface area of a Pyramid
// @return: surface area of the pyramid
double Pyramid::surfaceArea() const {
    return baseWidth*baseLength + baseWidth*pow(pow(baseLength/2,2)+height*height,0.5) +
    baseLength*pow(pow(baseWidth/2,2)+height*height,0.5);
}