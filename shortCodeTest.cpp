#include <iostream>
#include <string>
#include <sstream>


#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

using namespace std;

// int* func(){
//     int array[2];
//     array[0] = 0;
//     array[1] = 1;
//     int*intPtr = &array[0]; 
//     return intPtr;
// }

int main(){

    
    const clock_t start = clock();
 
    int sum = 0;    
    for (int i = 1; i<999999999; i++){
        sum = sum +1;
    }

    clock_t timeElapsed = clock() - start;
    unsigned msElapsed = timeElapsed / CLOCKS_PER_MS;


    
    cout.precision(17);
    cout << "Pi: " << fixed << msElapsed << endl;


    
}

