#include <stdio.h>

int main(){
    int race_count, age, ages[100], eligible_races;
    race_count = age = eligible_races = 0;
    scanf("%d", &race_count);
    for(int i = 0; i < race_count; i++){
        scanf("%d", &ages[i]);
    }
    scanf("%d", &age);
    for(int i = 0; i < race_count; i++){
        if(ages[i] >= age) eligible_races++;
    }
    printf("%d", eligible_races);
    return 0;
}