#include <iostream>
using namespace std;

/**
 * Sorts an array of integers in ascending order using the bubble sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
void bubbleSortAscending(int arr[], int len) {
    int i, j;
    bool swapped;
    for (i = 0; i < len - 1; i++) {
        swapped = false;
        for (j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}
/**
 * Sorts an array in descending order using the bubble sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
void bubbleSortDescending(int arr[], int len) {
    int i, j;
    bool swapped;
    for (i = 0; i < len - 1; i++) {
        swapped = false;
        for (j = 0; j < len - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}

/**
 * Prints the elements of an integer array.
 * 
 * @param arr The integer array to be printed.
 * @param size The size of the array.
 */
void printArray(int arr[], int size) {
    for(int i =0;i<size;i++){
        cout << arr[i] << " " << endl;
    }
}

// Main function to test the above implementation
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);


    bubbleSortAscending(arr,n);
    printArray(arr,n);
    cout << endl;
    bubbleSortDescending(arr,n);
    printArray(arr,n);
    return 0;
}
