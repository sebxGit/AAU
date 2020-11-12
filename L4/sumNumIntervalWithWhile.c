#include <stdio.h>

int main()
{
    int n, i, j, val1 = 0, val2 = 0, sum;

    do
    {
        printf("Add all numbers, 0 excluded, between the int n and 2 * n. Type an int: \n");
        scanf("%d", &n);
    } while (n == 0);

    if (n > 0)
    {
        i = n;
        while (i <= n * 2)
        {
            val1 += i;
            i++;
        }
    }
    else
    {
        j = 2 * n;
        while (j <= n)
        {
            val2 += j;
            j++;
        }
    }
    printf("The value of all the numbers between n and 2n is: %d\n", val1 + val2);
}