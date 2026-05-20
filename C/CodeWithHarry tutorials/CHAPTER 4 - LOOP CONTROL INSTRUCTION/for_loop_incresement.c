#include <stdio.h>

int main(){
    int i, x;
    printf("Plese enter a value:\n");
    scanf("%d", &x);
    for(i=0;i<=x;i++){  // If you want to show value like, 1 to x then set the value of i to 1 else do not.
        printf("The value of i is %d\n", i);
    }
    return 0;
}