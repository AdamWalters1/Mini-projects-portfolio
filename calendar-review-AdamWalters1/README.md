[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/dW9YLKlQ)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=14152275)
# Review of Classes and Inheritance

## Calendar

Using the classes `extDateType` and `dayType`

Using the classes `extDateType` and `dayType`, design the
class `calendarType` so that, given the month and the year, we can print the calendar for that month. To print a
monthly calendar, you must know the first day of the month and the number of days in that month. Thus, you must store the first day of the month, which is of the form `dayType`, and the month and the year of the calendar. Clearly, the month and the year can be stored in an object of the form `extDateType` by setting the day component of the date to 1 and the month and year as specified by the user. Thus, the class `calendarType` has two member variables: an object of the type `dayType` and an object of the type `extDateType`.

Design the class `calendarType` so that the program can print a calendar for any month starting January 1, 1500. Note
that the day for January 1 of the year 1500 is a Monday. To calculate the first day of a month, you can add the appropriate days to Monday of January 1, 1500.

For the class `calendarType`, include the following operations:

- Determine the first day of the month for which the calendar will be printed. Call this operation `firstDayOfMonth`.
- Set the month
- Set the year
- Return the month
- Return the year
- Print th calendar for the particular month.
- Add the appropriate constructors to initialize the objects of the class `calendarType`.
- Write the definitions of the member functions of the class `calendarType` to implement the operations of the class
  `calendarType`.
- Write a test program to print the calendar for either a particular month or a particular year. For example, the
  calendar for the month of May 2019 is as follows:

```txt
                   September 2017
    Sun    Mon    Tue    Wed    Thu    Fri    Sat
                                         1      2
      3      4      5      6      7      8      9
     10     11     12     13     14     15     16
     17     18     19     20     21     22     23
     24     25     26     27     28     29     30
```

## Expected Output

```txt
June 10, 1981
6-10-1981
Days gone in the year: 161
Days left in the Year: 204
Enter number of days to be added:3

After increment date: 6-13-1981
Wednesday
Next Day: Thursday
Set Day: Sunday
Previous Day: Saturday
Add days: Friday
                     September 2017
    Sun    Mon    Tue    Wed    Thu    Fri    Sat
                                         1      2
      3      4      5      6      7      8      9
     10     11     12     13     14     15     16
     17     18     19     20     21     22     23
     24     25     26     27     28     29     30
```
