
#ifndef extDateType_H
#define extDateType_H

#include <string>
  
#include "dateType.h" 

using namespace std;
 
class extDateType: public dateType
{
public:
    void printLongDate(); 
    void setDate(int, int, int);
    void setMonth(int m);

    void printLongMonthYear();

    extDateType();
    extDateType(int, int, int);

private:
    string month;
};

#endif