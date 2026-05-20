#include <stdio.h>
#include <string.h>
struct employee
{
    int id_no;
    float salary;
    char name[26];
};

int main(){
    // struct employee e1, e2, e3;                                                                      Won't work :(    
    // for (int i = 0; i < 3; i++)                                                                      Won't work :(
    // {                                                                                                Won't work :(
    //     printf("Employee %d (ID No.): ", i+1);                                                       Won't work :(
    //     scanf("%d", &e1.id_no);                                                                      Won't work :(
    //     printf("Employee %d (Salary): ", i+1);                                                       Won't work :(
    //     scanf("%f", &e1.salary);                                                                     Won't work :(
    //     printf("Employee %d (Name): ", i+1);                                                         Won't work :(
    //     scanf("%25s", &e1.name);                                                                     Won't work :(
    // }                                                                                                Won't work :(
    // for (int j = 0; j < 3; j++)                                                                      Won't work :(
    // {                                                                                                Won't work :(
    //     printf("Employee %d: ID No. : %d, Salary: %f, Name: %s", j+1, e1.id_no, e1.salary, e1.name); Won't work :(
    // }                                                                                                Won't work :(
    
    struct employee e[3];
    for (int i = 0; i < 3; i++)
    {
        printf("Employee %d (Name): ", i+1);
        scanf("%25s", e[i].name);
        printf("Employee %d (ID No.): ", i+1);
        scanf("%d", &e[i].id_no);
        printf("Employee %d (Salary): ", i+1);
        scanf("%f", &e[i].salary);
    }
    for (int j = 0; j < 3; j++)
    {
        printf("Employee %d: ID No. : %d, Salary: %f, Name: %s", j+1, e[j].id_no, e[j].salary, e[j].name);
        printf("\n");
    }                     
    
    return 0;
}