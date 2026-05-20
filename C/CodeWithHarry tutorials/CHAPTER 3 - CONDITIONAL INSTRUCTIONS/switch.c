#include <stdio.h>

int main(){
    int x;
    printf("Type 1 for Kilometer, 2 for Meter, 3 for Mile\n");
    printf("Enter:\n");
    scanf("%d", &x);
    switch(x){
        case 1:
            printf("Kilometer");
            break;
        case 2:
            printf("Meter");
            break;
        case 3:
            printf("Mile");
            break;
        default:
            printf("Invalid option");
            break;
    }
    return 0;
}