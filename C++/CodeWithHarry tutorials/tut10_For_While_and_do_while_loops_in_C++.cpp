#include <iostream>

using namespace std;

int main(){

    // ********** for loop **********
    // for (initialization, condition, updation)
    // {
    //     loop body(C++ code)
    // }

    // Example of for loop:
    for (int i = 1; i < 101; i++)
    {
        cout << i << "\n";
    }

    // Example of infinite for loop:
    for (int i = 0; true; i++)
    {
        cout << i << "\n";
    }



    // ********** while loop **********
    // while (condition)
    // {
    //     C++ code
    // }

    // Example of while loop:
    int i = 1;
    while (i < 101)
    {
        cout << i << "\n";
        i++;
    }

    // Example of infinite while loop:
    int i = 0;
    while (true)
    {
        cout << i << "\n";
        i++;
    }
    


    // ********** do-while loop **********
    // do
    // {
    //     C++ code
    // } while (condition);
    
    // Example of do-while loop:
    int i = 1;
    do
    {
        cout << i << "\n";
        i++;
    } while (i < 101);
    
    // Example of infinite do-while loop:
    int i = 0;
    do
    {
        cout << i << "\n";
        i++;
    } while (true);
    


    // Practise (Challenge)
    int table_of = 6;
    int iteretion_no = 0;
    do
    {
        cout << table_of << " X " << (iteretion_no + 1) << " = " << (table_of * (iteretion_no + 1)) << "\n";
        iteretion_no++;
    } while (iteretion_no < 10);
    
    return 0;
}