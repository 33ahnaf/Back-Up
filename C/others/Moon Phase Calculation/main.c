//  Copyright: ©Ahnaf Shariar 2025
//
//  Code originally written on 28 March, 2025 @ 3:20 PM (UTC +6:00)
//  by Md. Ahnaf Shariar
//
//  This example code is in the public domain.

#include <stdio.h>

#define delta_of_illumination_percentage 6.779661017

int main(){
    // Time and Phase of Moon are calculated based on 29th of March, 2025 in Rangpur, Bangladesh.
    int current_total_days_since_birth_of_Meghna = 4790; // this is set to 2 days ahead of what it should be because after 2 days there will be a new moon / 0 % moon.
    double current_illumination_percentage = 0.0;

    while(current_total_days_since_birth_of_Meghna > 0){

        if(current_illumination_percentage == 0){
            current_illumination_percentage -= delta_of_illumination_percentage;
        }else if(current_illumination_percentage < 0){
            if(current_illumination_percentage > -100){
                current_illumination_percentage -= delta_of_illumination_percentage;
            }else if(current_illumination_percentage < -100){
                current_illumination_percentage *= -1;
                current_illumination_percentage = 100 - (current_illumination_percentage - 100);
                current_illumination_percentage -= delta_of_illumination_percentage;
            }else if(current_illumination_percentage == -100){
                current_illumination_percentage *= -1;
                current_illumination_percentage -= delta_of_illumination_percentage;
            }
        }else if(current_illumination_percentage > 0){
            if(current_illumination_percentage < 100){
                current_illumination_percentage -= delta_of_illumination_percentage;
            }else if(current_illumination_percentage == 100){
                current_illumination_percentage -= delta_of_illumination_percentage;
            }
        }

        current_total_days_since_birth_of_Meghna--;
    }

    if(current_illumination_percentage < -100){
        current_illumination_percentage *= -1;
        current_illumination_percentage = 100 - (current_illumination_percentage - 100);
    }

    printf("%lf", current_illumination_percentage);
    return 0;
} // Time taken :  2 hours



// abandoned code
// --------------
// int current_total_days_since_birth_of_Meghna = 4790; // this is set to 2 days ahead of what it should be because after 2 days there will be a new moon / 0 % moon.
// double previous_illumination_percentage = -6.779661017;
// double current_illumination_percentage = 0.0;
// while(current_total_days_since_birth_of_Meghna > 0){
//     if(current_illumination_percentage > 0 && current_illumination_percentage < 100){
//         previous_illumination_percentage = current_illumination_percentage;
//         current_illumination_percentage += delta_of_illumination_percentage;
//     }else if(current_illumination_percentage >= 100){
//         current_illumination_percentage = 100 - current_illumination_percentage;
//         previous_illumination_percentage = current_illumination_percentage;
//         current_illumination_percentage = current_illumination_percentage - delta_of_illumination_percentage;
//     }else if(current_illumination_percentage <= -100){
//         current_illumination_percentage = (current_illumination_percentage * -1) - 100;
//         previous_illumination_percentage = current_illumination_percentage;
//         current_illumination_percentage += delta_of_illumination_percentage;
//     }else if(current_illumination_percentage < 0 && current_illumination_percentage > -100){
//         previous_illumination_percentage = current_illumination_percentage;
//         current_illumination_percentage -= delta_of_illumination_percentage;
//     }
//     current_total_days_since_birth_of_Meghna--;
// }
// printf("%lf", current_illumination_percentage);