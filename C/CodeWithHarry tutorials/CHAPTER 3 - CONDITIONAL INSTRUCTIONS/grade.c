#include <stdio.h>

int main()
{
    char grade;
    int marks;
    printf("Enter mark:\n");
    scanf("%d", &marks);
    if (marks >= 90)
    {
        grade = 'A';
    }

    else if (marks >= 80)
    {
        grade = 'B';
    }

    else if (marks >= 70)
    {
        grade = 'C';
    }

    else if (marks >= 60)
    {
        grade = 'D';
    }

    else if (marks >= 50)
    {
        grade = 'E';
    }

    else
    {
        grade = 'F';
    }
    printf("Your mark is %d and your grade is %c", marks, grade);
    return 0;
}