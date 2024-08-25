#include <cstring> 
#include <cctype> 
#include <iostream>

using namespace std;

int main()
{
    char str[81];
    int len;
    int i = 0;
    

    cout << "Please enter a string to be uppercased" << endl;
    cin.getline(str,81);
    len = strlen(str);
    for(i;i < len;i++){
        str[i] = toupper(str[i]);
    }
    cout << str << endl;

    return 0;
}