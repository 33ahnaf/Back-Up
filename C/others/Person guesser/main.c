#include <stdio.h>

void ask_user(const char *question, char *char_ptr){
    printf("%s [Y/n]\n>", question);
    scanf(" %c", char_ptr);
}

int main(){
    char user_input;
    ask_user("Is your character a male?", &user_input);

    if(user_input == 'y' || user_input == 'Y'){
        ask_user("Is your character a teacher?", &user_input);
        if(user_input == 'y' || user_input == 'Y'){
            ask_user("Is your character a principle?", &user_input);
            if(user_input == 'y' || user_input == 'Y'){
                ;
            }else if (user_input == 'n' || user_input == 'N'){
                ;
            }else{
                printf("Invalid option!\n");
                return 1;
            }
        }else if (user_input == 'n' || user_input == 'N'){
            printf("Md. Ahnaf Shariar\n");
        }else{
            printf("Invalid option!\n");
            return 1;
        }
    }else if (user_input == 'n' || user_input == 'N'){
        ask_user("Is your character a teacher?", &user_input);
        if(user_input == 'y' || user_input == 'Y'){
            printf("Miss. Nahida Sultana\n");
        }else if (user_input == 'n' || user_input == 'N'){
            printf("Mst. Afrina Rahman Meghna\n");
        }else{
            printf("Invalid option!\n");
            return 1;
        }
    }else{
        printf("Invalid option!\n");
        return 1;
    }
    return 0;
}


// if(user_input == 'y' || user_input == 'Y'){
//     ;
// }else if (user_input == 'n' || user_input == 'N'){
//     ;
// }else{
//     printf("Invalid option!\n");
//     return 1;
// }