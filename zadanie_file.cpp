
/*
	Denisa Mensatorisová
	Zadanie ZS 2017
	3.11.2017
*/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

FILE *vypis(FILE *fr)
{
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
	int x, i ;   
	int n = 0;           /* pocet zaznamov */
	int velkost = 0;     /* velkost pola SPZ */
	char meno[10]; char priez[16]; char spz[7]; char typ[2]; char cena[9]; char datum[8]; 
	char *pom;	   /* pre ulozenie zaciatok pola */
	FILE *p_fw;

	pom = NULL;
	p_fw = NULL;
	
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
		
		
		//printf("pocet zaznamov: %d\n", n);
		//printf("velkost pola SPZ: %d\n", velkost);	/* len na test vypisy */
			
		rewind(sub);      // smernik chod na zaciatok suboru
	
		//printf("adresa pole pred: %p\n", pole);		/* len na test */
		
		if (pole == NULL)
		{
			pole = (char *)malloc(n*velkost);
			if (pole == NULL) 
			{
				printf("chyba alokacia pamat pola\n");
				return pole;
			}
			pom = pole;			/* odpamataj si zaciatocnu adresu */
		}
		else
		{
			free(pole);
			pole = NULL;
			pole = (char *)malloc(n*velkost);		/* smernik ide len po 1 byte a nie po 7 */			
			if (pole == NULL) 
			{
				printf("chyba alokacia pamat pola\n");
				return pole;
			}
			pom = pole;
		}
		
		//printf("adresa pole po alokacii: %p\n", pole); 		/* len na test */

		/* teraz naplnim pole SPZ */
		n = 0;
	    do
		{	
			if (fscanf(sub,"%s", meno) != EOF) x=1;
			else break;	    	
			if (fscanf(sub,"%s", priez) != EOF) x=1;     
			else break;
	
			fscanf(sub,"%s", pole);
			//printf("adresa pole pri %d plneni: %p\n", n, pole); 		/* len na test */
			pole = pole+7;							// smernik pole je typu char ide len po 1 byte takze ho musim zvysit o 7 = dlzku SPZ
			n++;
	    	
			fscanf(sub,"%s", typ);
			fscanf(sub,"%s", cena);			
			if (fscanf(sub,"%s", datum) != EOF) x=1;
			else break;
			 
		} while (true);
		
		pole = pom;			/* nastav adresu smernika pole na zaciatok */
		rewind(sub);        // smernik na subor na zaciatok 
		
		
		// potrebujeme este ulozit aj pre ine funkcie pocet zaznamov v subore
		
		p_fw = fopen(".\\poczaznamov.txt", "w");
		if (p_fw != NULL)
		{
			fprintf(p_fw,"%d\n",n);
			fflush(p_fw);
			fclose(p_fw);
		}
		else
		{
			printf("chyba pri zapise do suboru\n");
		}
				
		//printf("adresa pole po naplneni a nastaveni na zaciatok: %p\n", pole); 		// len na test 
		
		/*
		printf("obsah pola :\n");
		for (i = 0; i<n*velkost;i++)
		{ 
			printf("%c", *pole);		// OK - na test 
			pole++;
		}
		printf("\n");
		*/
		pole = pom;		// nastav adresu smernika pole na zaciatok
		 
	}
		
	return pole;
}


void vypisSPZ(char *pole)
{
	char *pom;	   /* pre ulozenie zaciatok pola */
	int i = 0; int j; int n = 0;
	FILE *p_fr;
	
	pom = NULL;
	p_fr = NULL;
		
	if (pole == NULL)
	{
		printf("Pole nie je vytvorene\n");
	}
	else
	{
		// zistim najprv pocet zaznamov ulozeny v subore
		p_fr = fopen(".\\poczaznamov.txt", "r");
		if (p_fr != NULL)
		{
			fscanf(p_fr,"%d",&n);
			fclose(p_fr);
		}
		else
		{
			printf("chyba pri citani zo suboru\n");
		}

		pom = pole;
		for (i=0; i < n ; i++)
		{
			for (j=0; j < 7; j++)      // 7 je dlzka SPZ
			{
				printf("%c", *pole);
				if((j == 1) || (j == 4)) printf(" ");		/* vloz medzeru */
				pole++;	
			}
			printf("\n");
		}
		pole = pom;
	}	
}


void vypisPalindrom(char *pole)
{
	char *pom;	   /* pre ulozenie zaciatok pola */
	int i = 0; int n = 0;
	FILE *p_fr;	
	
	pom = NULL;
	p_fr = NULL;
	
	if (pole == NULL)
	{
		printf("Pole nie je vytvorene\n");
	}
	else
	{
		// zistim najprv pocet zaznamov ulozeny v subore
		p_fr = fopen(".\\poczaznamov.txt", "r");
		if (p_fr != NULL)
		{
			fscanf(p_fr,"%d",&n);
			fclose(p_fr);
		}
		else
		{
			printf("chyba pri citani zo suboru\n");
		}
				
		pom = pole;
		for (i=0; i < n ; i++)
		{
			if( (*pole == *(pole+6)) && (*(pole+1) == *(pole+5)) && (*(pole+2) == *(pole+4)) )
			{
				printf("%c%c\n", *pole, *(pole+1));   // OK
				//printf("%c%c%c%c\n", *pole, *(pole+1), *(pole+2), *(pole+3));   // test
				pole = pole + 7;
			}
			else
			{
				pole = pole+7;
			}
		}
		pole = pom;
	}	
}



void Bonus(char *pole)
{
	char *pom; char *pole2;	   /* pre ulozenie zaciatok pola */
	int i = 0; int j = 0; int n = 0;
	FILE *p_fr;	
	
	pom = NULL; pole2 = NULL; p_fr = NULL;
	
	if (pole == NULL)
	{
		printf("Pole nie je vytvorene\n");
	}
	else
	{
		// zistim najprv pocet zaznamov ulozeny v subore
		p_fr = fopen(".\\poczaznamov.txt", "r");
		if (p_fr != NULL)
		{
			fscanf(p_fr,"%d",&n);
			fclose(p_fr);
		}
		else
		{
			printf("chyba pri citani zo suboru\n");
		}
						
		int pocet[n]; int maxpocet = 1;
		
		for (i = 0; i < n; i++) 
		{
			pocet[i] = 1;
		}
		
		pom = pole;
		pole2 = pole+7;  // pole2 bude sluzit na krokovanie v dalsom cykle
		
		for (i = 0; i < (n-1) ; i++)          // posun pole
		{			
		    //printf("%d %c%c\n", i, *pole, *(pole+1));    // len na test
		    
			for( j = (i+1); j < n; j++ )      // posun pole2 
			{
			    //printf("  %d %c%c\n", j, *pole2, *(pole2+1));    // len na test
			    
				if( (*pole == *pole2) && (*(pole+1) == *(pole2+1)) )
				{
					pocet[i] = (pocet[i] + 1);    // ak je zhoda tak zvys pocet pre i-ty prvok-okres
					if (pocet[i] > maxpocet) 
					{
						maxpocet = pocet[i];      // ak je viac ako maxpocet tak aktualizuj maxpocet
					}
				}
				pole2 = pole2 + 7;    // skoc na dalsiu SPZ
			}
			pole = pole + 7;    // skoc na dalsiu SPZ
			pole2 = pole + 7;   // skoc na dalsiu SPZ ale o 1 vyssiu ako ukazuje pole
		}
		pole = pom;
		pole2= pom;

		/*
		printf("adresa pole bonus: %p\n", pole); 		// len na test 

		for (i = 0; i < n; i++) 
		{
			printf("pocet %d : %d\n", i, pocet[i] );    // len na test 
		}
		*/
		
		for (i = 0; i < n ; i++)         // vypis vysledok - okres s najviac predanych aut
		{
			if(pocet[i] == maxpocet)
			{ 
				printf("%c%c %d\n", *pole, *(pole + 1), pocet[i]);    // OK - ak by bolo viac s maxpocet tak vypise vsetky s maxpocet
			}
			pole = pole+7;   // skoc na dalsiu SPZ
		}
		pole = pom;
	}	
	
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
		/*
		printf(" %d%02d%02d\n", rok,mesiac,den); 
		sdatum[0] = '\0';      // vynuluje retazec a poskladaj ho z rok, mesiac, den
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
		*/
		
		printf("zadaj aktualny datum v tvare \"RRRRMMDD\" : ");
		scanf("%s",&sdatum);
		printf("zadal si %s\n", sdatum);        // len test ci to robi dobre
				
		if (c == 'v')     // iba ak bola volba "v"
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
			//printf("adresa pole po navrate z funkcie n: %p\n", p_pole);		// OK - len na test 		
		}
		break;
	}
	case 's' :
		{
			vypisSPZ(p_pole);
			//printf("adresa pole po navrate z funkcie s: %p\n", p_pole);		// OK - len na test 		
			break;
		}
	case 'p' :
		{
			vypisPalindrom(p_pole);   // OK
			break;
		}
	case 'z' :
		{
			Bonus(p_pole);     // OK
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

fclose(ff);

//if (ff != NULL) free((void *)ff);              // pri tomto vykazuje chybu ??!!! - neviem preèo nechce uvo¾ni pamä
ff = NULL;

if (p_pole != NULL) free((void *)p_pole);      // toto urobi OK !
p_pole = NULL;

return 0;
}

