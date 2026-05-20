#include <stdio.h>

int main(){
    FILE *ptr;
    ptr = fopen("reading_file_char_by_char.txt", "r");
    char c;
    while (1)
    {
        c = fgetc(ptr);
        if (c == EOF)
        {
            break;
        }
        printf("%c", c);
    }
    
    return 0;
}