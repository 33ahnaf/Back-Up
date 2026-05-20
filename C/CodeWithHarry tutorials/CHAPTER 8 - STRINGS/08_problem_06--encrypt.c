#include <stdio.h>
#include <string.h>

int main(){
    char secret_massage[] = "My password is robinhood32";
    for (int i = 0; i < strlen(secret_massage); i++)
    {
        secret_massage[i] = secret_massage[i] + 1;
    }
    printf("%s", secret_massage);
    return 0;
}