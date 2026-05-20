#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define false 0
#define true 1

int main(){

    // DIGITAL CLOCK

    time_t rawTime = 0; // January 1st 1970 (Epoch)
    struct tm *pTime = NULL;
    int isRunning = true;
    printf("DIGITAl CLOCK\n");
    while(isRunning){
        printf("test\n");
    }
    return 0;
}