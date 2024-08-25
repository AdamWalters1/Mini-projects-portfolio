#ifndef SEARCH_SORT_1_LIST_OPERATIONS_HPP
#define SEARCH_SORT_1_LIST_OPERATIONS_HPP

#include <iostream>
#include <iomanip>

using namespace std;

const int ARRAY_SIZE = 20;

void remove(int list[], int& len, int removeItem);
void removeAt(int list[], int& len, int index);
void removeAll(int list[], int& len, int removeItem);
void insertAt(int list[], int& len, int insertItem, int index);
void reverseOrder(int list[], int len);
void printOperation(const string& operation, const int *list, int len);
void bubbleSort(int list[], int len);
bool isSorted(const int list[], int len);



#endif //SEARCH_SORT_1_LIST_OPERATIONS_HPP
