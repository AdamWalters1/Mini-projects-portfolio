#include "list_operations.hpp"


/**
 * Removes the specified element from the list.
 *
 * @param list The array representing the list.
 * @param len The length of the list.
 * @param removeItem The element to be removed.
 */
void remove(int list[], int& len, int removeItem){
    int loc;
    bool found = false;
    if (len == 0)
        cout << "Cannot remove from an empty list." << endl;
    else{
        for(int i =0;i<len;i++){
            if(removeItem==list[i]){
                found = true;
                loc = i;
                break;
            }
        }
        if(found){
            for(int i =0;i<len -1;i++)
                list[i] = list[i+1];
            len--;
        } else{
            cout << "Item to be deleted is not in the list." << endl;
        }
    };
}

/**
 * Removes an element at the specified index from the given list.
 *
 * @param list The list from which the element is to be removed.
 * @param len The length of the list.
 * @param index The index of the element to be removed.
 */
void removeAt(int list[], int& len, int index){
    if (index <0 || index >= len)
        cout << "index is out of range. " << endl;
    else{
        for(int i = index; i< len -1;i++)
            list[i] = list[i+1];
        len--;
    }
};

/**
 * Removes all occurrences of a specified element from an integer array.
 *
 * @param list The integer array from which elements will be removed.
 * @param len The length of the array.
 * @param removeItem The element to be removed from the array.
 */
void removeAll(int list[], int& len, int removeItem){
    int i =0;
    bool found = false;
    while(i<len){
        if(removeItem==list[i]){
            found = true;
            for(int j =i;j<len-1;j++)
                list[j] = list[j+1];
            len--;
        } else
            i++;
    }
    if(!found)
        cout << "Item to be deleted is not the list." << endl;
}

/**
 * Inserts an element at a specified index in the given list.
 *
 * @param list The array representing the list.
 * @param len The current length of the list.
 * @param insertItem The element to be inserted.
 * @param index The index at which the element should be inserted.
 */
void insertAt(int list[], int& len, int insertItem, int index){
    if(index <0 || index >= len)
        cout << "Index is out of range." << endl;
    else{
        if(index > len){
            cout << "Item will be inserted as the end of the list." << endl;
            list[len] = insertItem;
            len++;
        } else{
            for(int i = len -1; i >index ; i--)
                list[i+1] = list[i];
            list[index]=insertItem;
            len++;
        }
    }
}

/**
 * Function to sort an array using the Bubble Sort algorithm.
 *
 * Bubble Sort is a simple sorting algorithm that repeatedly steps through the list,
 * compares adjacent elements and swaps them if they are in the wrong order.
 * The pass through the list is repeated until the list is sorted.
 *
 * @param arr The array to be sorted.
 * @param n The size of the array.
 */
void bubbleSort(int arr[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

/**
 * Function to reverse the order of elements in an array.
 *
 * This function iterates over the first half of the array and swaps each element
 * with the corresponding element in the second half of the array.
 *
 * @param list The array to be reversed.
 * @param len The size of the array.
 */
void reverseOrder(int list[], int len){
    for (int i = 0; i < len / 2; i++)
        swap(list[i], list[len - i - 1]);
    cout << "Array reversed." << endl;
}

/**
 * Function to check if an array is sorted in ascending order.
 *
 * This function iterates over the array and checks if each element is less than or equal to the next element.
 * If it finds an element that is greater than the next one, it returns false.
 * If it doesn't find any such element, it returns true, indicating that the array is sorted.
 *
 * @param list The array to be checked.
 * @param len The size of the array.
 * @return true if the array is sorted, false otherwise.
 */
bool isSorted(const int list[], int len){
    for (int i = 0; i < len-1; i++){
        if (list[i] > list[i + 1])
            return false;
    }
    return true;
}

// Additional helper functions may be defined as needed

void printOperation(const string &operation, const int *list, int len) {
    cout << operation << ": ";
    for (int i = 0; i < len; i++)
        cout << list[i] << " ";
    cout << endl;
}
