#include <stdio.h>

int main(){
    int array[3][10];
    int multi[3] = {2, 7, 9};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            array[i][j] = multi[i] * (j+1);
        }
        
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%d X %d = %d\n", multi[i], (j+1), array[i][j]);
        }
        printf("\n");
    }
    
    
    return 0;
}