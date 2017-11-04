
#include "stdio.h"

FILE * vypis()
{
  FILE *fr;
  char z;
  char popis1[18] = "meno priezvisko: ";
  char popis2[6] = "SPZ: ";
  char popis3[6] = "typ: ";
  char popis4[7] = "cena: ";
  char popis5[8] = "datum: ";
  char meno[50];
  char spz[7];
  char typ;
  char cena[8];
  char datum[8];
  char text[50];

  if ((fr = fopen("ppredaj.txt","rt")) != NULL)
  {

	
    printf(popis1);
    do    
    {
      z = fgetc(fr);
      printf("%c",z);
    } while ( z != '\n');
    //printf("%c",z);
    
    printf(popis2);
    do
    {
      z = fgetc(fr);
      printf("%c",z);
    } while ( z != '\n');
    //printf("%c",z);
    

    printf(popis3);
    do
    {
      z = fgetc(fr);
      printf("%c",z);
    } while ( z != '\n');
    //printf("%c",z);

    printf(popis4);
    do
    {
      z = fgetc(fr);
      printf("%c",z);
    } while ( z != '\n');
    //printf("%c",z);

    printf(popis5);
    do
    {
      z = fgetc(fr);
      printf("%c",z);
    } while ( z != '\n');
    //printf("%c",z);

    
    /*
	fgets(text, sizeof(text), fr);
    printf(popis1);
    fputs(text,stdout);

	fgets(text, sizeof(text), fr);
    printf(popis2);
    fputs(text,stdout);

	fgets(text, sizeof(text), fr);
    printf(popis3);
    fputs(text,stdout);

	fgets(text, sizeof(text), fr);
    printf(popis4);
    fputs(text,stdout);

	fgets(text, sizeof(text), fr);
    printf(popis5);
    fputs(text,stdout);

	fgets(text, sizeof(text), fr);
    fputs(text,stdout);
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
