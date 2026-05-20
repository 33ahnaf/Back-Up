//  Copyright: ©Ahnaf Shariar 2025
//
//  Code originally written on 27 March, 2025 @ 5:18 PM (UTC +6:00)
//  by Md. Ahnaf Shariar
//
//  This example code is in the public domain.

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define epoch_time_when_Meghna_was_born 1329393600

void delay(int delay_time) {
    clock_t time_then = clock();
    while ((clock() - time_then) < delay_time){
    }
}

void show_days_since_somewhen(int epoch_time){
    float days = epoch_time/86400.0;
    printf("%f Days since the given epoch time\n", days);
}

void count_time(int epoch_time){
    while(true){
        show_days_since_somewhen(time(NULL) - epoch_time);
        delay(10);
    }
}

int main(){
    count_time(epoch_time_when_Meghna_was_born);
    return 0;
}

// That's it! Time taken to code :  12 minutes.