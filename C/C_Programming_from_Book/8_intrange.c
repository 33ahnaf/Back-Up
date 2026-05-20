#include <stdio.h>
#include <stdlib.h>

void main(){
    short int pstv_range = 32767; /* store 32767 to pstv_range variable */
    short int ngtv_range = -32768; /* store 32768 to ngtv_range variable */

    system("clear");

    printf("\n %hd + 1 is %hd.\n", pstv_range, pstv_range + 1);
    printf("\n %hd - 1 is %hd.\n", ngtv_range, ngtv_range - 1);

    getchar();
}
