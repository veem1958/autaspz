
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

FILE * vypis()
{
  FILE *fr;
  char z;
  char popis1[] = "meno priezvisko: ";
  char popis2[] = "SPZ: ";
  char popis3[] = "typ: ";
  char popis4[] = "cena: ";
  char popis5[] = "datum: ";

    
  if ((fr = fopen("ppredaj.txt","rt")) != NULL)
  {

	do
	{
	
	    printf(popis1);
	    do    
	    {
	      z = fgetc(fr);
	      printf("%c",z);
		  if (z == EOF) break; 
	    } while ( z != '\n');
	    
	    printf(popis2);
	    do
	    {
	      z = fgetc(fr);
	      printf("%c",z);
		  if (z == EOF) break; 
	    } while ( z != '\n');    
	
	    printf(popis3);
	    do
	    {
	      z = fgetc(fr);
	      printf("%c",z);
		  if (z == EOF) break; 
	    } while ( z != '\n');
	
	    printf(popis4);
	    do
	    {
	      z = fgetc(fr);
	      printf("%c",z);
		  if (z == EOF) break; 
	    } while ( z != '\n');
	
	    printf(popis5);
	    do
	    {
	      z = fgetc(fr);
	      printf("%c",z);
		  if (z == EOF) break; 
	    } while ( z != '\n');
	
	    printf("..");
	    do
	    {
	      z = fgetc(fr);
	      printf("%c",z);
		  if (z == EOF) break; 
	    } while ( z != '\n');
         
	
	} while (z != EOF);
	
  }

  return fr;
}


void odmena(FILE * sub)
{
  char z;
  int  x;
  float cena2;
  char meno[10];
  char priez[16];
  char spz[8];
  char typ[2];
  char cena[9];
  char datum[9];
  char prazdny[2];
  char pom[2];


if ((sub = fopen("ppredaj.txt","rt")) != NULL)
  {
    do
	{
	
		if (fscanf(sub,"%s", meno) != EOF) x=1;
		else break;
    	
		if (fscanf(sub,"%s", priez) != EOF) x=1;     //printf("%s %s\n",meno,priez);
		else break;

		fscanf(sub,"%s", spz);
    	//printf("%s %s %s\n",meno,priez,spz);
    	
		fscanf(sub,"%s", typ);

		fscanf(sub,"%s", cena);
		{
		   	printf("%s %s %s %s\n",meno,priez,spz,cena);
		   	cena2 = atof(cena);
		   	printf("cena float : %.2lf\n", cena2);
		}
		
		if (fscanf(sub,"%s", datum) != EOF) x=1; 
		else break;
		    
	} while (true);
		
  }
}


int main()
{

char znak, c ;
int rok, mesiac, den;
time_t datum;
tm *str;
FILE * ff;

printf("v - otvori subor a vypise zaznamy \n");
printf("o - vypis odmien \n");
printf("n - spocita pocet zaznamov, SPZ zapise do pola \n");
printf("s - vypis SPZ \n");
printf("p - vypis skratku okresu z SPZ \n");
printf("z - vypis okres s najvacsim poctom predanych aut \n");
printf("k - koniec programu \n");

printf("\n");

// zistime aktualny datum
time(&datum); 
str = localtime(&datum);
rok = (str->tm_year + 1900);
mesiac = (str->tm_mon+1);	
den = str->tm_mday;		 
/*
printf("datum je : %s\n",asctime(str));
printf("rok je : %d\n", rok);
printf("mesiac je : %02d\n", mesiac);
printf("den je : %02d\n", den);
printf("datum : %d%02d%02d\n", rok,mesiac,den); 
*/

do
{
  znak = getchar();
  switch(znak)
  {
    case 'v': 
	{
		c = 'v';
		ff = vypis();
		break;
	}
    case 'o': 
	{
		printf(" %d%02d%02d\n", rok,mesiac,den); 
		odmena(ff);
		break;
	}
    default: continue;
  }
} while(znak != 'k');

if (c == 'v') fclose(ff);

return 0;
}

