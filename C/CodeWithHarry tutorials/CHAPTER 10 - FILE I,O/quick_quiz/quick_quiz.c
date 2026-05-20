#include <stdio.h>

int main(){
    FILE *ptr;
    ptr = fopen("ahnaf2.txt", "r");
    if (ptr == NULL)
    {
        printf("Sorry, the file does not exist!\n"); // If the file doesn't exist, mean if the pointer value become NULL then it will prints the massage.
    }else{
        int num;
        fscanf(ptr, "%d", &num);
        printf("The number is: %d\n", num);
    }
    return 0;
}