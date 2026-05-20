#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

void main(){
    float area, radius, PI;
    char ch;
    PI = 3.14159;

    system("clear");

    printf("\n Do you want to calculate area? (Y/n): ");
    ch = getchar();
    ch = toupper(ch);

    while( ch != 'N' ){
        system("clear");
        printf("\n What's your radius?: ");
        scanf("%f", &radius);
        area = PI * radius * radius;
        printf("\n\n Area of a circle is: %.2f.", area);
        usleep(3000 * 1000);
        printf("\n\n\n Do you want to calculate area? (Y/n): ");
        ch = getchar();
        ch = toupper(ch);
    }
}
