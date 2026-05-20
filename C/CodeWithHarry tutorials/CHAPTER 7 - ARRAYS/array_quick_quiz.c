#include <stdio.h>

int main(){
    int arr[3][2];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("Enter a number:\n");
            scanf("%d", &arr[i][j]);
        }
        
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("arr[%d][%d] = %d\n", i, j, arr[i][j]);
        }
        
    }
    return 0;
}