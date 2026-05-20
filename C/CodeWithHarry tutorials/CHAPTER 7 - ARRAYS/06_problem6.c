#include <stdio.h>

int count(int arr[], int n)
{
    int no_of_positive_intiger = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0)
        {
            no_of_positive_intiger++;
        }
    }
    return no_of_positive_intiger;
}

int main()
{
    int array[] = {2, 4, -6, 8, -10, 12, 14, -16, 18, 20};
    printf("Number of positive intiger(s): %d", count(array, 10));
    return 0;
}