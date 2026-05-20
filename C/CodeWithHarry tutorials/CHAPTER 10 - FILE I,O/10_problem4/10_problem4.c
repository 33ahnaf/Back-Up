#include <stdio.h>
typedef struct employee
{
    char name[26];
    int salary;
}employee;

int main(){
    employee employee[2];
    for (int i = 0; i < 2; i++)
    {
        printf("Employee %d: \n", i+1);
        printf("Name: ");
        scanf("%25s", employee[i].name);
        printf("Salary: ");
        scanf("%d", &employee[i].salary);
    }
    FILE *ptr;
    ptr = fopen("10_problem4.txt", "w");
    fprintf(ptr, "----------Employee list----------\n");
    for (int i = 0; i < 2; i++)
    {
        fprintf(ptr, "%d. Name: %s, Salary: %d\n", i+1, employee[i].name, employee[i].salary);
    }
    fclose(ptr);
    return 0;
}