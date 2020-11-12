#include <stdio.h>
/* AMAZING STORYLINE WITH GREAT PLOT. CHOOSE HOW THE STORY WILL GO. */

int main(void)
{
    /* Lokale variabler */
    char strname[10], strAdj[10], strNoun[10];
    char name, adjective, noun;

    printf("Type a name.\n>>");
    name = scanf("%s", strname);

    printf("Type an adjective.\n>>");
    adjective = scanf("%s", strAdj);

    printf("Type a noun.\n>>");
    noun = scanf("%s", strNoun);



    /* Udskriver tekst og bruger skriver et input til historien*/
    printf("Der var engang et lille svin, som hed %s.\nHan loeib meget %s og var glad for at spise %s.\n-----------------THE END-----------------", &strname, &strAdj, &strNoun);

    return 0;
}
