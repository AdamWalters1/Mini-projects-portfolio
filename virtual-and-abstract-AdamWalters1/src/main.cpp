#include <iostream>
#include "threeDShape.h"

using namespace std;
int main() {
    int numShapes, shapeType;
    double r,l,w,h;
    std::cout << "Enter the number of shapes: ";
    std::cin >> numShapes;

    auto** shapes = new ThreeDShape*[numShapes];

    for(int i = 0;i<numShapes;i++){
        cout << "enter the shape type for shape " << i +1 << " (1 for sphere, 2 for Pyramid): ";
        cin >> shapeType;
        if(shapeType == 1){
            cout << "Enter the radius of the sphere: ";
            cin >> r;
            shapes[i] = new Sphere(r);
            cout << endl;
        }
        else if(shapeType == 2){
            cout << "Enter the length of the pyramid: ";
            cin >> l;
            cout << "Enter the width of the pyramid: ";
            cin >> w;
            cout << "Enter the height of the pyramid: ";
            cin >> h;
            shapes[i] = new Pyramid(w,l,h);
            cout << endl;
        }
        else{
            cout << "You have entered a wrong input. Defaulting to a sphere with radius 1" << endl;
            shapes[i] = new Sphere(1);
        }
    }

    cout << "Calculating properties of entered shapes..." << endl;
    for(int i = 0;i<numShapes;i++){
        cout << "Shape " << i+1 << " Volume : " << shapes[i]->volume() <<
         ", Surface Area: " << shapes[i]->surfaceArea() << endl;
    }
    return 0;
}
