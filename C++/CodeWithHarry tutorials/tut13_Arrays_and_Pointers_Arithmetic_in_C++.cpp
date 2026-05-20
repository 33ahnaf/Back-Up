#include <iostream>

using namespace std;

int main(){
    // ********** Array **********
    int student_s__math_marks[] = {77, 89, 65, 83};
    cout << "Student 1 = " << student_s__math_marks[0] << "\n";
    cout << "Student 2 = " << student_s__math_marks[1] << "\n";
    cout << "Student 3 = " << student_s__math_marks[2] << "\n";
    cout << "Student 4 = " << student_s__math_marks[3] << "\n";

    // ***** using for loop *****
    for (int i = 0; i < 4; i++)
    {
        cout << "Student " << i+1 << " = " << student_s__math_marks[i] << "\n";
    }

    // Quick Quiz: do the same thing using while and do-while loop
    // ***** using while loop *****
    int iteretion_no = 0;
    while (iteretion_no < 4)
    {
        cout << "Student " << iteretion_no+1 << " = " << student_s__math_marks[iteretion_no] << "\n";
        iteretion_no++;
    }
    
    // ***** using do-while loop *****
    int iteretion_no = 0;
    do
    {
        cout << "Student " << iteretion_no+1 << " = " << student_s__math_marks[iteretion_no] << "\n";
        iteretion_no++;
    }while (iteretion_no < 4);



    // ********** Pointer Arithmetic **********
    // int *ptr = &student_s__math_marks[0];
    int *ptr = student_s__math_marks; // same as &student_s__math_marks[0]; (you don't have write &arr[0] , you can just write arr)
    cout << "Address of arr[0]: " << ptr << "\n";
    cout << "Value at address of arr[0]: " << *(ptr++) << "\n";
    cout << "\n";
    // ptr++; // Don't need to do this.
    cout << "Address of arr[1]: " << ptr << "\n";
    cout << "Value at address of arr[1]: " << *(ptr++) << "\n";
    cout << "\n";
    // ptr++; // Don't need to do this.
    cout << "Address of arr[2]: " << ptr << "\n";
    cout << "Value at address of arr[2]: " << *(ptr++) << "\n";
    cout << "\n";
    // ptr++; // Don't need to do this.
    cout << "Address of arr[3]: " << ptr << "\n";
    cout << "Value at address of arr[3]: " << *ptr << "\n";
    return 0;
}