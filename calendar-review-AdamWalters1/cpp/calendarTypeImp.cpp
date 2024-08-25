

#include <iostream>
#include <cassert>
#include <iomanip>
  
#include "dateType.h"
#include "extDateType.h"
#include "dayType.h" 
#include "calendarType.h"

using namespace std;

void calendarType::setMonth(int m)
{
    firstDate.setMonth(m);
}

void calendarType::setYear(int y){
    firstDate.setYear(y);
}

int calendarType::getMonth(){
    return firstDate.getMonth();
}
int calendarType::getYear(){
    return firstDate.getYear();
}

void calendarType::printCalendar(){
    cout << setw(21) << " ";
    firstDate.printLongMonthYear();
    cout << endl;
    printTitle();
    printDates();
    cout << endl;
}

calendarType::calendarType(){
    firstDate.setDate(1,1,1500);
    firstDay.setDay("Monday");

}

calendarType::calendarType(int m, int y){
    assert(1 <= m && m <= 12 && y >= 1500);
    firstDate.setDate(m,1,y);
    firstDay = firstDayOfMonth();

}
dayType calendarType::firstDayOfMonth(){
    int year = firstDate.getYear();
    extDateType d;
    dayType cDay("Monday");

    for(int y = 1500; y <year; y++){
        d.setYear(y);
        if(d.isLeapYear())
            cDay.addDay(366);
        else
            cDay.addDay(365);
    }
    cDay.addDay(firstDate.numberOfDaysPassed() -1);
    return cDay;
}

void calendarType::printTitle(){
    cout << setw(7) << "Sun" << setw(7) << "Mon"
         << setw(7) << "Tues" << setw(7) << "Wed"
         << setw(7) << "Thurs" << setw(7) << "Fri"
         << setw(7) << "Sat";

}
void calendarType::printDates(){
    static string weekDays[7] = {"Sunday","Monday","Tuesday","Wednesday",
                                "Thursday","Friday","Saturday"};
    int mLength = firstDate.getDaysInMonth();
    int dValue = 1;
    int x;
    dayType d("Sunday");

    for(int x = 0; x < 7; x++)
        if(weekDays[x] == firstDay.getDay())
            break;
    
    if(x !=0)
        cout << setw(7*x) << " ";
    
    d = firstDay;
    while(dValue <= mLength){
        cout << setw(7) << dValue;
        dValue++;

        if(d.getDay() == "Saturday")
            cout << endl;
        d.setDay(d.nextDay());
    }
    if(d.getDay()=="Sunday")
        cout << endl;
}
