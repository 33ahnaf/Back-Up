#include <stdio.h>

int main(){
    FILE *ptr;
    ptr = fopen("ahnaf.txt", "r");
    int num;
    fscanf(ptr, "%d", &num);
    printf("The number is: %d\n", num);
    fscanf(ptr, "%d", &num);
    printf("The number is: %d", num);
    fclose(ptr); // This is a good practise to close the file.
    return 0;
}