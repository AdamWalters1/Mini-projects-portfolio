#include <cassert> // Necessary header file for assert

int main() {
    int x = 5;
    assert(x == 5); // No problem here
    assert(x != 5); // This will fail and terminate the program
    return 0;
}