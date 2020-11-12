#include <stdio.h>
#include <math.h>

#define INPUT_SIZE 50

/* Sebastian Truong, Grp. A409, Aalborg Universitet Software 1. semester 2020 */

/*Programmet akkumulerer tal vha. operatorer, hvilket vil forts�ttes indtil
  brugeren hopper ud af loopet. */

/* Her har jeg modtaget hj�lp til stdin med fgets af en medstuderende. Kunne ikke
  gennemskue, hvad *stream bet�d pga. bl.a. manglende eksempler fra nettet.
  Kigget på internettet hvordan man bruger pointers og hvad syntaksen til
  switches er. */

double run_calculator(void);
void scan_data(char *op, double *val);
void do_next_op(char *op,  double *val, double *accumulator, int *calculating);

int main(void)  {
  run_calculator();
  return 0;
}

double run_calculator(void){
  int calculating = 1;
  double val = 0.0, accumulator = 0.0;
  char op;

  /* Hopper ud af while-l�kken n�r brugeren skriver q. Tjekket ved do_next_op()*/
  while(calculating){
    printf("Enter operator, and an optional operand: ");

    scan_data(&op, &val);
    do_next_op(&op, &val, &accumulator, &calculating);

    if (op == 'q')
      printf("Final result is: %lf.\n", accumulator);
    else
      printf("Result so far is %lf.\n", accumulator);
  }

  return accumulator;
}

void scan_data(char *op, double *val) {
  /* Indl�ser det tastede i terminalen og parser string til de respektive datatyper. */
  char input[INPUT_SIZE];
  fgets(input, INPUT_SIZE, stdin);
  sscanf(input, "%c %lf", &*op, &*val);
}

void do_next_op(char *op, double *val, double *accumulator, int *calculating){

  /* Tager b�de de un�re og bin�re operatorer, hvoraf de un�re kun best�r af en
     kalkulation, mens bin�re blot benytter to. Dette skelnes ved formlerne
     brugt.*/

  switch(*op){
    case '+': *accumulator += *val; break;
    case '-': *accumulator -= *val; break;
    case '*': *accumulator *= *val; break;
    case '/': (*val != 0) ? *accumulator /= *val : *accumulator; break;
    case '^': *accumulator = pow(*accumulator, *val); break;
    case '#': (*accumulator > 0) ? *accumulator = sqrt(*accumulator) : *accumulator; break;
    case '%': *accumulator = -*accumulator; break;
    case '!': *accumulator = 1 / *accumulator; break;
    case 'q': *calculating = 0; break;
  }
}
