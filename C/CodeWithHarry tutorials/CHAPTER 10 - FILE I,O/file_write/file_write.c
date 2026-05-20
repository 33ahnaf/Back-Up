#include <stdio.h>

int main(){
    FILE *ptr;
    ptr = fopen("ahnaf_write.txt", "a");
    int num = 1024;
    fprintf(ptr, "%d", num);
    fclose(ptr);
    return 0;
}