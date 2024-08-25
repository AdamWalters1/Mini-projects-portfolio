#include <iostream>
#include <vector>

using namespace std;

int recBinarySearch(vector<int> &list, int item, int first, int last);

int main()
{
    vector<int> list{2, 5, 7, 10, 15, 17, 20, 25, 30, 35};
    int item = 20;

    int index = recBinarySearch(list, item, 0, list.size() - 1);

    if (index != -1){
        cout << "Item found at index " << index << endl;
    }
    else{
        cout << "Item not found" << endl;
    }

    return 0;
}

/**
 * @brief Performs a recursive binary search on a sorted vector.
 * 
 * @param list The sorted vector to search in.
 * @param item The item to search for.
 * @param first The index of the first element in the vector.
 * @param last The index of the last element in the vector.
 * @return The index of the found item, or -1 if the item is not found.
 */
int recBinarySearch(vector<int> &list, int item, int first, int last)
{
    if (first > last){
        return -1; // Element not found
    }
    int mid = first + (last - first) / 2;
    if (list[mid] == item){
        return mid; // Element found at index mid
    }
    else if (list[mid] < item){
        return recBinarySearch(list, item, mid + 1, last); // Search in the right half
    }
    else{
        return recBinarySearch(list, item, first, mid - 1); // Search in the left half
    }
}

