#include <iostream>
#include <vector>
#include <algorithm> // For sort (a O(n log n) sorting algorithm)

using namespace std;

int main() {
	// All components of a vector need to be of the same type 
	// (in this case, all integers)
    vector<int> vec = {10, 20, 30, 40, 50};

    // Inserting an element at the beginning using insert()
    vec.insert(vec.begin(), 5);
    
    // Erasing the second element
    vec.erase(vec.begin() + 1);

    // Sorting the vector
    sort(vec.begin(), vec.end());

    // Using emplace_back to add an element at the end
    vec.emplace_back(60);

    // Output the elements using range-based for loop
    cout << "Vector elements: ";
    for (int n : vec) {
        cout << n << " ";
    }
    cout << endl;

    // Checking if vector is empty
    cout << "Is the vector empty? " << (vec.empty() ? "Yes" : "No") << endl;

    // Printing the front and back element
    cout << "First element: " << vec.front() << ", Last element: " << vec.back() << endl;

    return 0;
}
