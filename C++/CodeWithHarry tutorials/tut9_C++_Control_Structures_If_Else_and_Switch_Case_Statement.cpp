#include <iostream>

using namespace std;

int main()
{
    //********** Selection Control Structure **********

    //********** if - else if - else ladder **********
    int age;
    cout<<"Enter your age: ";
    cin>>age;
    if (age<1)
    {
        cout<<"You are not born yet!\n";
    }
    else if (age < 18)
    {
        cout<<"You cant't come to my party!\n";
    }
    else if (age == 18)
    {
        cout<<"You can come to my party but you will get a kid pass!\n";
    }
    else
    {
        cout<<"You can come and enjoy my party!\n";
    }

    //********** Switch-Case Statement **********
    int user_input;
    cout << "Enter 0 for Kilometre or 1 for Mile or 2 for Nautical Mile: ";
    cin >> user_input;
    cout << "\n";
    switch (user_input)
    {
    case 0:
        cout << "Kilometre\n";
        break;
    case 1:
        cout << "Mile\n";
        break;
    case 2:
        cout << "Nautical Mile\n";
        break;
    default:
        cout << "Invalid option!\n";
        break;
    }

    return 0;
}