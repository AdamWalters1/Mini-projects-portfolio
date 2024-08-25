[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/OtCu-M8O)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=13732824)
# More classes in C++, `static` variables and `const`

## Bank Account

Define the class bankAccount to implement the basic properties of a bank account. An object of this class should store
the following data:

- Account holder’s name (string)
- account number ( int )
- account type (string, checking/saving)
- balance ( double )
- interest rate ( double, Store interest rate as a decimal number.)

Add appropriate member functions to manipulate an object. Use a static member in the class to automatically assign
account numbers. Declare an array of 10 components of type bankAccount to process up to 10 customers and write a program
to illustrate how to use your class.

I will walk you through this. 

## Expected Output

```txt
1: Enter 1 to add a new customer.
2: Enter 2 for an existing customer.
3: Enter 3 to print customers data.
9: Enter 9 to exit the program.
1

Enter customer's name:John

Enter account type (checking/savings):checking

Enter amount to be deposited to open account:300

Enter interest rate (as a percent):2

1: Enter 1 to add a new customer.
2: Enter 2 for an existing customer.
3: Enter 3 to print customers data.
9: Enter 9 to exit the program.
3

Account Holder Name: John
Account Type: checking
Account Number: 1100
Balance: $300.00
Interest Rate: 2.00%
*****************************

1: Enter 1 to add a new customer.
2: Enter 2 for an existing customer.
3: Enter 3 to print customers data.
9: Enter 9 to exit the program.
9
```

## Tests 

The tests for this assignment are designed to evaluate the code from a strict perpsective for certain functions. 
Passing all of the tests indicates a 100, however if tests are not passed the code will be looked into. 


