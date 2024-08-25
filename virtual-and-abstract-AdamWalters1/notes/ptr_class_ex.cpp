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

    virtual ~petType() {};

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

    // destructor
    virtual ~dogType() {};

private: 
    string breed;
};

void callPrint(petType* p);

int main(){

    petType *q = new petType("Lucky");
    dogType *r = new dogType("Tommy", "German Shepherd");

// The other way of doing this that takes more lines
/*  petType *q;
    dogType *r;

    q = new petType("Lucky");
    r = new dogType("Tommy", "German Shepherd"); */


    q->print();
    cout << endl;
    r->print();
    cout << endl;

    cout << "*** Calling the function callPrint ***" << endl; 
    callPrint(q);
    cout << endl;
    callPrint(r);
    cout << endl;

    // Delete the allocated memory
    delete q;
    delete r;

    return 0;
}

void callPrint(petType* p){
    p->print();
}