#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Create a vector of integers
    // If you don't want to use the std namespace, you can use the following line
    // std::vector<int> vec;
    vector<int> vec;


    // Add elements to the vector
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    // Access elements
    cout << "Element at index 1: " << vec[1] << std::endl;

    // Remove last element
    vec.pop_back();

    // Using iterators to print all elements
    cout << "Current elements in vector: ";
    for(auto i = vec.begin(); i != vec.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    // Size of the vector
    cout << "Size of vector: " << vec.size() << endl;

    return 0;
}
