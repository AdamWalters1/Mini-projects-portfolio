
# C++ arrays
## Description

Program to help understand the basics of arrays in C++.

## Objectives

- To gain experience with arrays in C++
- To be able to use arrays within functions to solve a problem.

## Program 1: Uppercase Letters

Write a program that reads a string from the user and prints it out in all uppercase letters.

Make the array a character array.

## Program 2: Answer Key

A teacher needs help in grading a True/False test. The students' IDs and test asnwers are stored in a file. The first entry in the file is the answer key. Each subsequent entry in the file is a student's ID followed by their answers. For example,

```text
ABCD54301 TFTFTFTT TFTFTFFTTTFT 
```

The student ID is `ABCD54301` and their answer to question 1 is True, their answer to question 2 is False, etc. The student did not answer question 9. The exam has 20 questions and the class has more than 150 students.

Each correct answer is worth 2 points. Each wrong answer is worth -1 point. Each question left blank is worth 0 points.

example output,

```text
ABCD54301 TFTFTFTT TFTFTFFTTTFT 25 F
```

Assume the following grade scale:

- A: 90-100
- B: 80-89.99
- C: 70-79.99
- D: 60-69.99
- F: 0-59.99

