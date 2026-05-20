#include <stdio.h>

int main(){
    int i, x;
    printf("Plese enter a value:\n");
    scanf("%d", &x);
    for(i=x;i>=0;i--){  // If you want to show value like, x to 1 then erase the = sign else do not.
        printf("The value of i is %d\n", i);
    }
    return 0;
}