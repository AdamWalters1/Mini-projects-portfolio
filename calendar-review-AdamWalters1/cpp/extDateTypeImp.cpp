#include <iostream>
#include <string>
#include "dateType.h"
#include "extDateType.h"
  
using namespace std;

void extDateType::printLongDate()
{
    cout << month << " " << getDay() << ", " << getYear();
}
 
void extDateType::printLongMonthYear()
{
    cout << month << " " << getYear();

}

void extDateType::setDate(int m, int d, int y) 
{
    static string months[13] = {"", "January", "February", "March", "April", 
                           "May", "June", "July", "August", 
                            "September", "October", "November", "December"};

    dateType::setDate(m, d, y);

    month = months[m];
}

void extDateType::setMonth(int m)
{
    static string months[13] = {"", "January", "February", "March", "April", 
                                "May", "June", "July", "August", 
                                "September", "October", "November", "December"};
    dateType::setMonth(m);
    month = months[m];
}

extDateType::extDateType()
{
    month = "January";
}

extDateType::extDateType(int m, int n, int d)
            : dateType(m,n,d)
{
    static string months[13] = {"", "January", "February", "March", "April", 
                                "May", "June", "July", "August", 
                                "September", "October", "November", "December"};
    month = months[m];
}

