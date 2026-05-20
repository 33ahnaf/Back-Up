#include <stdio.h>
#include <time.h>

int main(){
    for (int i = 0; i < 2000000000; i++)
    {
        
    }
    
    printf("%.3lf", (double) clock() / CLOCKS_PER_SEC);
    return 0;
}