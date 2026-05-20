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
void StringCopy(char target[], char sourse[]){
    for (int i = 0; i < len(sourse); i++)
    {
        target[i] = sourse[i];
    }
    target[len(sourse)] = '\0';
}
int main(){
    char ahnafs_paper[31] = "2 X 4 + 5 = 25";
    char shazids_paper[31];
    StringCopy(shazids_paper, ahnafs_paper);
    printf("Ahnaf's paper: %s\nShazid's paper: %s", ahnafs_paper, shazids_paper);
    return 0;
}