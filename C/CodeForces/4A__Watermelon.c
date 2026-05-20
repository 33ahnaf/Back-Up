#include <stdio.h>

int main(){
    int w;
    scanf("%d", &w);
    if(w < 4){ printf("NO"); return 0; }
    w % 2 == 0 ? printf("YES") : printf("NO");
    return 0;
}