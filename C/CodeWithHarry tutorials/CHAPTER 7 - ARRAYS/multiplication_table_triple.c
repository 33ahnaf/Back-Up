#include <stdio.h>

int main(){
    int arr[3][10];
    int multi[] = {2, 7, 9};
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
            printf("The value of %d X %d is %d\n", multi[l], (t+1),arr[l][t]);
        }
        printf("\n");
    }
    return 0;
}