#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int promt()
{
    int dies_called;
    do
    {
        printf("How many dies do you want to throw over 5?\n");
        scanf("%d", &dies_called);
    } while (dies_called < 5);
    return dies_called;
}

int dice_roll()
{
    return (int)rand() % 6;
}

int *roll_multiple_dies(int ct)
{
    int *tb = (int *)malloc(ct * sizeof(int));
    if (tb == NULL)
    {
        printf("Cannot allocate memory. Exit.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < ct; i++)
    {
        tb[i] = dice_roll();
    }
    return tb;
}

/* Compares if n in array is equivalent with num. Accumulates and returns the
   value of the sum of all occurences of num. */
int alike(const int tb[], const int ct_array, const int num, int *score)
{
    int sum_alikeNum = 0;

    for (int i = 0; i < ct_array; i++)
    {
        if (tb[i] == num)
        {
            sum_alikeNum += num;
        }
    }
    *score += sum_alikeNum;
    return sum_alikeNum;
}

/* Compares two numbers and returns ints to qsort, which it will interpret. */
int n_cmp(const void *ep1, const void *ep2)
{
    int *tp1 = (int *)ep1,
        *tp2 = (int *)ep2;
    if (*tp1 < *tp2)
        return -1;
    else if (*tp1 > *tp2)
        return 1;
    else
        return 0;
}

void pair(const int tb[], const int ct_array, int *score)
{
    int prev_num = -1, pairs = 0;

    for (int i = 0; i < ct_array; i++)
    {
        if (tb[i] == prev_num)
        {
            // Assuming 1 pair = 0, if there are two pairs.
            pairs += 1;
            *score += tb[i] + prev_num;
            i++; // Skips next number, because it is already in pair.
        }
        prev_num = tb[i];
    }
    printf("\nPairs: %d, Score: %d", pairs, *score);
}

void ofAKind(const int tb[], const int ct_array, int *score)
{
    for (int i = 0; i < ct_array - 3; i++)
    {
        if (tb[i] == tb[i + 1] && tb[i] == tb[i + 2] && tb[i] == tb[i + 3])
        {
            *score += tb[i] * 4;
            printf("\nFour of a kind: Num %d, Score: %d", tb[i], *score);
            break;
        }
    }

    for (int i = 0; i < ct_array - 2; i++)
    {
        if (tb[i] == tb[i + 1] && tb[i] == tb[i + 2])
        {
            *score += tb[i] * 3;
            printf("\nThree of a kind: Num %d, Score: %d", tb[i], *score);
            break;
        }
    }
}

void straight(const int tb[], const int ct_array, int *score)
{
    /* Making a new string from the original array to a string. */
    char tb_inString[6];
    for (int i = 0; i < ct_array; i++)
    {
        tb_inString[i] = tb[i] + '0'; /* Syntax for converting an int to a char. */
    }
    tb_inString[5] = '\0'; /* Strings have this null value on the last element of the array.*/

    if (strcmp(tb_inString, "12345") == 0)
    {
        printf("\nSmall Straight!");
        *score += 15;
    }

    if (strcmp(tb_inString, "23456") == 0)
    {
        printf("\nLarge Straight!");
        *score += 20;
    }
    printf("\nStraights score: %d", *score);
}

void fullHouse(const int tb[], const int ct_array, int *score)
{
    // ONLY CONCEPT, BUT ONLY USE WHEN RESTRUCTURED
    if (pair == 1 && ofAKind == 3)
    {
        if (tb[0] == tb[2])
        {
            *score += tb[0] * 3 + tb[4] * 2;
        }
        else
        {
            *score += tb[0] * 2 + tb[4] * 3;
        }
    }
}

void chance(const int tb[], const int ct_array, int *score)
{
    for (int i = 0; i < ct_array; i++)
    {
        *score += tb[i];
    }
    printf("\nChance score %d", *score);
}

void yatzy(const int tb[], const int ct_array, int *score)
{
    /* Making a new string from the original array to a string. */
    char tb_inString[6];
    for (int i = 0; i < ct_array; i++)
    {
        tb_inString[i] = tb[i] + '0'; /* Syntax for converting an int to a char. */
    }
    tb_inString[5] = '\0'; /* Strings have this null value on the last element of the array.*/

    if (strcmp(tb_inString, "55555") == 0)
    {
        printf("Yatzy! ");
        *score += 15;
    }
    printf("Yatzy score: %d", *score);
}

int main(void)
{
    time_t t;
    srand((unsigned)time(&t));
    int dies_total = promt();
    int score;

    int *tb = roll_multiple_dies(dies_total);

    for (int k = 0; k < dies_total; k++)
    {
        printf("%d  ", tb[k]);
    }

    printf("\n");

    // Upper section
    int single_score_cap = 0;
    for (int n = 1; n <= 6; n++)
    {
        int n_sum = alike(tb, dies_total, n, &score);
        single_score_cap += n_sum;
        printf("%d: %d\n", n, n_sum);
    }

    // Lower section
    qsort(tb, dies_total, sizeof(int), n_cmp);
    for (int k = 0; k < dies_total; k++)
    {
        printf("%d  ", tb[k]);
    }

    pair(tb, dies_total, &score);
    ofAKind(tb, dies_total, &score);
    straight(tb, dies_total, &score);
    chance(tb, dies_total, &score);
    yatzy(tb, dies_total, &score);

    printf("\nTotal Score: %d\n", score);

    free(tb);
    return 0;
}
