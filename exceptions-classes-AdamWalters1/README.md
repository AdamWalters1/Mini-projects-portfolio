# Exceptions with classses
## Assignment

### Program 1

Program 1 builds off of a previous assignment that I have did in the past where we created a calculator that could add, subtract, multiply, and divide two numbers. In this program, I added be adding exception handling to the division function in the calculator.

I did the program in both Python and C++ and add exception handling to the division function in the calculator. If the user tries to divide by zero, the program should throw an exception and print an error message to the console. I also put an exception in for a non-numeric/invalid input.

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

Wrote a program that lets the user perform arithmetic operations on fractions. Fractions are of the form $\frac{a}{b}$, in which $a$ and $b$ are integers and $b \neq 0$. Your program must be menu driven, allowing the user to select the operation (+, -, *, or /) and input the numerator and denominator of each fraction. The program consists of at least the following functions:

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
