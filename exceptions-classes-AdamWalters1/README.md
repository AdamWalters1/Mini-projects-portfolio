[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/OeApaDQ3)
# Exceptions with Classes

![Assignment meme](img/r_900421_Uenkt.jpg)
![Other assignment meme](img/meme-dev-humor-c-be-like-134.jpg)

## Assignment

### Program 1

Program 1 builds off of a previous assignment that we have done in the past where we created a calculator that could add, subtract, multiply, and divide two numbers. In this program, we will be adding exception handling to the division function in the calculator.

Redo the program in both Python and C++ and add exception handling to the division function in the calculator. If the user tries to divide by zero, the program should throw an exception and print an error message to the console. You will also be required to put an exception in for a non-numeric/invalid input.

Make sure the program can handle float numbers.

For the Python and C++ versions of program 1, you will have two versions of the program. One that will use a derived class of an exception to give the user a custom error message (such as [`program1_wClass.py`](src/program1/program1_wClass.py)) and one that will use the built-in exception for division by zero (such as [`program1.py`](src/program1/program1.py)).

#### Expected Output

```txt
Enter two numbers: 2 0

Enter operator: + (addition), - (subtraction), * (multiplication), / (division): /

2.00 / 0.00 = Attempted to divide by zero
Enter the divisor: 2

2.00 / 2.00 = 1.00
```

---

### Program 2

Write a program that lets the user perform arithmetic operations on fractions. Fractions are of the form $\frac{a}{b}$, in which $a$ and $b$ are integers and $b \neq 0$. Your program must be menu driven, allowing the user to select the operation (+, -, *, or /) and input the numerator and denominator of each fraction. Furthermore, your program must consist of at least the following functions:

- `menu`
  - This function informs the user about the program’s purpose, explains how to enter data, and allows the user to select the operation.
- `addFractions`
  - This function takes as input four integers representing the numerators and denominators of two fractions, adds the fractions, and returns the numerator and denominator of the result. (Notice that this function has a total of six parameters.)
- `subtractFractions`
  - This function takes as input four integers representing the numerators and denominators of two fractions, subtracts the fractions, and returns the numerator and denominator of the result. (Notice that this function has a total of six parameters.)
- `multiplyFractions`
  - This function takes as input four integers representing the numerators and denominators of two fractions, multiplies the fractions, and returns the numerators and denominators of the result. (Notice that this function has a total of six parameters.)
- `divideFractions`
  - This function takes as input four integers representing the numerators and denominators of two fractions, divides the fractions, and returns the numerator and denominator of the result. (Notice that this function has a total of six parameters.)

This program needs to be able to handle divisions by 0 and non-numeric/invalid inputs.

#### Expected Output

```txt
This program performs operations on fraction. Enter
1 : To add fraction
2 : To subtract fraction
3 : To multiply fraction
4 : To divide fraction
9 : To exit the program
4
For fraction 1
Numerator: Enter an integer: 2


Denominator: Enter an integer: 0

Denominator must be nonzero.
Denominator: Enter an integer: 0

Denominator must be nonzero.
Denominator: Enter an integer: 3


For fraction 2
Numerator: Enter an integer: 3


Denominator: Enter an integer: 4


2/3 / 3/4 = 8/9
This program performs operations on fraction. Enter
1 : To add fraction
2 : To subtract fraction
3 : To multiply fraction
4 : To divide fraction
9 : To exit the program
9
```
