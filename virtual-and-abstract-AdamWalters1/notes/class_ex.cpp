#include <iostream>
#include <string>

using namespace std;

// Abstract base class
class petType {
public:
    // virtual function
    virtual void print() const {
        cout << "Name: " << name;
    };

    petType(string n = ""){
        name = n;
    }; // constructor

private:
    string name;
};

class dogType: public petType {
public:
    // override the print function
    void print() const {
        petType::print();
        cout << ", Breed: " << breed << endl;
    };

    dogType(string n = "", string b = ""): petType(n){
        breed = b;
    };
private:
    string breed;

};

void callPrint(petType& p);

int main(){
    petType pet("Lucky");
    dogType dog("Tommy", "German Shepherd");

    pet.print();
    cout << endl;
    dog.print();

    cout << "*** Calling the function callPrint ***" << endl;
    callPrint(pet);
    cout << endl;
    callPrint(dog);
    cout << endl;

    return 0;
}

void callPrint(petType& p){
    p.print();
}