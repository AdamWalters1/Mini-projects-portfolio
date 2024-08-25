#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void addFractions(int num1, int num2, int den1, int den2,
				  int& numfrac, int& denfrac);
void subtractFractions(int num1, int num2, int den1, int den2,
				       int& numfrac, int& denfrac);
void multiplyFractions(int num1, int num2, int den1, int den2,
				       int& numfrac, int& denfrac);
void divideFractions(int num1, int num2, int den1, int den2,
				     int& numfrac, int& denfrac, bool& flag);

void menu();
void getFraction(int& numerator, int& denominator);

void showResult(char operation, int num1, int num2, int den1, int den2,
				  int numfrac, int denfrac);
int getNum();

int main()
{
    int numerator1, numerator2, denominator1, denominator2;
    int resultnum, resultdeno;

    int choice;

    bool flag = false;

    menu();
    cin >> choice;

    while (choice != 9)
    {
        cout << "For fraction 1" << endl;
        getFraction(numerator1, denominator1);
        cout << endl;

        cout << "For fraction 2" << endl;
        getFraction(numerator2, denominator2);
        cout << endl;

        switch (choice)
        {
		case 1:
            addFractions(numerator1, numerator2,
                         denominator1, denominator2,
                         resultnum, resultdeno);
            showResult('+', numerator1, numerator2,
                        denominator1, denominator2,
                        resultnum, resultdeno);
            break;
        case 2:
            subtractFractions(numerator1, numerator2,
						     denominator1, denominator2,
							 resultnum, resultdeno);
            showResult('-', numerator1, numerator2,
                        denominator1, denominator2,
                        resultnum, resultdeno);
            break;
        case 3:
            multiplyFractions(numerator1, numerator2,
                             denominator1, denominator2,
                             resultnum, resultdeno);
            showResult('*', numerator1, numerator2,
                        denominator1, denominator2,
                        resultnum, resultdeno);
            break;
        case 4:
            divideFractions(numerator1, numerator2,
                            denominator1, denominator2,
                            resultnum, resultdeno, flag);
            if (!flag)
                showResult('/', numerator1, numerator2,
                            denominator1, denominator2,
                            resultnum, resultdeno);
            else
                cout << "****  Try again!!!  ****"<<endl;
            break;
        default:
            cout << "Invalid selection." << endl;
        }

        menu();
        cin >> choice;
    }

    return 0;
}

void addFractions(int num1, int num2, int den1, int den2,
				  int& numfrac, int& denfrac)
{
    numfrac = num1 * den2 + num2 * den1;
    denfrac = den1 * den2;
}

void subtractFractions(int num1, int num2, int den1, int den2,
				  int& numfrac, int& denfrac)
{
    numfrac = num1 * den2 - num2 * den1;
    denfrac = den1 * den2;
}

void multiplyFractions(int num1, int num2, int den1, int den2,
				  int& numfrac, int& denfrac)
{
    numfrac = num1 * num2;
    denfrac = den1 * den2;
}

void divideFractions(int num1, int num2, int den1, int den2,
				  int& numfrac, int& denfrac, bool& flag)
{
    // TODO: Fill in your code here
    // Check for division by zero 
     try {
        if (num2 == 0) {
            throw string("Cannot divide by zero.");
        }
        numfrac = num1 * den2;
        denfrac = den1 * num2;
    } catch (const string& errorMsg) {
        cout << errorMsg << endl;
        flag = true;
    }
}

void menu()
{
    cout << "This program performs operations on fraction. Enter"
         << endl;
    cout << "1 : To add fraction" << endl;
    cout << "2 : To subtract fraction" << endl;
    cout << "3 : To multiply fraction" << endl;
    cout << "4 : To divide fraction" << endl;
    cout << "9 : To exit the program" << endl;
}

void getFraction(int& numerator, int& denominator)
{
    // TODO: Fill in your code here
    bool done = false;
    do
    {
        try
        {
            cout << "Numerator: Enter an integer: ";
            cin >> numerator;
            cout << endl;

            cout << "Denominator: Enter an integer: ";
            cin >> denominator;
            cout << endl;

            if (denominator == 0)
                throw string("Denominator must be nonzero.");

            done = true;
        }
        catch (const string& message)
        {
            cout << message << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    } while (!done);
}

void showResult(char operation, int num1, int num2, int den1, int den2,
                int numfrac, int denfrac)
{
    cout << num1 << "/" << den1;

    switch (operation)
    {
    case '+':
        cout << " + ";
        break;
    case '-':
        cout << " - ";
        break;
    case '*':
        cout << " * ";
        break;
    case '/':
        cout << " / ";
        break;
    default:
        cout << "Invalid operation." << endl;
    }

	cout << num2 << "/" << den2 << " = "
         << numfrac << "/" << denfrac << endl;
}

int getNum()
{
    bool done = false;
    int number = 0;

    string str =
            "The input stream is in the fail state.";

    do
    {
        try
        {
            cout << "Enter an integer: ";
            cin >> number;
            cout << endl;

            if (!cin)
                throw str;

            done = true;
        }
        catch (string messageStr)
        {
            cout << messageStr << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
    while (!done);

    return number;
}
