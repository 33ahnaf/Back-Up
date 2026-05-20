#include <stdio.h>
typedef struct employee{
    int salary;
    float score;
}employee;
int main(){
    employee e1;
    employee* ptr = &e1;
    // (*ptr).salary = 2000;
    // (*ptr).score = 3.5;
    ptr->salary = 2000; // Same as (*ptr).salary = 2000;
    ptr->score = 3.5; // Same as (*ptr).score = 3.5;
    printf("Employee 1: Salary = %d, Score = %.1f star", ptr->salary, ptr->score);
    return 0;
}