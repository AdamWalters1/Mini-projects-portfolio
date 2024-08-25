#include <iostream>
#include <string>

using namespace std;

/**
 * Class Time - Represents a specific time of day with hours, minutes, and seconds.
 */
class Time {
public:
    /**
     * Constructor for the Time class.
     * @param hr Hours part of the time.
     * @param min Minutes part of the time.
     * @param sec Seconds part of the time.
     */
    Time(int hr, int min, int sec) {
        hours = new int(hr);
        minutes = new int(min);
        seconds = new int(sec);
    }

    /**
     * Destructor for the Time class. Cleans up allocated memory to prevent memory leaks.
     */
    ~Time() {
        delete hours;
        delete minutes;
        delete seconds;
    }

    /**
     * Prints the time in 24-hour format based on AM or PM input.
     * @param am_pm A string representing either "AM" or "PM".
     */
    void print24HourTime(const string& am_pm) const {
        if(am_pm == "AM"){
            if(*hours == 12)
                *hours = 0;
        }
        else if(am_pm == "PM"){
            if(*hours != 12)
                *hours += 12;
        }
        cout << *hours <<":" <<*minutes << ":" << *seconds << endl;
    }

private:
    int* hours;   // Pointer to store hours.
    int* minutes; // Pointer to store minutes.
    int* seconds; // Pointer to store seconds.
};

/**
 * Abstract class InvalidTimeException - Represents a base class for time validation exceptions.
 */
class InvalidTimeException {
public:
    /**
     * Pure virtual function that returns the error message.
     * @return A string representing the error message.
     */
    virtual string what() = 0;
};

/**
 * Class invalidHr - Represents an exception for invalid hour input.
 */
class invalidHr : public InvalidTimeException {
public:
    /**
     * Constructor for invalidHr.
     * @param str Optional custom error message.
     */
    invalidHr(const string& str = "The value of hr must be between 0 and 12"){
        message = str;
    }
    /**
     * Returns the error message.
     * @return A string representing the error message.
     */
    string what() override { return message; }

private:
    string message; // Error message
};

/**
 * Class invalidMin - Represents an exception for invalid minute input.
 */
class invalidMin : public InvalidTimeException {
public:
    invalidMin(const string& str = "The value of minutes must be between 0 and 59.") : message(str) {}
    string what() override { return message; }

private:
    string message; // Error message
};

/**
 * Class invalidSec - Represents an exception for invalid second input.
 */
class invalidSec : public InvalidTimeException {
public:
    /**
     * Constructor for invalidSec.
     * @param str Optional custom error message.
     */
    invalidSec(const string& str = "The value of seconds must be between 0 and 59.") : message(str) {}
    string what() override { return message; }

private:
    string message; // Error message
};

int getHours(); 
int getMinutes(); 
int getSeconds();

/**
 * Main function of the program.
 * @return Returns 0 upon successful completion.
 */
int main() {
    // Example usage of Time and handling exceptions
    int hr = getHours(); 
    int min = getMinutes(); 
    int sec = getSeconds(); 
    string am_pm;

    cout << "Enter AM or PM: ";
    cin >> am_pm;
    cout << endl;

    Time* time = nullptr;
    try{
        time = new Time(hr,min,sec);
        time -> print24HourTime(am_pm);
    } catch (InvalidTimeException& e){
        cout << e.what() << endl;
    } catch (...){
        cout << "An unexpected error occurred." << endl;
    }

    delete time;    
    return 0;
}

/**
 * Prompts the user for the hours input and validates it.
 * @return Valid hours as an integer.
 */
int getHours() {
    int hr = 0;
    while (true){
        cout << "Enter hours (0-12): ";
        cin >> hr;
        if(cin.fail()){
            cin.clear();
            cin.ignore(100,'\n');
            cout << "You have an invalid input. Please enter a number: ";
            continue;
        }
        if(hr >= 0 && hr <= 12)
            return hr;
        else
            throw invalidHr();
    }
}

/**
 * Prompts the user for the minutes input and validates it.
 * @return Valid minutes as an integer.
 */
int getMinutes() {
    int min = 0;
    while (true){
        cout << "Enter minutes (0-59): ";
        cin >> min;
        if(cin.fail()){
            cin.clear();
            cin.ignore(100,'\n');
            cout << "You have an invalid input. Please enter a number: ";
            continue;
        }
        if(min >= 0 && min <= 59)
            return min;
        else
            throw invalidMin();
    }
}

/**
 * Prompts the user for the seconds input and validates it.
 * @return Valid seconds as an integer.
 */
int getSeconds() {
    int sec = 0;
    while (true){
        cout << "Enter seconds (0-59): ";
        cin >> sec;
        if(cin.fail()){
            cin.clear();
            cin.ignore(100,'\n');
            cout << "You have an invalid input. Please enter a number: ";
            continue;
        }
        if(sec >= 0 && sec <= 59)
            return sec;
        else
            throw invalidSec();
    }
}
