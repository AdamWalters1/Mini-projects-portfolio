#include <iostream>
 
using namespace std;
 
int largest(const int list[], int lowerIndex, int upperIndex);


int main() 
{
    int list[] = {10000, 2000000, 5, 56,452345, 556, 2135,9,877,1003};
    cout << "The largest element in the list is: " << largest(list,0,6) << endl;
    return 0;
}

int largest(const int list[], int lowerIndex, int upperIndex){
    int max;

    if (lowerIndex == upperIndex)
        return list[lowerIndex];
    else{
        max = largest(list,lowerIndex++,upperIndex);
        if(list[lowerIndex] >= max)
            return list[lowerIndex];
        else 
            return max;
        
    }
}
