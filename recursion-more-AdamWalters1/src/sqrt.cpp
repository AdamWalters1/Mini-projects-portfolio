#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double squareRoot(double num, double a, double episoln);

int main() 
{
    double num, epsilon;
    cout << "Enter a nonnegative real number: ";
    cin >> num;
    epsilon = .001;
    if (num < 0) {
        cout << "Error: Entered number is negative." << endl;
    } else {
        double result = squareRoot(num, num, epsilon);
        cout << "Square root of " << num << " within tolerance " << epsilon << " is approximately: " 
        << fixed << setprecision(3) << result << endl;
    }

    return 0;
}

/**
 * Calculates the square root of a number using the Newton's method.
 * 
 * @param num The number for which the square root is to be calculated.
 * @param a The initial guess for the square root.
 * @param epsilon The desired level of accuracy.
 * @return The square root of the given number.
 */
double squareRoot(double num, double a, double epsilon)
{
    if (abs(a * a - num) <= epsilon) {
        return a;
    } else {
        double next_a = (a * a + num) / (2 * a);
        return squareRoot(num, next_a, epsilon);
    }
}
