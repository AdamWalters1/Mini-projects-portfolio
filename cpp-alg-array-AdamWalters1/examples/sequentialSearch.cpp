#include <iostream>
using namespace std;

/**
 * Searches for an element in a 1D array using sequential search algorithm.
 * 
 * @param arr The array to be searched.
 * @param n The size of the array.
 * @param x The element to be searched for.
 * @return The index of the element if found, -1 otherwise.
 */
int sequentialSearch1D(int arr[], int n, int x) {
    for(auto i = 0; i <n; i++){
        if(arr[i] == x){
            return i;
        }
        return -1;
    }
}

/**
 * Searches for an element in a 2D array using sequential search algorithm.
 * 
 * @param arr The 2D array to be searched.
 * @param rows The number of rows in the array.
 * @param cols The number of columns in the array.
 * @param x The element to be searched for.
 * @return True if the element is found, false otherwise.
 */
bool sequentialSearch2D(int arr[][5], int rows, int cols, int x) {
    for(auto i = 0;i < rows;i++){
        for(auto j =0;i< cols; i++){
            if(arr[i][j] == x){
                cout << "Element found here: Row: " << i << " Column: " << j << endl;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr1D[] = {2, 4, 7, 10, 15};
    int n1D = sizeof(arr1D) / sizeof(arr1D[0]);
    int x; // Element to search for in 1D array

    cout << "Enter the element to search for in the 1D array: ";
    cin >> x;

    cout << sequentialSearch1D(arr1D,n1D,x);
    return 0;
}
