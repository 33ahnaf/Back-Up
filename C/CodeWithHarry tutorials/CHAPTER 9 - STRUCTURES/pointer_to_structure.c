#include <stdio.h>
#include <string.h>
struct employee
{
    int code;
    float salary;
    char name[10];
};

int main(){
    struct employee e1;
    struct employee *ptr;
    ptr = &e1;
    e1.salary = 54.34;
    e1.code = 2947;
    strcpy(e1.name, "Ahnaf");

    // printf("%d\n", (*ptr).code); // prints the value of value at pointer .code

    printf("%d\n", ptr->code); // exactly same as (*ptr).code

    printf("%d", ptr); // prints the value of the pointer.
    

    // struct employee e1;
    // e1.salary = 54.34;
    // e1.code = 2947;
    // strcpy(e1.name, "Ahnaf");
    // struct employee *ptr;        <--    You can't do this!
    // ptr = e1.code;
    // printf("%d\n", *ptr);
    // printf("%d", ptr);


    return 0;
}