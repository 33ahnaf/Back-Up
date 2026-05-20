#include <stdio.h>

int main(){
    FILE *ptr;
    ptr = fopen("fgetc_fputc.txt", "r/w/a"); // remember r means read, w means write, a means append.

    // char c = fgetc(ptr); // reads and stores the first charecter of fgetc_fputc.txt in c variable.
    // printf("%c", c);

    // fputc('A', ptr); // writes charecter 'A' in the file fgetc_fputc.txt;
    return 0;
}