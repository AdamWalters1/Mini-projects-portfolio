#include <iostream>
using namespace std;

/**
 * Sorts an array in ascending order using the selection sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */

void selectionSortAscending(int arr[], int n) {
    int i, j, min;
 
    for (i = 0; i < n - 1; i++) {
        // Finding the min number
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
        // Swap the found minimum number with first number
        if (min != i)
            swap(arr[min], arr[i]);
    }
}

/**
 * Sorts an array of integers in descending order using the selection sort algorithm.
 * 
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
void selectionSortDescending(int arr[], int n) {
    int i, j, max;
 
    for (i = 0; i < n - 1; i++) {
        // Finding the min number
        max = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] > arr[max])
                max = j;
        }
        // Swap the found minimum number with first number
        if (max != i)
            swap(arr[max], arr[i]);
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

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    selectionSortAscending(arr, n);
    cout << "Sorted array in Ascending Order: \n";
    printArray(arr, n);

    selectionSortDescending(arr, n);
	cout << "Sorted array in Descending Order: \n";
	printArray(arr, n);
    return 0;
}