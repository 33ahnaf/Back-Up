#include <stdio.h>

int main() 
{

    int n;
    printf(">");
    scanf("%d", &n);
    int size = (n * 2 - 1);
  	for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((i == 0 || i == size - 1)  ||  (j == 0 || j == size - 1)) {
                printf("%d ", n);
            }else{
                if (n - i > 0) {
                    printf("%d ", n - i);
                }else{
                    printf("%d ", (i+2) - n);
                }
            }
        }
        printf("\n");
    }
    return 0;
}


/*
0 1 2 3 4 5 6 7 8

5 5 5 5 5 5 5 5 5   0
5 4 4 4 4 4 4 4 5   1
5 4 3 3 3 3 3 4 5   2
5 4 3 2 2 2 3 4 5   3
5 4 3 2 1 2 3 4 5   4
5 4 3 2 2 2 3 4 5   5
5 4 3 3 3 3 3 4 5   6
5 4 4 4 4 4 4 4 5   7
5 5 5 5 5 5 5 5 5   8

*/

/*
 n - i
 5 - 0 = 5
 5 - 1 = 4
 5 - 2 = 3
 5 - 3 = 2
 5 - 4 = 1
 
 i - n
 6 - 5 = 1
 7 - 5 = 2

 i - n
 7 - 5 = 2
 8 - 5 = 3
*/