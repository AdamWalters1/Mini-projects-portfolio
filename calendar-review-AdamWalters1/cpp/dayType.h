
#ifndef H_dayType
#define H_dayType
  
#include <string>
  
using namespace std;

class dayType
{
public:
    void print() const;
    string nextDay() const;
    string prevDay() const; 
    void addDay(int nDays);

    void setDay(string d);
    string getDay() const;

    dayType();
    dayType(string d);

private:
    string weekDay;
};

#endif