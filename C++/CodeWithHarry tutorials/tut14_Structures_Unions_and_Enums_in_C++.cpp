#include <iostream>

using namespace std;

typedef struct employee
{
    int salary;
    float rating;
    int serial_no;
}employee;

typedef union employee
{
    int salary;
    float rating;
    int serial_no;
}employee;


int main(){
    // ********** structure **********
    // Just like C
    employee e1, e2, e3;
    e1.salary = 5000;
    e2.salary = 7000;
    e3.salary = 4500;

    e1.rating = 3.5;
    e2.rating = 4.6;
    e3.rating = 2.7;

    e1.serial_no = 1;
    e2.serial_no = 2;
    e3.serial_no = 3;

    cout << "e1 Salary = " << e1.salary << "\n";
    cout << "e2 Salary = " << e2.salary << "\n";
    cout << "e3 Salary = " << e3.salary << "\n";
    
    cout << "e1 Rating = " << e1.rating << "\n";
    cout << "e2 Rating = " << e2.rating << "\n";
    cout << "e3 Rating = " << e3.rating << "\n";

    cout << "e1 Serial No. = " << e1.serial_no << "\n";
    cout << "e2 Serial No. = " << e2.serial_no << "\n";
    cout << "e3 Serial No. = " << e3.serial_no << "\n";



    // ********** union **********
    // Just like C
    employee e1, e2, e3; // same as --> union employee e1, e2, e3;
    e1.salary = 5000;
    cout << "e1 Salary = " << e1.salary << "\n";
    e2.salary = 7000;
    cout << "e2 Salary = " << e2.salary << "\n";
    e3.salary = 4500;
    cout << "e3 Salary = " << e3.salary << "\n";

    e1.rating = 3.5;
    cout << "e1 Rating = " << e1.rating << "\n";
    e2.rating = 4.6;
    cout << "e2 Rating = " << e2.rating << "\n";
    e3.rating = 2.7;
    cout << "e3 Rating = " << e3.rating << "\n";

    e1.serial_no = 1;
    cout << "e1 Serial No. = " << e1.serial_no << "\n";
    e2.serial_no = 2;
    cout << "e2 Serial No. = " << e2.serial_no << "\n";
    e3.serial_no = 3;
    cout << "e3 Serial No. = " << e3.serial_no << "\n";



    // ********** enum **********
    enum color
    {
        RED, // 0
        GREEN, // 1
        BLUE // 2
    };
    color value_of_red = RED;
    color value_of_green = GREEN;
    color value_of_blue = BLUE;

    cout << value_of_red << "\n";
    cout << value_of_green << "\n";
    cout << value_of_blue << "\n\n";

    cout << RED << "\n";
    cout << GREEN << "\n";
    cout << BLUE << "\n";
    return 0;
}