#include <stdio.h>

int main(){
    int n, a, b, c, answers_count = 0;
    scanf("%d", &n);
    while(n--){
        scanf("%d %d %d", &a, &b, &c);
        if(a + b + c >= 2)
            answers_count++;
    }
    printf("%d", answers_count);
    return 0;
}