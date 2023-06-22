#include <stdio.h>
#include <stdlib.h>

enum forret {guacamole, tarteletter, lakserulle, graeskarsuppe};
enum hovedret {gyldenkaal, hakkeboef, gullash, forloren_hare};
enum dessert {pandekager_med_is, gulerodskage, chokolademousse, citronfromage};

int main(void){
    srand(time(NULL));


}

void make_random_forret(){
    return (rand() % 4);
}
