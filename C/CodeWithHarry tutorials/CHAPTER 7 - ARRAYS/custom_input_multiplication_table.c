#include <stdio.h>

int main(){
    int n1, n2, n3;
    printf("Enter three number:\n");
    scanf("%d %d %d", &n1, &n2, &n3);
    int arr[3][10];
    int multi[3] = {n1, n2, n3};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            arr[i][j] = multi[i] * (j+1);
        }
        
    }
    
    for (int l = 0; l < 3; l++)
    {
        for (int t = 0; t < 10; t++)
        {
            printf("%d X %d = %d\n", multi[l], (t+1),arr[l][t]);
        }
        printf("\n");
    }
    return 0;
}