[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/kpfuECUa)

# Exception Handling in Python and C++ with your

![Assignment Meme](img/programmerhumor-io-programming-memes-edfc502b5cef531-608x570.jpg)

## Objective

The goal of this assignment is to deepen your understanding of exception handling in both Python and C++. You will create two programs: one in Python and one in C++, which will accept time input (hours, minutes, seconds) from the user, validate the input, and convert it to a 24-hour format based on AM or PM input. You'll practice defining and using custom exceptions for input validation.

## Requirements

### Common Requirements for Both Languages

- Your program must prompt the user for hours, minutes, seconds, and whether it's AM or PM.
- Validate the user inputs:
  - Hours must be between 0 and 12.
  - Minutes and seconds must be between 0 and 59.
  - AM/PM input must be either "AM" or "PM" (case-insensitive).
- If an invalid input is provided, the program should raise and handle a custom exception, informing the user of the invalid input and prompting for it again.
- After successfully receiving valid inputs, your program should convert the time to a 24-hour format and display it.

### Specific Requirements

#### Python

- Define custom exception classes for invalid hours, minutes, and seconds.
- Use a `try-except` block to handle exceptions.
- Utilize the `input()` function to receive user inputs.
- Use functions to modularize your code (e.g., `get_hours()`, `get_minutes()`, `get_seconds()`, `print_24_hour_time()`).

#### C++

This version of the program will be a "bit" more challenging. You will be required to use pointers and dynamic memory allocation to store the user inputs. You will also need to use `try-catch` blocks to handle exceptions.

1. **Classes**:
   - **Time Class**: Create a `Time` class that encapsulates the hours, minutes, and seconds as private pointer variables. This class should have:
     - A constructor that takes three integers (hours, minutes, seconds) and allocates memory for each.
     - A destructor that deallocates the memory for these pointers.
     - A member function `print24HourTime` that takes a string (AM/PM) and prints the time in 24-hour format.
   - **InvalidTimeException Class**: Create an abstract class `InvalidTimeException` that will serve as a base class for specific time-related exceptions. This class should have:
     - A pure virtual function `what` that returns a string message.
   - **invalidHr, invalidMin, invalidSec Classes**: Each of these classes should inherit from `InvalidTimeException` and represent specific exceptions for invalid hour, minute, and second inputs, respectively. They should override the `what` method to return a custom error message.

2. **Functions**:
   - **getHours**: A function that prompts the user to enter hours, validates the input to be between 0 and 12 (inclusive), and returns the input as an integer. If the input is invalid, it should throw an `invalidHr` exception.
   - **getMinutes** and **getSeconds**: Functions similar to `getHours`, but `getMinutes` validates the input to be between 0 and 59 for minutes, and `getSeconds` does the same for seconds. They should throw `invalidMin` and `invalidSec` exceptions, respectively, for invalid inputs.

3. **Exception Handling**:
   - Use try-catch blocks in your `main` function to catch and handle the exceptions thrown by `getHours`, `getMinutes`, and `getSeconds`. Print the error messages to the user.

4. **Pointers**:
   - Use pointers for the hours, minutes, and seconds in the `Time` class.
   - Demonstrate dynamic memory allocation and deallocation for these pointers in the `Time` class constructor and destructor.
   - In `main`, dynamically create a `Time` object using the validated inputs and then delete it after use to avoid memory leaks.

5. **Main Function**:
   - In `main`, prompt the user to enter hours, minutes, seconds, and whether it's AM or PM. Use the functions and classes you've created to validate the inputs, handle exceptions, and print the time in 24-hour format.

## Expected Output

Your program should interact with the user as follows

```txt
Enter hours: 12 

Enter minutes: 30

Enter seconds: 45

Enter AM or PM: am

The 24-hour time is 00:30:45
```
