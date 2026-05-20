#include <stdio.h>
#include <string.h>

int main(){
    char first_name[31];
    char last_name[31];
    char copyed_name[31];
    printf("Enter your first name: ");
    scanf("%30s", first_name);
    printf("Enter your last name: ");
    scanf("%30s", last_name);
    printf("Your name: %s\n", first_name);
    printf("Length of your name: %d\n", strlen(first_name)); // strlen() function is used to print, store or know the length of a string.
    strcpy(copyed_name, first_name); // strcpy() function is used to copy and paste a string. eg: strcpy(string variable where you want to paste string , string variable where you want to copy from.)
    printf("Copyed name: %s\n", copyed_name);
    strcat(first_name, last_name); // strcat() function is used to join strings but not in the simple way. I mean strcat() join strings like this :  strcat(st1, st2); it means st2 joins to st1 like st1 = st1 + st2 :P
    printf("Full name: %s\n", first_name);
    strcmp("Ahnaf", "Ahnaf"); // It compairs two strings and return 0 if two strings are same or it will return positive or negative number bluh...bluh...bluh...idk anything please check CodeWithHarry's cheetsheet or something if you want to learn more.
    return 0;
}