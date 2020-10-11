#include <stdio.h>

int main()
{
    int a, b, var, divisor = 0;
    int done = 0;

    // Tjekker at to ikke-negative tal bliver indtastet

    while (!(done))
    {
        printf("\nChoose two non-negative integers and get the highest divisor. \n");
        scanf("%d %d", &a, &b);
        if (a > 0 && b > 0)
        {
            done = 1;
            break; // Ikke helt nødvendigt men for at demonstrere at den kommer ud af while-løkken
        }
        if (a == 0 || b == 0)
        {
            printf("\n(0 is indivisible. Please choose positive integers.)\n\n");
        }
        if (a < 0 || b < 0)
        {
            printf("\n(You chose negative numbers. Please choose positive integers.)\n\n");
        }
    }

    // Bytter om på a og b, hvis b er større end a

    if (a != b)
    {
        if (b < a) // Hvis b er større end a
        {
            var = b; // Byttes der om på variablerne a og b's størrelse
            b = a;
            a = var;
        }
    }

    // Laver udregningen vha. modulus og beregner den største divisor

    for (int n = b; n > 0; n--)
    {
        if (a % n == 0 && b % n == 0) // Tjekker om begge variabler går op i det aktuelle tal n
        {

            // Opdaterer divisor (den største divisor) variabel

            if (divisor == 0)
            {
                divisor = n;
            }
            else
            {
                if (n > divisor) // Aktuelle tal er større end den forrige divisor
                {
                    divisor = n;
                }
            }
        }
    }
    printf("GCD = %d\n(The biggest divisor between the number %d and %d)\n\n", divisor, a, b);

    return 0;

    // Lavet af Sebastian Truong, grp. A409, Aalborg Universitet (2020).
}