#include <iostream>  
#include <cmath>

using namespace std;

void binToDec(long binaryNumber, int& decimal, int& weight);

int main()
{
    int decimalNumber =0, bitWeight=0;
    long binaryNum;

    cout << "Enter a binary number: ";
    cin >> binaryNum;
    cout << endl;

    binToDec(binaryNum,decimalNumber,bitWeight);
    cout << "Binary number " << binaryNum << " is " << decimalNumber << " in decimal." << endl;

    return 0;
}

void binToDec(long binaryNumber, int& decimal, int& weight)
{
    int bit;
    if(binaryNumber >0){
        bit = binaryNumber %10;
        decimal += bit*pow(2,weight);
        binaryNumber /= 10;
        weight ++;
        binToDec(binaryNumber,decimal, weight);
    }
}
