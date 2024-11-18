


## Assignment

### Program 1

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


### Testing 

You can test the program by running the `list_operations_tests.cpp` file; however, if your main program is 
outputting correct results it is likely that the tests will pass. The tests themselves are also run on GitHub each 
time that your code is pushed. If you see a green checkmark, then your code has passed the tests and you will 
receive a 100. If you see a red X, then your code has failed the tests and you will receive a partial grade. 


