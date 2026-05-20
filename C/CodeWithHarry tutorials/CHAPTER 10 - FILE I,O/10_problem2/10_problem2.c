#include <stdio.h>

int main(){
    FILE *ptr;
    ptr = fopen("10_problem2.txt", "w");
    int table = 7;
    for (int i = 0; i < 10; i++)
    {
        int multi = table*(i+1);
        fprintf(ptr, "%d X %d = %d\n", table, i+1, multi);
    }
    fclose(ptr);
    return 0;
}