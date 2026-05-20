#include <stdio.h>
#include <string.h>

int main(){
    FILE *text_file;
    text_file = fopen("encrypt_and_decrypt.txt", "a");
    char user_input_text[101];
    int how_many_times_to_encrypt_or_decrypt;
    int encrypt_or_decrypt;
    printf("Welcome to encryption-decryption code\n");
    printf("-------------------------------------\n");
    printf("0 --> Encryption\n");
    printf("1 --> Decryption\n");
    printf("Enter 0 or 1: ");
    scanf("%d", &encrypt_or_decrypt);
    if (encrypt_or_decrypt == 0)
    {
        printf("How many times to encrypt: ");
        scanf("%d", &how_many_times_to_encrypt_or_decrypt);
        for (int i = 0; i < how_many_times_to_encrypt_or_decrypt; i++)
        {
            printf("Enter a text: ");
            scanf("%100s", user_input_text);
            for (int j = 0; j < strlen(user_input_text); j++)
            {
                if (user_input_text[j] == '_')
                {
                    user_input_text[j] == '_';
                }else
                {
                    user_input_text[j] = user_input_text[j] + 1;
                }
            }
            fprintf(text_file, "%s", user_input_text);
            fprintf(text_file, "%s", "\n");
        }
    }else if (encrypt_or_decrypt == 1)
    {
        printf("How many times to decrypt: ");
        scanf("%d", &how_many_times_to_encrypt_or_decrypt);
        for (int i = 0; i < how_many_times_to_encrypt_or_decrypt; i++)
        {
            printf("Enter a text: ");
            scanf("%100s", user_input_text);
            for (int j = 0; j < strlen(user_input_text); j++)
            {
                if (user_input_text[j] == '_')
                {
                    user_input_text[j] == '_';
                }else
                {
                    user_input_text[j] = user_input_text[j] - 1;
                }
            }
            printf("%s\n", user_input_text);
        }
    }else
    {
        printf("Invalid selection!");
    }
    fclose(text_file);
    return 0;
}