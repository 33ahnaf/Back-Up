//  Copyright: ©Ahnaf Shariar 2025
//
//  Code originally written on 27 March, 2025 @ 5:04 PM (UTC +6:00)
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

void show_time_in_YMDHMS_format(int epoch_time) {
    int year = (int) (epoch_time/31536000);
    int remaining_second = epoch_time%31536000;

    int month = (int) (remaining_second/2592000);
    remaining_second %= 2592000;

    int day = (int) (remaining_second/86400);
    remaining_second %= 86400;

    int hour = (int) (remaining_second/3600);
    remaining_second %= 3600;

    int minute = (int) (remaining_second/60);
    remaining_second %= 60;

    int second = (int) (remaining_second);

    printf("%d years - %d months - %d days - %d hours - %d minutes - %d seconds\n", year, month, day, hour, minute, second);
}

void count_time(int epoch_time) {
    while (true) {
        show_time_in_YMDHMS_format(time(NULL) - epoch_time);
        delay(10);
    }
}

int main(){
    count_time(epoch_time_when_Meghna_was_born);
    return 0;
}

// That's it! Time taken to code :  12 minutes.