#include <iostream>
#include <cmath>
using namespace std;

// declaring functions
bool isPrime(int n);
void bubbleSortAscending(int arr[],int len);
void printArray(int arr[],int size);

int main(){
    int arr[] = {11,25,27,13,8,30,21,7,17};
    int len = sizeof(arr)/sizeof(arr[0]);
    int count = 0;
    // finding how many primes there are
    for(int i = 0; i< len; i++){
        if(isPrime(arr[i]) == true){
            count++;
        }
    }
    // declaring prime array
    int primes[count];
    int index = 0;
    // putting all primes into the prime array
    for(int k = 0; k < len; k++){
        
        if(isPrime(arr[k]) == true){
            primes[index] = arr[k];
            
            index++;
        }
    }
    // bubble sort and printing
    bubbleSortAscending(primes,count);
    printArray(primes,count);
    return 0;
}
// isPrime checks n to see it its prime, returns true if so
bool isPrime(int n){
    
    if (n <= 1) {
        return false; 
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false; 
        }
    }
    return true; 
}
// sorts using bubble sort
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

void printArray(int arr[], int size) {
    for(int i =0;i<size;i++){
        cout << arr[i] << " " << endl;
    }
}