#include <stdio.h>
typedef struct date
{
    int dd;
    int mm;
    int yyyy;
}date;
int compare(date d1, date d2){
    if (d1.yyyy > d2.yyyy) // If d1.year is greater than d2.year then return 1.
    {
        return 1;
    }else if (d1.yyyy < d2.yyyy) // If d1.year is less than d2.year then return -1.
    {
        return -1;
    }else if (d1.yyyy == d2.yyyy) // If d1.year is equal to d2.year then go to next step.
    {
        if (d1.mm > d2.mm) // If d1.month is greater than d2.month then return 1.
        {
            return 1;
        }else if (d1.mm < d2.mm) // If d1.month is less than d2.month then return -1.
        {
            return -1;
        }else if (d1.mm == d2.mm) // If d1.month is equal to d2.month then go to next step.
        {
            if (d1.dd > d2.dd) // If d1.day is greater than d2.day then return 1.
            {
                return 1;
            }else if (d1.dd < d2.dd) // If d1.day is less than d2.day then return -1.
            {
                return -1;
            }else if (d1.dd == d2.dd) // If finally d1.day is also equal to d2.day then return 0.
            {
                return 0;
            }   
        }
    }
}
int main(){
    date d1 = {6, 6, 2010};
    date d2 = {14, 10, 2024};
    int compare_date = compare(d1, d2);
    if (compare_date == 0)
    {
        printf("Both dates are same.");
    }else if (compare_date == 1)
    {
        printf("d1 is greater than d2.");
    }else if (compare_date == -1)
    {
        printf("d1 is less than d2.");
    }
    return 0;
}