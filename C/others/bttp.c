#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *file = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    int batteryPercentage;
    char command[20];
    fscanf(file, "%d", &batteryPercentage);
    sprintf(command, "figlet -c %d", batteryPercentage);
    system(command);
    return 0;
}
