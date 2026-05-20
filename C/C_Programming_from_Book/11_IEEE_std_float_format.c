#include <stdio.h>
#include <stdlib.h>

void main(){
    float a = 10.375;
    char *p;
    int i;

    p = ( char * ) &a;
    
    system("clear");
    printf("\n ");

    for( i = 0; i <= 3; i++ ) printf( "%02x ", ( unsigned char ) p[i] );

    printf("\n");
}
