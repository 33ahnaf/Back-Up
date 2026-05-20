#include <stdio.h>

int main(){
    FILE *ptr1;
    FILE *ptr2;
    ptr1 = fopen("10_problem3.txt", "r");
    ptr2 = fopen("10_problem3_2.txt", "w");
    char ch;
    while (1)
    {
        ch = fgetc(ptr1);
        if (ch == EOF)
        {
            break;
        }
        fprintf(ptr2, "%c", ch);
        fprintf(ptr2, "%c", ch);
    }
    fclose(ptr1);
    fclose(ptr2);
    return 0;
}