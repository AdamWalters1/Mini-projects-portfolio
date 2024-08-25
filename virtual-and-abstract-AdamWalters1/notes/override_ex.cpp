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
