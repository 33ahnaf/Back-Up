#include <stdio.h>

int main(){
    const float PI = 3.1415;
    int width, length, radius, rect_area;
    float circle_area;

    width = 113;
    length = 19;
    radius = 7;

    rect_area = width * length;
    circle_area = PI * radius * radius;

    printf("Length: %d\tWidth: %d\tArea: %d\n", length, width, rect_area);
    printf("Radius: %d\tArea: %.3f\n", radius, circle_area);
    return 0;
}