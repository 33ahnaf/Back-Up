#include <stdio.h>
#include <stdlib.h>

void main(){
    int a, b, c; /* declare three int type variable */
    system("clear"); /* clear the screen */

    printf("\nEnter first value: "); /* prompt user for first value */
    scanf("%d", &a); /* store the first value in a */

    printf("\nEnter second value: "); /* prompt user for second value */
    scanf("%d", &b); /* store the second value in b */

    c = a * b; /* store a * b in c */

    printf("\n%d * %d is %d.\n", a, b, c); /* printf a,b and c's value */

    getchar(); /* wait for key press */
}
