#include "../src/list_operations.cpp"
#include <gtest/gtest.h>
#include <iostream>

// Test for Bubble Sort Functionality
TEST(ListOperationsTest, BubbleSort) {
    int list[ARRAY_SIZE] = {10, 5, 15, 8, 25, 20, 3, 18,
                            12, 7, 22, 1, 4, 11, 6,
                            14, 9, 2, 23, 17};
    int len = ARRAY_SIZE;
    bubbleSort(list, len);
    for (int i = 0; i < len - 1; ++i) {
        EXPECT_LE(list[i], list[i + 1]) << "Array is not sorted at index " << i;
    }
}

// Test for Insert At Function
TEST(ListOperationsTest, InsertAt) {
    int list[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    int len = 5;
    insertAt(list, len, 100, 2); // Insert 100 at position 2
    EXPECT_EQ(list[2], 100) << "Insert at index did not place the item correctly.";
    EXPECT_EQ(len, 6) << "Length did not update correctly after insertion.";
}

// Test for Remove Function
TEST(ListOperationsTest, Remove) {
    int list[ARRAY_SIZE] = {1, 100, 2, 3, 4, 5};
    int len = 6;
    remove(list, len, 100);
    EXPECT_EQ(len, 5) << "Length did not decrease after removal.";
    for (int i = 0; i < len; ++i) {
        EXPECT_NE(list[i], 100) << "Item was not removed from the list.";
    }
}

// Test for Remove At Function
TEST(ListOperationsTest, RemoveAt) {
    int list[ARRAY_SIZE] = {1, 100, 2, 3, 4, 5};
    int len = 6;
    removeAt(list, len, 1); // Remove item at index 1
    EXPECT_EQ(len, 5) << "Length did not decrease after removal.";
    EXPECT_NE(list[1], 100) << "Item at index was not removed.";
}

// Test for Remove All Function
TEST(ListOperationsTest, RemoveAll) {
    int list[ARRAY_SIZE] = {100, 1, 100, 2, 100, 3, 100, 4, 5};
    int len = 9;
    removeAll(list, len, 100); // Remove all 100s
    EXPECT_EQ(len, 5) << "Length did not decrease correctly after removing all instances.";
    for (int i = 0; i < len; ++i) {
        EXPECT_NE(list[i], 100) << "Not all instances were removed.";
    }
}

// Test for Reverse Order Function
TEST(ListOperationsTest, ReverseOrder) {
    int list[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    int expected[ARRAY_SIZE] = {5, 4, 3, 2, 1};
    int len = 5;
    reverseOrder(list, len);
    for (int i = 0; i < len; ++i) {
        EXPECT_EQ(list[i], expected[i]) << "Array was not reversed correctly.";
    }
}

// Test for isSorted Function
TEST(ListOperationsTest, IsSorted) {
    int sortedList[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    int unsortedList[ARRAY_SIZE] = {5, 4, 3, 2, 1};
    EXPECT_TRUE(isSorted(sortedList, 5)) << "Function incorrectly identified the list as unsorted.";
    EXPECT_FALSE(isSorted(unsortedList, 5)) << "Function incorrectly identified the list as sorted.";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
