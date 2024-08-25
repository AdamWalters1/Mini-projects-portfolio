#ifndef THREEDSHAPE_H
#define THREEDSHAPE_H

#include<cmath>

// Abstract Base Class for 3D Shapes
class ThreeDShape {
public:
    virtual double volume() const = 0;
    virtual double surfaceArea() const = 0;
    virtual ~ThreeDShape() {} // Ensure a virtual destructor
};

// Derived Class - Sphere
class Sphere : public ThreeDShape {
private:
    double radius;
public:
    Sphere(double r);
    double volume() const override;
    double surfaceArea() const override;
};

// Derived Class - Pyramid
class Pyramid : public ThreeDShape {
private:
    double baseWidth, baseLength, height;
public:
    Pyramid(double bw, double bl, double h);
    double volume() const override;
    double surfaceArea() const override;
};

#endif // THREEDSHAPE_H
