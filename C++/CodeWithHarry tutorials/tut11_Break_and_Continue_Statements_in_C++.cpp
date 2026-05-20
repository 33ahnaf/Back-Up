#include <iostream>

using namespace std;

int main(){
    // ********** break **********
    for (int i = 0; i < 101; i++)
    {
        if (i == 50)
        {
            break;
        }
        cout << i << "\n";
    }
    
    // ********** continue **********
    for (int i = 0; i < 101; i++)
    {
        if (i%2 == 1)
        {
            continue;
        }
        cout << i << "\n";
    }
    return 0;
}