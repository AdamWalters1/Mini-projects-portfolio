#include <iostream>

using namespace std; 

int sequential_search(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i; // Target found, return the index
        }
    }
    return -1; // Target not found
}

int main() {
    int arr[]={1,2,3,4,5};
    int N = sizeof(arr)/sizeof(arr[0]);
    int target = 5;
    int result = sequential_search(arr,N,target);

    if(result != -1)
        cout << "Suspect has escaped. " << endl;
}
