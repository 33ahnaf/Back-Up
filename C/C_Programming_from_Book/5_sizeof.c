#include <stdio.h>
#include <stdlib.h>

void main(){
    system("clear");

    printf("\n\t Integer    type data takes %d byte(s)", sizeof(int));
    printf("\n\t Character  type data takes %d byte(s)", sizeof(char));
    printf("\n\t Floating   type data takes %d byte(s)", sizeof(float));
    printf("\n\t Double     type data takes %d byte(s)", sizeof(double));

    getchar();
}
