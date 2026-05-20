#include <stdio.h>

int main(){
    char name[11];
    // scanf("%10s", name);
    for (int i = 0; i < 10; i++)
    {
        scanf("%c", &name[i]);
        fflush(stdin); // this command should discard \n (newlines) but it's not working properly. :(
    }
    name[10] = '\0';

    printf("%s", name);
    return 0;
}