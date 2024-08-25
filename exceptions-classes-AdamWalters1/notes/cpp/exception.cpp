#include <iostream>
#include <iostream>
#include <stdexcept> // For std::runtime_error and other standard exceptions

using namespace std;

int divide(int numerator, int denominator) {
    if (denominator == 0) {
        // Throw a runtime_error exception if denominator is 0
        throw runtime_error("Division by zero error");
    }
    return numerator / denominator;
}

int main() {
    try {
        // Attempt to divide 10 by 0 - this will throw an exception
        int result = divide(10, 0);
        cout << "The result is " << result << std::endl;
    } catch (const runtime_error& e) {
        // Catch a runtime_error exception
        cerr << "Caught a runtime error: " << e.what() << std::endl;
    } catch (const exception& e) {
        // Catch other exceptions derived from std::exception
        cerr << "Caught an exception: " << e.what() << std::endl;
    } catch (...) {
        // Catch all other types of exceptions
        cerr << "Caught an unknown exception" << std::endl;
    }

    return 0;
}