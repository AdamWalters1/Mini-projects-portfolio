[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/slz3HiC8)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=14896221)
# Searching and Sorting Algorithms

## Sorting Algorithms

There are a number of sorting algorithms that can be used to sort a list of items. The choice of sorting algorithm depends on the size of the list, the nature of the items in the list, and the resources available to the program.

Here are some of the most common sorting algorithms:

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort
- Heap Sort
- Radix Sort
- Counting Sort

Since the choice of sorting algorithm depends on the size of the list, the nature of the items in the list, and the resources available to the program, it is important to understand the time complexity of each sorting algorithm, so that the best algorithm can be chosen for a given situation.

### Time Complexity of Sorting Algorithms

The time complexity of a sorting algorithm is a measure of the amount of time it takes to sort a list of items. The time complexity of a sorting algorithm is usually expressed in terms of the number of comparisons and swaps that are required to sort a list of items.

There is also a space complexity of a sorting algorithm, which is a measure of the amount of memory that is required to sort a list of items. The space complexity of a sorting algorithm is usually expressed in terms of the number of extra memory locations that are required to sort a list of items.

You can see a table of the time complexity of some of the most common sorting algorithms here [Time Complexity of Sorting Algorithms](https://www.geeksforgeeks.org/time-complexities-of-all-sorting-algorithms/).

Another Resource is [Big-O Cheat Sheet](https://www.bigocheatsheet.com/).

Given this information, you can choose the best sorting algorithm for a given situation.

### Bubble Sort

Bubble Sort is a simple sorting algorithm that works by repeatedly stepping through the list to be sorted, comparing each pair of adjacent items and swapping them if they are in the wrong order. The pass through the list is repeated until no swaps are needed, which indicates that the list is sorted. Here's the pseudocode for Bubble Sort:

```plaintext
procedure bubbleSort( A : list of sortable items )
    n = length(A)
    repeat 
        swapped = false
        for i = 1 to n-1 inclusive do
            if A[i-1] > A[i] then
                swap( A[i-1], A[i] )
                swapped = true
            end if
        end for
        n = n - 1
    until not swapped
end procedure
```

Good for small datasets, however because of its $\mathcal{O}(n^2)$ time complexity, it is not recommended for large datasets.

## Searching Algorithms

Searching algorithms, like sorting algorithms, can be used for nearly any type of data, but choosing which one to use depends on the size of the data and the nature of the data. Two of the most common searching algorithms are:

- Linear/Sequential Search
- Binary Search

### Linear/Sequential Search

Linear/Sequential Search is a simple searching algorithm that works by sequentially checking each element in a list until a match is found or the whole list has been searched. Here's the pseudocode for Linear/Sequential Search:

```plaintext
procedure linearSearch( A : list of items, target : value to find )
    for i = 0 to length(A) - 1 do
        if A[i] == target then
            return i // Target found, return the index
        end if
    end for
    return -1 // Target not found
end procedure
```

Assuming the list is unsorted, the time complexity of Linear/Sequential Search is $\mathcal{O}(n)$ at worst if the item being looked for is the last one found. If the thing it is looking for is the first element in the list, it will be found in the first comparison, giving a time complexity of $\mathcal{O}(1)$.

## Assignment

### Program 1

You'll be writing a program with three functions

1. **`remove`**
   - Takes three parameters: an array of integers, the number of elements in the array, and an integer (say,
     removeItem). The function should find and delete the first occurrence of removeItem in the array. If the
     value does not exist or the array is empty, output an appropriate message. (Note that after deleting the
     element, the number of elements in the array is reduced by 1.) Assume that the array is unsorted. Use the
     Linear/Sequential Search algorithm to find the element to be removed.
2. **`removeAt`**
   - Takes three parameters: an array of integers, the number of elements in the array, and an integer (say, index).
     The function should delete the array element indicated by index. If index is out of range or the array is
     empty, output an appropriate message. (Note that after deleting the element, the number of elements in the
     array is reduced by 1.) Assume that the array is unsorted.
3. **`removeAll`**
   - Takes three parameters: an array of integers, the number of elements in the array, and an integer (say,
     removeItem). The function should find and delete all the occurrences of removeItem in the array. If the value
     does not exist or the array is empty, output an appropriate message. (Note that after deleting the element, the number of elements in the array is reduced.) Assume that the array is unsorted.
4. **`insertAt`**
   - Takes four parameters: an array of integers, the number of elements in the array, an integer (say, insertItem),
     and an integer (say, index). The function should insert insertItem in the array at the position specified by
     index. If index is out of range, output an appropriate message. (Note that index must be between 0 and the
     number of elements in the array; that is, $0 \leq index < \text{the number of elements in the array}$.) Assume that the array is unsorted.
5. **`bubbleSort`**
   - Takes two parameters: an array of integers and the number of elements in the array. This function sorts the array using the Bubble Sort algorithm, a straightforward comparison-based sorting method. It repeatedly traverses the list, compares adjacent elements, and swaps them if they are in the wrong order. This process repeats until no more swaps are needed, indicating that the array is sorted. Bubble Sort is known for its simplicity but is inefficient for large data sets with a time complexity of \(\mathcal{O}(n^2)\).

6. **`reverseOrder`**
   - Takes two parameters: an array of integers and the number of elements in the array. This function reverses the order of the elements in the array. It works by swapping the first element with the last, the second element with the second last, and so on, until it reaches the middle of the array. This function is useful for inverting the sequence of a list, and its performance is efficient with a time complexity of \(\mathcal{O}(n/2)\), simplifying to \(\mathcal{O}(n)\).

7. **`isSorted`**
   - Takes two parameters: an array of integers and the number of elements in the array. This function checks if the array is sorted in ascending order. It iteratively compares each element with the next one; if any element is found that is greater than the following element, the function returns `false`, indicating that the array is not sorted. If no such pair is found, it returns `true`. This utility function is particularly useful in algorithms where the sorted nature of the array is a prerequisite or for validating the outcome of sorting operations. Its time complexity is \(\mathcal{O}(n)\), as it may need to check each element in the worst case.

8. **`printOperation`**
   - Takes three parameters: a string representing the name of the operation, an array of integers, and the number of elements in the array. This function prints the name of the operation followed by the contents of the array. It formats the output so that the operation name is left-aligned, ensuring clarity and readability in displaying results. This function is especially useful for debugging or visually verifying the intermediate steps in a series of array operations.

I have added some documentation and TODO's to guide you along the path. I have left the `main.cpp` file for you so 
that you can see how the functions are being called. You can run the program and see the output.

### Testing 

You can test the program by running the `list_operations_tests.cpp` file; however, if your main program is 
outputting correct results it is likely that the tests will pass. The tests themselves are also run on GitHub each 
time that your code is pushed. If you see a green checkmark, then your code has passed the tests and you will 
receive a 100. If you see a red X, then your code has failed the tests and you will receive a partial grade. 

If you encounter any issues with the tests, please let me know.

## References

- [Time Complexity of Sorting Algorithms](https://www.geeksforgeeks.org/time-complexities-of-all-sorting-algorithms/)
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/)
