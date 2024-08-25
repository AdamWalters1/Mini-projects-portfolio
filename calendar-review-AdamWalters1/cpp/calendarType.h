
#ifndef calendarType_h
#define calendarType_h
 
#include "dateType.h" 
#include "extDateType.h"
#include "dayType.h"
  
class calendarType
{
public:
    void setMonth(int m);
    void setYear(int y); 

    int getMonth();
    int getYear();

    void printCalendar();

    calendarType();
    calendarType(int m, int y);

private:

    dayType firstDayOfMonth();

    void printTitle();
    void printDates();

    extDateType firstDate;
    dayType  firstDay;
};


#endif