#include <iostream>
#include <vector>

using namespace std; 

int main() {
    vector<int> vec;

    // Initial size and capacity
    cout << "Initial size: " << vec.size() << endl;
    cout << "Initial capacity: " << vec.capacity() << endl;

    // Adding elements to the vector
    for (auto i = 0; i < 10; ++i) {
        vec.push_back(i);
        cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;
    }

    // Reserving more space
    vec.reserve(20);
    cout << "After reserve(20), Capacity: " << vec.capacity() << endl;

    // Reducing the vector size
    vec.resize(5);
    cout << "After resize(5), Size: " << vec.size() << ", Capacity: " << vec.capacity() << endl;

    // Request to shrink capacity
    vec.shrink_to_fit();
    cout << "After shrink_to_fit(), Capacity: " << vec.capacity() << endl;

    return 0;
}
