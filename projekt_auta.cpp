#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"


typedef struct auta
{
	char kategoria[50];
	char znacka[50];
	char predajca[100];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
	struct auta *next;	
} Tauta;

void nacitaj(FILE *fr, Tauta **z, Tauta **k, int *n); 

int main()
{
	FILE *sub;
	Tauta *zac, *kon;
	int c, pocet;

	zac = kon = NULL;
	sub = NULL;
	pocet = 0;

	do {
	    system("cls");   						// namiesto clrscr();
	    printf("Nacitaj subor ........ n\n");
	    printf("Pridaj ............... p\n");
	    printf("Vypis ................ v\n");
	    printf("Zmaz ................. z\n");
	    printf("Hladaj ............... h\n");
	    printf("Aktualizuj (bonus).... a\n");
	    printf("Koniec ............... k\n");
	
	    switch (c = getch()) 
		{
	      case 'n': nacitaj(sub, &zac, &kon, &pocet); break;
	      case 'p': /*pridaj(zac);*/  break;
	      case 'v': /*vypis(zac);*/ break;
	      case 'z': /*zmaz(&zac, &kon);*/ break;
	      case 'h': /*hladaj(zac);*/ break;
	      case 'a': /*aktualizuj(zac);*/ break;
	      default: continue;
	    }
	
	  } while (c != 'k');


 return 0;
}


void nacitaj(FILE *fr, Tauta **z, Tauta **k, int *n)
{
	char meno[200];
	int znak, i; 
	 
	//printf("Nacitavam subor \n");
	
	if ((fr = fopen("auta.txt","r")) == NULL)		//testovanie otvorenia suboru
	{
		printf ("Zaznamy neboli nacitane\n"); 		//vypise ak sa subor nepodarilo otvorit
	}	
	else 
	{
		i = 0;
		while(znak != EOF)
		{
			do
			{
				znak = fgetc(fr) ;
				if (znak == EOF) break;
				if (znak == '\0') printf(" es ");
				if (znak == '$') *n = *n+1; 			// pocita zaznamy v subore
				if (znak == '\n') 
				{
					meno[i] = '\0';   	// ukonci ako retazec
					i=0;				// vynuluj i na zaciatok
					printf("meno: %s\n", meno);
				}
				if ((znak != EOF) && (znak != '\0') && (znak != '$') && (znak != '\n'))
				{
					meno[i] = znak; 
					i++;
				}
				//printf("%c", znak);

			} while(znak != '\n') ;
			
		};
		
		printf ("Nacitalo sa %d zaznamov\n", *n); 	//vypise pocet nacitanych zaznamov		
	}
	
	if (fr != NULL) fclose(fr);
	
	getch();
}
