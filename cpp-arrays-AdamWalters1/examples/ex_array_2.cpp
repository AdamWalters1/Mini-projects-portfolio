#include <iostream>
#include <fstream>
using namespace std;

void displayArray(int arr[], int size);

int main() {
    // Declare an array
    int numbers[5];

    // Open file for reading
    ifstream inFile("data.txt");

    // Read data from file into the array
    if (inFile.is_open()) {
        for(int i = 0; i < 5; i++) {
            if (!(inFile >> numbers[i])) {
                cerr << "Error reading data from file." << endl;
                return -1;
            }
        }
        inFile.close();
    } else {
        cerr << "Unable to open file." << endl;
        return -1;
    }

    // Use the function to display the array
    displayArray(numbers, 5);

    return 0;
}

// Function to display the array
/**
 * Displays the elements of an integer array.
 * 
 * @param arr The integer array to be displayed.
 * @param size The size of the array.
 */
void displayArray(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        cout << "Element at index " << i << ": " << arr[i] << endl;
    }
}