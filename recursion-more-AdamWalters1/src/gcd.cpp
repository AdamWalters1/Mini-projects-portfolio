#include <iostream>

using namespace std;
 
int gcd(int first, int second);

int main() 
{
    int first, second;

    cout << "Please enter the first number: ";
    cin >> first;
    cout << "Please enter the second number: ";
    cin >> second;

    cout << "The greatest common demoninator is " << gcd(first,second) << endl;
    return 0;
}

/**
 * Calculates the greatest common divisor (GCD) of two integers.
 *
 * @param first The first integer.
 * @param second The second integer.
 * @return The GCD of the two integers.
 */
int gcd(int first, int second)
{
    if (second == 0)
        return first;
    else    
        return gcd(second, first%second);
}