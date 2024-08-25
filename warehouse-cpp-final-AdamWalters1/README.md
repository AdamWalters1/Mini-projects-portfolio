[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/UKNqFGJW)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=15000936)
# Warehouse Inventory Management System

![Assignment Meme](imgs/K-YFXZbQiiSDFCc9HaOx3C8k6UcQgksV9NgbJEKTQxY.webp)

## Introduction

In this project, you will develop a console-based Warehouse Inventory Management System for a fictional hardware store. The system will manage the inventory of various appliances, allowing for operations such as checking stock, buying items, and sorting and searching the inventory. The project will incorporate fundamental and advanced concepts of C++, including object-oriented programming, file handling, sorting algorithms, and more.

THIS PROJECT IS TO BE DONE INDIVIDUALLY. ALL WORK MUST BE YOUR OWN. FAILURE TO DO SO WILL RESULT IN A GRADE OF ZERO FOR THE PROJECT AND A VIOLATION OF THE GSST HONOR CODE.

## Requirements

1. Class Design
   - Create a class `Appliance` with the following attributes:
     - `ID` (int): a unique identifier for the appliance
     - `name` (string): the name of the appliance
     - `quantityOrdered` (int): the price of the appliance
     - `stock` (int): the number of appliances in stock
     - `quantitySold` (int): the number of appliances sold
     - `manufacturerPrice` (double): the price at which the store buys the appliance
     - `sellingPrice` (double): the price at which the store sells the appliance
   - Derive classes like `Dishwasher`, `Microwave`, `CookingRange`, and `CircularSaw` from `Appliance` class. Each of these classes should have additional attributes and methods that are specific to the appliance type (e.g. water usage for dishwashers, wattage for microwaves, etc.)
2. Functionality
   - **Load Data**: Inventory data from a text file into a vector of `Appliance` pointers. (Hint: use polymorphism to store different types of appliances in the same vector, you can use pointers in vector to store different types of objects.)
   - **Inventory Management**: Allow adding to the inventory, updating stock as sales are made, and displaying inventory.
   - **Sales**: Implement a function to handle sales transactions, updating inventory and storing sales information for receipt printing.
   - **Sorting**: Implement the merge sort algorithm to sort the appliances by name (i.e. prior to displaying the inventory, the data is sorted and then displayed in an alphabetical order due to the sorting algorithm).
   - **Searching**: Implement a binary search algorithm to search for an appliance by name.
3. User Interface:
   - Implement a simple console-based menu system that allows the user to:
     - Check if an item is in stock
     - Purchase an item
     - Check the price of an item View and sort the entire inventory
     - Print a sales recipt to a file  
4. File I/O
   - **Input**: Read inventory data from the provided text file.
   - **Output**: Print receipt of all purchases to a text file.
5. Error Handling
   - Implement error handling for invalid user input and file I/O errors, **using exceptions**.

## Example Output to Console

```txt
Welcome to the Friendly Hardware Store!
Choose among the following options.
1: To see if an item is in the store.
2: To buy an item.
3. To check the price of an item.
4: To print the inventory.
5: To print receipt to a text file
9: To end the program.
4


                      Friendly Hardware Store

itemID itemName       pOrdered pInStore pSold manufPrice sellingPrice Attribute 
4444   Circular Saw        150      150     0      45.00      125.00  12 Amp 
3333   Cooking Range        50       50     0     450.00      850.00  4 Burners
1111   Dish Washer          20       20     0     250.50      550.50  300 gal/min 
2222   Micro Wave           75       75     0     150.00      400.00  1000 watts

Total Inventory: $102260.00
Total number of items in the store: 295


Welcome to the Friendly Hardware Store!
Choose among the following options.
1: To see if an item is in the store.
2: To buy an item.
3. To check the price of an item.
4: To print the inventory.
5: To print receipt to a text file
9: To end the program.
2

Enter the name of the item: Dish Washer
Enter the number of pieces: 3

Amount Due = $1651.50
Welcome to the Friendly Hardware Store!
Choose among the following options.
1: To see if an item is in the store.
2: To buy an item.
3. To check the price of an item.
4: To print the inventory.
5: To print receipt to a text file
9: To end the program.
2

Enter the name of the item: Micro Wave
Enter the number of pieces: 2

Amount Due = $2451.50
Welcome to the Friendly Hardware Store!
Choose among the following options.
1: To see if an item is in the store.
2: To buy an item.
3. To check the price of an item.
4: To print the inventory.
5: To print receipt to a text file
9: To end the program.
3

Enter the name of the item: Micro Wave
The price of Micro Wave = 400.00.

Welcome to the Friendly Hardware Store!
Choose among the following options.
1: To see if an item is in the store.
2: To buy an item.
3. To check the price of an item.
4: To print the inventory.
5: To print receipt to a text file
9: To end the program.
5 

Receipt printed to file: receipt.txt

Welcome to the Friendly Hardware Store!
Choose among the following options.
1: To see if an item is in the store.
2: To buy an item.
3. To check the price of an item.
4: To print the inventory.
5: To print receipt to a text file
9: To end the program.
9
```

## Example Receipt

```txt
Friendly Hardware Store

Receipt

Item Name      Quantity    Price
Dish Washer    3           1651.50
Micro Wave     2           800.00
Total Amount Due: $2451.50
```

## Grading Rubric

# Grading Rubric for Warehouse Inventory Management System

## Overview

Grades will be awarded based on the following criteria, which evaluate the student's ability to meet the project's objectives, correctly implement functionality, and follow best programming practices.

| Criteria                           | Points | Details                                                                                                 |
| ---------------------------------- | ------ | ------------------------------------------------------------------------------------------------------- |
| **Class Design**                   | 20%    | Complete implementation of `Appliance` and derived classes with all specified attributes and methods.   |
|                                    |        | Correct use of inheritance and polymorphism. Proper encapsulation of class properties and methods.      |
| **Functionality**                  | 30%    | Correct implementation of data loading, inventory management, sales functions, and algorithms.          |
| **User Interface**                 | 20%    | User-friendly console menu that handles all functionalities, including error handling for user inputs.  |
| **File I/O**                       | 10%    | Correct reading from and writing to files, including error handling.                                    |
| **Error Handling**                 | 5%    | Robust error handling across all aspects of the program using exceptions where appropriate.             |
| **Code Quality and Documentation** | 5%     | Well-organized and readable code with adequate comments and documentation. COMMENTS AND DOCUMENTATION MUST BE THOROUGH |
| **Commit History**                           |  10%      |   Regular commits with clear, concise messages that accurately reflect each set of changes made. Good version control practices are followed, demonstrating progress and organization in the development process. |

***NOTE:*** For commit history, to receive credit you must have at least 10 ***MEANINGFUL*** commits. I will be checking for commits on the following days. Failure to have commits on these days will result in a deduction of points. If you finish the project early, you can make commits ahead of time to meet the requirements.

- Tuesday, May 7 by 11:59 PM
- Thursday, May 9 by 11:59 PM
- Tuesday, May 14 by 11:59 PM
- Friday, May 17 by 11:59 PM (DUE DATE of the project)

***Note**: Deductions may occur for issues such as memory leaks, global variables, and lack of modularity. Bonus points are discretionary based on the instructor's evaluation of effort and quality beyond the basic requirements.
