#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class divisionByZero                    
{                                       
public:                                 
    divisionByZero()                    
    {                                   
        message = "Division by zero";   
    }                                   

    divisionByZero(string str)          
    {                                   
        message = str;                  
    }                                   

    string what()                       
    {                                   
        return message;                 
    }                                   

private:                                
    string message;                     
};                 


int main()
{
	float num1,num2;
	char opr;
	bool done = false;
	string str = "Invalid Input. Your must enter numbers. ";
	cout << fixed << showpoint << setprecision(2);

	try{
		cout << "Enter two numbers: ";
		cin >> num1 >> num2;
		cout << endl;

		if(!cin)
			throw str;
		cout << "Enter operator (+,-,*,/): ";
		cin >> opr;
		cout << endl;

		cout << num1 << " " << opr << num2 << " = ";

		switch(opr){
			case '+':
				cout << num1+num2 << endl;
				break;
			case '-':
				cout << num1-num2 << endl;
				break;
			case '*':
				cout << num1*num2 << endl;
				break;
			case '/':
				do{
					try{
						if(num2==0)
							throw divisionByZero();
						cout << num1/num2 << endl;
						done = true;
					}
					catch(divisionByZero e){
						cerr << e.what();
						cin.clear();
						cin.ignore(100,'\n');
						cout << "Enter in the divisor again: ";
						cin >> num2;
						cout << endl;
						cout << num1 <<" " << opr << " " << num2 << " = ";

					}
				}while(!done);
				break;
			default:
				cout << "Illegal operation entered" << endl;
		}
	}
	catch(string messageStr){
		cout << messageStr << endl;
		cout << "Program terminates!" << endl;
	}
	return 0;
}
  

