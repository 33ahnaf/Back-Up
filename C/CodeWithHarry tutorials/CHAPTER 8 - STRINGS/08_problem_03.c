#include <stdio.h>
int len(char str[]){
    int i = 0, len;
    char check_len;
    check_len = str[0];
    while (check_len != '\0')
    {
        i++;
        check_len = str[i];
    }
    len = i;
    return len;
}
int main(){
    char name[] = "Ahnaf Shariar Ahon";
    printf("%d", len(name));
    return 0;
}