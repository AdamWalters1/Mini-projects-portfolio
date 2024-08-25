#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

void fillVector(vector<int>& list);
void copyVector(const vector<int>& source, vector<int>& destination);
void bubbleSort(vector<int>& list, int& comp, int& assign);
void selectionSort(vector<int>& list, int& comp, int& assign);
void insertionSort(vector<int>& list, int& comp, int& assign);

int main()
{
    vector<int> list1(5000);
    vector<int> list2(5000);
    vector<int> list3(5000);

    int compBubbleSort = 0, compSelectionSort = 0, compInsertionSort = 0;
    int assignBubbleSort = 0, assignSelectionSort = 0, assignInsertionSort = 0;

    fillVector(list1);
    copyVector(list1, list2);
    copyVector(list1, list3);

    bubbleSort(list1, compBubbleSort, assignBubbleSort);
    selectionSort(list2, compSelectionSort, assignSelectionSort);
    insertionSort(list3, compInsertionSort, assignInsertionSort);

    cout << "Number of comparisons---" << endl;
    cout << "  Bubble sort: " << compBubbleSort << endl;
    cout << "  Selection sort: " << compSelectionSort << endl;
    cout << "  Insertion sort: " << compInsertionSort << endl << endl;

    cout << "Number of item assignments---" << endl;
    cout << "  Bubble sort: " << assignBubbleSort << endl;
    cout << "  Selection sort: " << assignSelectionSort << endl;
    cout << "  Insertion sort: " << assignInsertionSort << endl << endl;

    return 0;
}

void fillVector(vector<int>& list)
{
    random_device rd;
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    // Define the range for the random integers
    int min = 1;
    int max = 100000;

    // Create a uniform distribution for the range
    uniform_int_distribution<int> dist(min, max);

    // Generate random integers and store them in the vector
    for (int i = 0; i < list.size(); ++i) {
        list[i] = dist(gen);
    }
}

void copyVector(const vector<int>& source, vector<int>& destination)
{
    for (size_t i = 0; i < source.size(); ++i) {
        destination[i] = source[i];
    }
}

/**
 * Sorts a vector of integers using the bubble sort algorithm.
 * 
 * @param list The vector of integers to be sorted.
 * @param comp The reference to an integer that will store the number of comparisons made during the sorting process.
 * @param assign The reference to an integer that will store the number of assignments made during the sorting process.
 */
void bubbleSort(vector<int>& list, int& comp, int& assign)
{
    comp = 0;
    assign = 0;
    int n = list.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            comp++;
            if (list[j] > list[j + 1]) {
                assign += 3; // For swapping
                swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, then the array is already sorted.
        if (!swapped)
            break;
    }
}

/**
 * Sorts a vector of integers using the selection sort algorithm.
 * 
 * @param list The vector of integers to be sorted.
 * @param comp The number of comparisons made during the sorting process (output parameter).
 * @param assign The number of assignments made during the sorting process (output parameter).
 */
void selectionSort(vector<int>& list, int& comp, int& assign)
{
    int smallestIndex, temp;
    comp = 0;
    assign =0;
    for (int i=0; i<list.size()-1;i++){
        smallestIndex = i;
        for(int minIndex = i+1;minIndex<list.size();minIndex++){
            if(list[minIndex] < list[smallestIndex])
                smallestIndex=minIndex;
            comp++;
        }
        temp = list[smallestIndex];
        list[smallestIndex] = list[i];
        list[i] = temp;
        assign +=3;
    }
}

/**
 * Sorts a vector of integers using the insertion sort algorithm.
 * 
 * @param list The vector to be sorted.
 * @param comp The number of comparisons made during the sorting process (output parameter).
 * @param assign The number of assignments made during the sorting process (output parameter).
 */
void insertionSort(vector<int>& list, int& comp, int& assign)
{
    int firstOutOfOrder, location;
    int temp;
    int length = list.size();
    comp = 0;
    assign = 0;

    for(firstOutOfOrder = 1; firstOutOfOrder < length; firstOutOfOrder++){
        comp++;
        if(list[firstOutOfOrder]<list[firstOutOfOrder-1]){
            temp = list[firstOutOfOrder];
            location = firstOutOfOrder;
            assign +=2;
            do{
                list[location] = list[location - 1];
                assign++;
                location--;
                comp++; // for every iteration of for loop
            } while(location >0 && list[location-1]>temp);
            list[location]=temp;
            assign++;
        }
    }
}
