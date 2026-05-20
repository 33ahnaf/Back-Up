#include <stdio.h>
#include <time.h>

int main(){
    clock_t iniatial_time = clock();
    for (int i = 0; i < 1000000000; i++)
    {
        
    }
    
    clock_t terminal_time = clock();
    double execution_time = (double)(terminal_time - iniatial_time) / CLOCKS_PER_SEC;
    printf("Time = %f", execution_time);
    return 0;
}