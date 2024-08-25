[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/d5wuBzgL)
# Abstract Classes, Virtual Functions, and Overiding in C++

## Table of Contents

- [Abstract Classes, Virtual Functions, and Overiding in C++](#abstract-classes-virtual-functions-and-overiding-in-c)
  - [Table of Contents](#table-of-contents)
  - [Pointers and Classes](#pointers-and-classes)
  - [Abstract Classes](#abstract-classes)
    - [Abstract Classes in C++](#abstract-classes-in-c)
    - [Abstract Classes in Python (remember, no pointers here)](#abstract-classes-in-python-remember-no-pointers-here)
  - [Virtual Functions](#virtual-functions)
    - [Overriding in C++](#overriding-in-c)
    - [Overriding in Python](#overriding-in-python)
  - [Assignment](#assignment)
    - [`ThreeDShape` (Abstract Base Class)](#threedshape-abstract-base-class)
    - [`Sphere` (Derived Class)](#sphere-derived-class)
    - [`Pyramid` (Derived Class)](#pyramid-derived-class)
    - [Formulae](#formulae)
    - [Expected Output](#expected-output)

## Pointers and Classes

When using pointers and classes together there are three things that are normally done:

1. Include the destructor in the base class (typically done as a `virtual` function)
2. Overload the assignment operator for the class. (Not doing just yet)
3. Include the copy constructor in the base class. (Not doing just yet)

We won't be using pointers with classes too much in today's assignment, but it's good to know how to do it. We'll be using pointers with classes in the next assignment. I have provided the following examples for you to use in your work:

| C++ With Pointers | C++ Without Pointers | Python |
| :---: | :---: | :---: |
| [Abstract Class with Pointers](notes/abc_ex_ptr.cpp) | [Abstract Class without Pointers](notes/abc_ex.cpp) | [Abstract Class in Python](notes/abc_ex.py) |
| [Classes with Pointers](notes/ptr_class_ex.cpp) | [Classes without Pointers](notes/class_ex.cpp) | |
| | [Overriding in C++](notes/override_ex.cpp) | [Overriding in Python](notes/override_ex.py) |

## Abstract Classes

Abstract classes that are ***not*** instantiated are used to provide a common interface for derived classes. They are more like a template that all other classes that are derived from them. At no point can you create an object of an abstract class, you can only create objects of derived classes. This goes for both C++ and Python. Python you have to use an `ABC` class from the `abc` module to create an abstract class (technically, not, but highly recommended to prevent further issues).

### Abstract Classes in C++

You can find the example code file to run [here](notes/abstract_class_ex.cpp).

```cpp
#include <iostream>
#include <string>

// Abstract base class
class Animal {
public:
    // Pure virtual function makes this class abstract
    virtual void speak() const = 0;

    // Virtual destructor to ensure proper cleanup of derived class objects
    virtual ~Animal() {}
};

// Derived class
class Dog : public Animal {
public:
    // Implementation of the pure virtual function from the base class
    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};

// Another derived class
class Cat : public Animal {
public:
    // Implementation of the pure virtual function from the base class
    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

int main() {
    Dog myDog;
    myDog.speak(); // Outputs: Woof!

    Cat myCat;
    myCat.speak(); // Outputs: Meow!

    return 0;
}

```

Click [here](notes/abc_ex_ptr.cpp) to see a version that uses pointers to the base class.

### Abstract Classes in Python (remember, no pointers here)

You can find the example code file to run [here](notes/abc_ex.py).

```py
from abc import ABC, abstractmethod

class Animal(ABC):
    @abstractmethod
    def speak(self):
        pass


class Dog(Animal):
    def speak(self):
        print("Woof!")


class Cat(Animal):
    # Implement the abstract method
    def speak(self):
        print("Meow!")

# Demonstration myAnimal = Animal() # This would raise an error: Can't instantiate
# abstract class Animal with abstract methods speak

if __name__ == "__main__":

    # This would raise an error: Can't instantiate abstract class Animal with abstract methods speak
    # myAnimal = Animal()  

    myDog = Dog()
    myDog.speak()  # Outputs: Woof!

    myCat = Cat()
    myCat.speak()  # Outputs: Meow!

```

## Virtual Functions

Virtual functions are used to ensure that the most derived class's function is called. This is done by using the `virtual` keyword in the base class and the `override` keyword in the derived class. This is done to ensure that the most derived class's function is called when using pointers to the base class.

Virtual functions are not part of Python, but you can override methods in Python, effectively making all methods `virtual` in Python.

### Overriding in C++

You can find the example code file to run [here](notes/override_ex.cpp).

```cpp
#include <iostream>
using namespace std;

// Base class
class Animal {
public:
    // Virtual function
    virtual void speak() const {
        cout << "This animal does not have a sound" << endl;
    }
    // Virtual destructor to ensure proper cleanup of derived objects
    virtual ~Animal() {}
};

// Derived class
class Dog : public Animal {
public:
    // Override speak function
    void speak() const override {
        cout << "Woof!" << endl;
    }
};

// Another derived class
class Cat : public Animal {
public:
    // Override speak function
    void speak() const override {
        cout << "Meow!" << endl;
    }
};

// Function to demonstrate polymorphism
void animalSound(const Animal& animal) {
    animal.speak();
}

int main() {
    Animal myAnimal;
    Dog myDog;
    Cat myCat;

    animalSound(myAnimal); // Outputs: This animal does not have a sound
    animalSound(myDog);    // Outputs: Woof!
    animalSound(myCat);    // Outputs: Meow!

    return 0;
}
```

### Overriding in Python

Python does not have `vitual` functions as C++ does, however that doesn't mean that you can't override methods in
Python, its just that you can whenver you want to because effectively all methods are `virtual` in Python, even
though that's not what they really are under the hood. We've done this in the past but here's an example for you,
you can find the file and run the code [here](notes/override_ex.py):

```py
class Animal:
    def speak(self):
        print("This animal does not have a sound")

class Dog(Animal):
    def speak(self):
        print("Woof!")

class Cat(Animal):
    def speak(self):
        print("Meow!")

def animal_sound(animal):
    animal.speak()


myAnimal = Animal()
myDog = Dog()
myCat = Cat()

animal_sound(myAnimal)  # Outputs: This animal does not have a sound
animal_sound(myDog)     # Outputs: Woof!
animal_sound(myCat)     # Outputs: Meow!
```

## Assignment

For today's assignment we'll be making an abstrace class called `TheeDShape`, two inherited classes called `Pyramid` and `Sphere`. Within these classes we'll calculate the surface area and volume of each shape. The user will be prompted to enter the number of shapes, the type of shape, and the dimensions of the shape. The program will then calculate the surface area and volume of each shape and display the results.

### `ThreeDShape` (Abstract Base Class)

- **Methods:**
  - `virtual double volume() const = 0`: Pure virtual function to calculate the volume of the shape.
  - `virtual double surfaceArea() const = 0`: Pure virtual function to calculate the surface area of the shape.
- **Destructor:**
  - `virtual ~ThreeDShape() {}`: Virtual destructor for safe polymorphic deletion.

### `Sphere` (Derived Class)

- **Private Members:**
  - `double radius`: Represents the radius of the sphere.
- **Public Members:**
  - Constructor `Sphere(double r)`: Initializes the `Sphere` object with a given radius.
  - `double volume() const override`: Overrides the base class method to calculate the volume of a sphere.
  - `double surfaceArea() const override`: Overrides the base class method to calculate the surface area of a sphere.

### `Pyramid` (Derived Class)

- **Private Members:**
  - `double baseWidth`: Represents the width of the pyramid's base.
  - `double baseLength`: Represents the length of the pyramid's base.
  - `double height`: Represents the height of the pyramid from the base to the apex.
- **Public Members:**
  - Constructor `Pyramid(double bw, double bl, double h)`: Initializes the `Pyramid` object with base width, base length, and height.
  - `double volume() const override`: Overrides the base class method to calculate the volume of a pyramid.
  - `double surfaceArea() const override`: Overrides the base class method to calculate the surface area of a pyramid.

### Formulae

Sphere:

- Volume of a sphere: $V_{\text{sphere}} = \frac{4}{3} \pi r^3$

- Surface area of a sphere: $A_{\text{sphere}} = 4 \pi r^2$

Pyramid (with a rectangular base):

- Volume of a pyramid: $V_{\text{pyramid}} = \frac{1}{3} b_w b_l h$

- Surface area of a pyramid: $A_{\text{pyramid}} = b_w b_l + b_w \sqrt{\left(\frac{b_l}{2}\right)^2 + h^2} + b_l \sqrt{\left(\frac{b_w}{2}\right)^2 + h^2}$

Where:

- $r$ is the radius of the sphere.
- $b_w$ is the width of the pyramid's base.
- $b_l$ is the length of the pyramid's base.
- $h$ is the height of the pyramid (from the base to the apex).

### Expected Output

```txt
 Enter the number of shapes:2
 Enter shape type for shape 1 (1 for Sphere, 2 for Pyramid):1
 Enter radius of the sphere:3
 Enter shape type for shape 2 (1 for Sphere, 2 for Pyramid):2
 Enter base width of the pyramid:3
 Enter base length of the pyramid:4
 Enter height of the pyramid:5

Calculating properties of entered shapes...
Shape 1 - Volume: 113.097, Surface Area: 113.097
Shape 2 - Volume: 20, Surface Area: 49.2011
```
