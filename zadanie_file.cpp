
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

FILE *vypis(FILE *fr)
{
  //FILE *fr;
  int z;
  char popis1[] = "meno priezvisko: ";
  char popis2[] = "SPZ: ";
  char popis3[] = "typ: ";
  char popis4[] = "cena: ";
  char popis5[] = "datum: ";

  
	if (fr == NULL)
	{
	  	fr = fopen("ppredaj.txt","rt");
	}
    
	if (fr != NULL)
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
	         		
		} while(z != EOF);
		
		printf("\n");	
		rewind(fr);
	}
	else
	{
	  	printf("Neotvoreny subor\n");
	}
  
  return fr;
}


void odmena(FILE *sub, char *sdat)
{

	int  x, t;
	float cena2; float odm = 0;
	float perc0 = 0.022, perc1 = 0.015;
	char meno[10]; char priez[16]; char spz[7]; char typ[2]; char cena[9]; char datum[8]; char pom[2];

	//if ((sub = fopen("ppredaj.txt","rt")) != NULL)
	if (sub != NULL)
  	{	
	    do
		{	
			if (fscanf(sub,"%s", meno) != EOF) x=1;
			else break;
	    	
			if (fscanf(sub,"%s", priez) != EOF) x=1;     
			else break;
	
			fscanf(sub,"%s", spz);
	    	    	
			fscanf(sub,"%d", &t);       // nacita typ auta z textu priamo ako int
			/*
			fscanf(sub,"%s", typ);      // nacita typ auta z textu ako retazec 
			t = atoi(typ);              // prevod typu auta z retazca na int
			*/
			
			fscanf(sub,"%f", &cena2);   // nacita cenu z textu priamo ako float
			/*
			fscanf(sub,"%s", cena);     // nacita cenu ako retazec  
		   	cena2 = atof(cena);         // prevod ceny v retazci na float
			*/
			
			if (fscanf(sub,"%s", datum) != EOF) x=1; 
			else break;
			
			// teraz mozem vypocitat odmenu , potrebujem vediet typ auta , datum ci splna 1 rok od aktualneho datumu a cenu
			
			if (strcmp(datum, sdat) <= '\0')     // porovnaj datum zamestnania s aktualnym datumom ale o 1 rok nizsim  
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
				//printf("%s %s %s %s %.2lf %d %s\n",meno,priez,spz,cena,odm,t,datum);    // pomocny vypis
			}
			    
		} while (true);
		
		rewind(sub);
		
  	}
  
}


char *vytvorpole(FILE *sub, char *pole)
{
	//char *pole;
	int x ;   
	int n = 0;        // pocet zaznamov
	int velkost = 0;  // velkost pola SPZ
	char meno[10]; char priez[16]; 
	char spz[7]; char typ[2]; char cena[9]; char datum[8]; 
	char pspz[1][7]; 

	//if ((sub = fopen("ppredaj.txt","rt")) != NULL)
	if (sub != NULL)
	{
	    do
		{	
			if (fscanf(sub,"%s", meno) != EOF) x=1;
			else break;
	    	
			if (fscanf(sub,"%s", priez) != EOF) x=1;     
			else break;
	
			fscanf(sub,"%s", spz);
			velkost = sizeof(spz);
			n++;
	    	
			fscanf(sub,"%s", typ);
	
			fscanf(sub,"%s", cena);
			
			if (fscanf(sub,"%s", datum) != EOF) x=1;
			else break;
			 
		} while (true);
		
		printf("pocet zaznamov: %d\n", n);
		printf("velkost pola SPZ: %d\n", velkost);
			
		rewind(sub);
	
		printf("pole pred: %p\n", pole);
		
		if (pole == NULL)
		{
			pole = (char *)malloc(n*velkost);
			if (pole == NULL) return pole;
		}
		else
		{
			free(pole);
			pole = NULL;
			pole = (char *)malloc(n*velkost);			
			if (pole == NULL) return pole;
		}
		printf("pole po: %p\n", pole);

		
		rewind(sub);
			
	}
		
	return pole;
}


int main()
{

int znak, c = 'x';
int rok, mesiac, den;
char srok[5] ; char smes[3]; char sden[3]; char sdatum[9] = "";
time_t datum;
tm *str;

FILE *ff; char *p_pole;

ff = NULL; p_pole = NULL;

printf("v - otvori subor a vypise zaznamy \n");
printf("o - vypis odmien \n");
printf("n - spocita pocet zaznamov, SPZ zapise do pola \n");
printf("s - vypis SPZ \n");
printf("p - vypis skratku okresu z SPZ \n");
printf("z - vypis okres s najvacsim poctom predanych aut \n");
printf("k - koniec programu \n");

printf("\n");

// zistim aktualny datum
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
		ff = vypis(ff);
		break;
	}
    case 'o': 
	{
		printf(" %d%02d%02d\n", rok,mesiac,den); 
		sdatum[0] = '\0';      // vynuluje retazec
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

		printf("%s\n", sdatum);      // len test ci to robi dobre
				
		if (c == 'v')    // iba ak bola volba "v"
		{
			odmena(ff, sdatum);
		}
		break;
	}
	case 'n' :
	{
		if (c == 'v')    // iba ak bola volba "v"
		{
			p_pole = vytvorpole(ff, p_pole);
			printf("pole vrat: %p\n", p_pole);			
		}
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

// zatvorim subor a uvolnim pamat
if (c == 'v') 
{
	if (ff != NULL) fclose(ff);
}

//if (ff != NULL) free(ff);
ff = NULL;
//if (p_pole != NULL) free(p_pole);
p_pole = NULL;

return 0;
}

