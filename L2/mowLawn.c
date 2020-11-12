#include <stdio.h>
#include <math.h>

int main(){
    int ln_f, wd_f, ln_h, wd_h, area_f, area_h, area_g, a, ct;

    printf("Type length and width of foundation:\n");
    scanf("%d", &ln_f);
    scanf("%d", &wd_f);

    printf("Type length and width of house:\n");
    scanf("%d", &ln_h);
    scanf("%d", &wd_h);

    /*Finding area*/
    area_f = ln_f * wd_f;
    area_h = ln_h * wd_h;
    area_g = area_f - area_h;

    printf("Foundation: %d, House: %d, Grass: %d", area_f, area_h, area_g);

    ct = 0;

    for(area_g; area_g > 2; area_g -= 2){
        ct++;
    }

    printf("\nCount (secs): %d", ct);
    return 0;
}
