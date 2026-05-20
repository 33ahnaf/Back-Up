#include <stdio.h>
#include <time.h>

int main(){
    clock_t init, end;
    double used_time = 0;

    for(unsigned short i = 0; i < 10; i++){
        init = clock();
        for(unsigned i = 0; i < 3000000000; i++);
        end = clock();
        printf("#%d run: %lf\n", i+1, ((double) (end - init)) / CLOCKS_PER_SEC);
        used_time += ((double) (end - init)) / CLOCKS_PER_SEC;
    }
    used_time /= 10;
    printf("\nExecution time (~average): %lf\n", used_time);
    return 0;
}
// Average execution time on 10 runs -> 6.598900 seconds.