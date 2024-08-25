#include "list_operations.hpp"

#include <iostream>

using namespace std;


int main() {
    int list[ARRAY_SIZE] = {10, 5, 15, 8, 25, 20, 3,
                            18, 12, 7, 22, 1, 4, 11,
                            6, 14, 9, 2, 23, 17};
    int len = ARRAY_SIZE;

    cout << "Initial array:\n";
    printOperation("Array", list, len);

    // Demonstrating bubble sort
    cout << "Sorting the array using Bubble Sort:\n";
    bubbleSort(list, len);
    printOperation("Bubble Sort", list, len);

    // Demonstrating insertion at index 5
    cout << "Inserting 100 at index 5:\n";
    insertAt(list, len, 100, 5); // Insert 100 at position 5
    printOperation("Insert at index 5", list, len);

    // Demonstrating removal of specific item (100)
    cout << "Removing item 100:\n";
    remove(list, len, 100);
    printOperation("Remove item 100", list, len);

    // Demonstrating removal at a specific position (0)
    cout << "Removing item at index 0:\n";
    removeAt(list, len, 0); // Remove first item
    printOperation("Remove at index 0", list, len);

    // Demonstrating removal of all occurrences of an item (15)
    cout << "Removing all 15s:\n";
    removeAll(list, len, 15);
    printOperation("Remove all 15s", list, len);

    // Demonstrating reversing the order
    cout << "Reversing the order of the array:\n";
    reverseOrder(list, len);
    printOperation("Reverse Order", list, len);

    // Check if the list is sorted
    cout << "Is the list sorted? " << (isSorted(list, len) ? "Yes" : "No") << endl;

    return 0;
}


