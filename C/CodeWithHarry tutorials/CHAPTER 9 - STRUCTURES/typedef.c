#include <stdio.h>
#include <string.h>
typedef struct employee
{
    int code;
    float salary;
    char name[10];
}emp; // Shortcut for the structure.
int main(){

    // typedef int ahnaf;
    // ahnaf x = 14;                            we can use typedef to create our own data type.
    // printf("The value of x is: %d", x);
    
    // typedef struct employee emp; // We can also do this way. (Then we can't do the upper emp shortcut thing. I mean only one way)

    emp e1;
    e1.salary = 54.34;
    e1.code = 2947;
    strcpy(e1.name, "Ahnaf");
    printf("Name: %s, Salary: %f, Code: %d", e1.name, e1.salary, e1.code);
    return 0;
}