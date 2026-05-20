#include <stdio.h>
#include <string.h>
struct employee
{
    int code;
    float salary;
    char name[10];
};
void show(struct employee e);
void show(struct employee e){
    printf("Name: %s, Salary: %f, Code: %d", e.name, e.salary, e.code);
}
int main(){
    struct employee e1;
    e1.code = 2947;
    e1.salary = 54.34;
    strcpy(e1.name, "Ahnaf");
    show(e1);
    return 0;
}