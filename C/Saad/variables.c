#include <stdio.h>

int main(){
    // var_type var_name = var_value;




    int a = 5;
    a = 12;
    int b = 10;
    int c = 0;
    int d = -3;
    int e = -56;

    float PI = 3.1415;

    char my_fav_char = 'S';

    double random_num = 5.123123123;

    printf("a = %d\nb = %d\nc = %d\nd = %d\ne = %d\na + b = %d\n", a, b, c, d, e, a + b);
    printf("PI = %f\n", PI);
    printf("my fav character: %c\n", my_fav_char);
    printf("Ahnaf = %lf awdad\n", random_num);


    printf("%.2f\n", PI);

    printf("%-6d num\n", 123456);
    printf("%-6d num\n", 1234);
    printf("%6d num\n", 123456);
    printf("%6d num\n", 1234);


    const int abc = 5;
    // abc = 5;     Invalid!
    printf("%d\n", abc);



















    /* 
        %d  -> integer  -> 1, 2, 3, -10, -1, 0
        %f  -> float    -> 0.1231, 3.1415, 0.5, -23.55, 0.0
        %lf -> double   -> 0.123456234234232423423
        %c  -> char     -> 'A', 'B', '1', 'a', ';', '!'
    */

    return 0;
}