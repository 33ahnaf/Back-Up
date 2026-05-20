#include <iostream>

using namespace std;

int main(){
    unsigned short int is_Prime;
    for (int i = 0; i < 101; i++)
    {
        if (i == 2)
        {
            is_Prime = 1;
        }
        else if (i < 2)
        {
            is_Prime = 0;
        }
        else
        {
            for (int j = 2; j < i; j++)
            {
                if ((i%j) == 0)
                {
                    is_Prime = 0;
                    break;
                }
                else
                {
                    is_Prime = 1;
                }
            }
        }
        if (is_Prime == 1)
        {
            cout << i << "\n";
        }
    }
    return 0;
}