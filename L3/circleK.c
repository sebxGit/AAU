#include <stdio.h>
#include <math.h>

double r, x, y, dan, delta;

int main(){
    printf("Indtast x, y og r som floats (kommatal) og se om radius er inde i cirkel, periferien og uden for cirklen.");
    scanf("%lf%lf%lf", &x, &y, &r);
    printf("");
    printf("%.2lf, %.2lf, %.2lf\n", x, y, r);
    delta = r * 0.1;
    printf("sqrt(%lf^2 + %lf^2) = %lf", x, y, r);
    dan = sqrt(pow(x,2)+pow(y,2));

    /*
    if (dan < r){
        printf("This is small pp");
    }
    else if(dan == r){
        printf("This is normal size pp");
    }
    else{
        printf("This is bbc");
    }
    */

    (dan > r) ? printf("I cirklen") : (dan - delta <= r <= dan + delta) ? printf("Periferien") : printf("Uden for cirklen");
    
    return 0;
}