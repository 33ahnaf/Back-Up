#include <stdio.h>

int main(){
    long long n, m, a;
    scanf("%lld %lld %lld", &n, &m, &a);
    long long along_width = (n + a - 1) / a;
    long long along_breadth = (m + a - 1) / a;
    printf("%lld\n", along_breadth * along_width);
    return 0;
}