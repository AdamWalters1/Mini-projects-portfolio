
#include <iostream>
   
#include "dayType.h"
#include "dateType.h"
#include "extDateType.h"
#include "calendarType.h"

using namespace std; 

int main()
{
    dateType d(1,2,2005);
    extDateType ed(1,2,1984);
    int num;
    ed.printLongDate();
    cout << endl;
    ed.print();
    cout << endl;

    cout << "Days gone in the year: " << ed.numberOfDaysPassed() << endl;
    cout << "Days left in the year: " << ed.numberOfDaysLeft() << endl;
    cout << "Enter number of days left to add: ";
    cin >> num;
    cout << endl;

    ed.incrementDate(num);
    cout << "After increment date: ";
    ed.print();
    cout << endl;

    dayType newDay("Wednesday");
    newDay.print();
    cout << endl;

    cout << "Next day: " << newDay.nextDay() << endl;
    newDay.setDay("Sunday");
    cout << "Set day";
    newDay.print();
    cout << endl;

    cout << "Previous day" << newDay.prevDay () << endl;
    newDay.addDay(12);

    cout << "Added 12 days";
    newDay.print();
    cout << endl;

    calendarType cal(2,2005);
    cal.printCalendar();
    return 0;
}