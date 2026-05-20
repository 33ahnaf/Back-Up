#include <stdio.h>
#include <string.h>

int main(){
    int n, x = 0;
    char input[4];
    scanf("%d", &n);
    while(n--){
        scanf("%s", input);
        if(!strcasecmp(input, "X++") || !strcasecmp(input, "++X"))
            x++;
        else if(!strcasecmp(input, "X--") || !strcasecmp(input, "--X"))
            x--;
    }
    printf("%d", x);
    return 0;
}