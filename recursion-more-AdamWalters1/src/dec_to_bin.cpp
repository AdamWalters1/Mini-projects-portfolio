#include <iostream> 

using namespace std;

void decToBin(int num, int base);

int main()
{
    int num;
    cout << "Enter a decimal number: ";
    cin >> num;
    cout << "Binary representation: ";
    decToBin(num, 2);
    cout << endl;

    return 0; 
}

/**
 * Converts a decimal number to its binary representation.
 * 
 * @param num The decimal number to be converted.
 * @param base The base to convert the decimal number to.
 */
void decToBin(int num, int base)
{
    if (num > 0) {
        decToBin(num / base, base);
        cout << num % base;
    }
}
