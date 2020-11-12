#include <stdio.h>
#include <math.h>

int main(){
    int n, m;
    double s1, s2, hyp, res;

    printf("Indtast variabel 1 i heltal n.\n");
    scanf("%d", &n);

    printf("\nIndtast et større heltal end det før for variabel 2.\n");
    scanf("%d", &m);

    s1 = m * m - n * n;
    s2 = 2 * m * n;
    hyp = m * m + n * n;

    printf("s1: %.2lf, s2: %.2lf, hyp: %.2lf\n", s1, s2, hyp);

    res = pow(s1, 2) + pow(s2, 2);

    printf("s1^2: %.2lf + s2^2: %.2lf = c^2: %.2lf", pow(s1, 2), pow(s2, 2), res);

    return 0;

}