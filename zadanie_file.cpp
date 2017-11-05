
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

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
	
	    printf(" ");
	    do
	    {
	      z = fgetc(fr);
	      printf("%c",z);
		  if (z == EOF) break; 
	    } while ( z != '\n');
         
	
	} while (z != EOF);
	printf("\n");
	
  }
  else
  {
  	printf("Neotvoreny subor\n");
  }
  return fr;
}


void odmena(FILE * sub, char * sdat)
{
  char z;
  int  x, t;
  float cena2;
  float odm = 0;
  float perc0 = 0.022, perc1 = 0.015;
  char meno[10]; char priez[16];
  char spz[8]; char typ[2]; char cena[9];
  char datum[9]; 
  char pom[2];
 

if ((sub = fopen("ppredaj.txt","rt")) != NULL)
  {
    do
	{
	
		if (fscanf(sub,"%s", meno) != EOF) x=1;
		else break;
    	
		if (fscanf(sub,"%s", priez) != EOF) x=1;     
		else break;

		fscanf(sub,"%s", spz);
    	
		fscanf(sub,"%s", typ);
		t = atoi(typ);     // prevod typu auta z retazca na int

		fscanf(sub,"%s", cena);
		{
		   	cena2 = atof(cena);  // prevod ceny v retazci na float
		}
		
		if (fscanf(sub,"%s", datum) != EOF) x=1; 
		else break;
		
		// teraz mozem vypocitat odmenu , potrebujem vediet typ auta , datum ci splna 1 rok od aktualneho datumu a cenu
		
		if (datum <= sdat)      // porovnaj datum zamestnania s aktualnym datumom ale o 1 rok nizsim  
		{
			if (t == 1)
			{
				odm = cena2*perc1;  // odmena z ceny ak nove auto
			}
			else
			{
				odm = cena2*perc0;  // odmena z ceny ak stare auto
			}
			printf("%s %s %s %.2lf\n",meno,priez,spz,odm); 
			//printf("%s %s %s %s %.2lf %d %s\n",meno,priez,spz,cena,odm,t, datum);  // pomocny vypis
		}
		    
	} while (true);
		
  }
  
}


int main()
{

char znak, c = 'x';
int rok, mesiac, den;
char srok[5] ;
char smes[3];
char sden[3];
char sdatum[9] = "";
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
itoa((rok-1),srok,10);      // konverzia rok ako cislo na retazec ale o 1 rok menej -- musi byt 1 rok zamestnanec
itoa(mesiac,smes,10);   
itoa(den,sden,10);		 


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
		strcat(sdatum,srok);
		if (mesiac < 10) 
		{
			strcat(sdatum,"0");
			strcat(sdatum,smes);
		}
		else {strcat(sdatum,smes);}
		
		if (den < 10) 
		{
			strcat(sdatum,"0");
			strcat(sdatum,sden);
		}
		else {strcat(sdatum,sden);}
		
		if (c == 'v')    // iba ak bola volba "v"
		{
			odmena(ff, sdatum);
		}
		break;
	}
	case 'n' :
		{
			break;
		}
	case 's' :
		{
			break;
		}
	case 'p' :
		{
			break;
		}
	case 'z' :
		{
			break;
		}
    default: continue;
  }
} while(znak != 'k');

if (c == 'v') fclose(ff);

return 0;
}

