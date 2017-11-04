
#include "stdio.h"

FILE * vypis()
{
  FILE *fr;
  char z;
  char meno[50];
  char spz[7];
  char typ;
  char cena[8];
  char datum[8];

  if ((fr = fopen("ppredaj.txt","rt")) != NULL)
  {
    printf("meno priezvisko: ");
    do
    {
      z = fgetc(fr);
      printf("%c",z);
    } while ( z != '\n');
    //printf("%c",z);

	fgets(text, sizeof(text), fr);
    printf("SPZ: ");
    fputs(text,stdout);
    
    /*
    do
    {
      z = fgetc(fr);
      printf("%c",z);
    } while ( z != '\n');
    printf("%c",z);
    */
  }

  return fr;
}

int main()
{

char znak;
int (*pv_f)();
FILE * ff;

printf("v - otvori subor a vypise zaznamy \n");
printf("o - vypis odmien \n");
printf("n - spocita pocet zaznamov, SPZ zapise do pola \n");
printf("s - vypis SPZ \n");
printf("p - vypis skratku okresu z SPZ \n");
printf("z - vypis okres s najvacsim poctom predanych aut \n");
printf("k - koniec programu \n");

do
{
  znak = getchar();
  switch(znak)
  {
    case 'v': ff = vypis();
    default: continue;
  }
} while(znak != 'k');

fclose(ff);

return 0;
}
