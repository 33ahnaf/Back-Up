#include <stdio.h>
#include <string.h>
struct student
{
    char first_name[11];
    char last_name[11];
    int roll;
    char quality[11];
};

int main(){
    struct student student[7];
    strcpy(student[0].first_name, "Afrina");
    strcpy(student[0].last_name, "Rahman");
    student[0].roll = 1;
    strcpy(student[0].quality, "Very good");

    strcpy(student[1].first_name, "Rupto");
    strcpy(student[1].last_name, "Sarkar");
    student[1].roll = 2;
    strcpy(student[1].quality, "Very good");

    strcpy(student[2].first_name, "Farah");
    strcpy(student[2].last_name, "Ulfath");
    student[2].roll = 3;
    strcpy(student[2].quality, "Very good");

    // struct student student[3] = {"Ahnaf", "Shariar", 4, "Very good"};// This is also a way and lot compact/simple.(This is not how its works)

    strcpy(student[3].first_name, "Ahnaf");
    strcpy(student[3].last_name, "Shariar");
    student[3].roll = 4;
    strcpy(student[3].quality, "Very good");

    strcpy(student[4].first_name, "Anas");
    strcpy(student[4].last_name, "Mahamud");
    student[4].roll = 7;
    strcpy(student[4].quality, "Very good");

    strcpy(student[5].first_name, "Bushra");
    strcpy(student[5].last_name, "Binte Zakaria");
    student[5].roll = 10;
    strcpy(student[5].quality, "Very good");
 
    strcpy(student[6].first_name, "Bashirul");
    strcpy(student[6].last_name, "Islam");
    student[6].roll = 11;
    strcpy(student[6].quality, "Very good");

    // struct student student[7] = {"0"}; // All values are assigned to 0.(But this is not capeable because all values are not integer nor char)

    for (int i = 0; i < 7; i++)
    {
        printf("Student %d: First name: %s, Last name: %s, Roll: %d, Quality: %s", i+1, student[i].first_name, student[i].last_name, student[i].roll, student[i].quality);
        printf("\n");
    }
    
    return 0;
}