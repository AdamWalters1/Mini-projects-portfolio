#include <stdexcept> // Necessary header file for std::runtime_error

// If you use `using namespace std;` you don't need to use `std::` before `runtime_error`

int main() {
    int x = 10;
    if (x > 5) {
        throw std::runtime_error("x should not be greater than 5");
    }
    return 0;
}