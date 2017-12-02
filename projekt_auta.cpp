#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
#include "ctype.h"


typedef struct auta
{
	char kategoria[50];
	char znacka[50];
	char predajca[100];
	int cena;
	int rok_vyroby;
	char stav_vozidla[200];
	struct auta *dalsi;	
} Tauta;


void nacitaj(FILE *fr, Tauta **z, Tauta **k); 
void vypis(Tauta *z); 
void pridaj(Tauta **z, Tauta **k); 
void zmaz(Tauta **z, Tauta **k);
void hladaj(Tauta *z);
void aktualizuj(Tauta *z);

//--------------------------------------------------------------------

void ZmazZoznam(Tauta **z, Tauta **k)
{
  Tauta *pom;

  while (*z != NULL) 
  {
    pom = *z;           	/* zapamätáme si pointer na prvý prvok */
    (*z) = (*z)->dalsi;     /* nový zaèiatok zoznamu */
    free((void*)pom); 		/* odstránenie prvku */  
  };	
  *k = *z;
}

//-------------------------------------------------------------------

int main()
{
	FILE *sub;
	Tauta *zac, *kon; 
	void *pom;
	int c;

	zac = kon = NULL;
	sub = NULL;

	do {
		    system("cls");   							// namiesto clrscr();
		    printf("Nacitaj subor .......... n\n");
		    printf("Pridaj ................. p\n");
		    printf("Vypis .................. v\n");
		    printf("Zmaz ................... z\n");
		    printf("Hladaj ................. h\n");
		    printf("Aktualizuj (bonus)...... a\n");
		    printf("Koniec ................. k\n");
		
		    switch (c = getch()) 
			{
		      case 'n': nacitaj(sub, &zac, &kon); break;
		      case 'p': pridaj(&zac, &kon); break;
		      case 'v': vypis(zac); break;
		      case 'z': zmaz(&zac, &kon); break;
		      case 'h': hladaj(zac); break;
		      case 'a': aktualizuj(zac); break;
		      default: break;
		    }
	
	  	} while (c != 'k');


	ZmazZoznam(&zac, &kon);  // vymaze zoznam a uvolni pamat 
	free((void *)zac);	
	free((void *)kon);
	zac = kon = NULL;	
	
 return 0;
}



//--------------------------- Bonus --------------------------------------------

void aktualizuj(Tauta *z)
{

	int i = 1; int n = 0; int vstup = 0; int dlz = 0; 
	char meno[200];
	
	if (z != NULL)	
	{
		printf("zadaj znacku: ");
		fflush(stdin);
		fgets(meno,49,stdin);		// nacita aj prazdne znaky , pocet max 49, nie zo suboru ale zo stdin bude citat (klavesnica)
		dlz = strlen(meno);
		dlz--;  					// odstranime '\n' ktore sa tam zo vstupu dostava tym ze ho nahradime \0
		meno[dlz] = '\0';
		
		printf("zadaj cenu: ");
		scanf("%d", &vstup);
		printf("\n");

 		while(z != NULL)
 		{
 			if((z->cena == vstup) && (strcmp(z->znacka,meno) == 0))		// ak sa cena zhoduje aj znacka
 			{
 				// zadaj vsetky polozky pre aktualizaciu prvku zoznamu
 				
		 		printf("kategoria: ");
				fflush(stdin);
				fgets(meno,49,stdin);		// nacita aj prazdne znaky , pocet max 49, nie zo suboru ale zo stdin bude citat (klavesnica)
				dlz = strlen(meno);
				dlz--;  					// odstranime '\n' ktore sa tam zo vstupu dostava tym ze ho nahradime \0
				meno[dlz] = '\0';
				strcpy(z->kategoria, meno);
				
				printf("znacka: ");
				fflush(stdin);
				fgets(meno,49,stdin);		// nacita aj prazdne znaky , pocet max 49, nie zo suboru ale zo stdin bude citat (klavesnica)
				dlz = strlen(meno);
				dlz--;  					// odstranime '\n' ktore sa tam zo vstupu dostava tym ze ho nahradime \0
				meno[dlz] = '\0';
				strcpy(z->znacka, meno);
				
				printf("predajca: ");
				fflush(stdin);
				fgets(meno,99,stdin);		// nacita aj prazdne znaky , pocet max 99, nie zo suboru ale zo stdin bude citat (klavesnica)
				dlz = strlen(meno);
				dlz--;
				meno[dlz] = '\0';
				strcpy(z->predajca, meno);
				
				printf("cena: ");		
				fflush(stdin);
				scanf("%8s", meno);
				z->cena = atoi(meno); 
				
				printf("rok vyroby: ");
				fflush(stdin);
				scanf("%4s",meno);
				z->rok_vyroby = atoi(meno);
		
				printf("stav vozidla: ");
				fflush(stdin);
				fgets(meno,199,stdin);
				dlz = strlen(meno);
				dlz--;
				meno[dlz] = '\0';
				strcpy(z->stav_vozidla, meno);
				
				n++;  				
 			}
 			
 			z = z->dalsi;		// chod na dalsi prvok zoznamu 
 		}
 		
 		printf("Aktualizovalo sa %d zaznamov",n);
 	}
 		
 		
  getch();		// caka na stlacenie lubovolnej klavesy 	
}


//-----------------------------------------------------------------------

void hladaj(Tauta *z)
{
	int i = 1;
	int vstup = 0;
	int nasiel = 0;
	
	if (z != NULL)	
	{
		printf("zadaj cenu: ");
		scanf("%d", &vstup);
		
 		while(z != NULL)
 		{
 			if( z->cena <= vstup )
 			{
	 			printf("%d.\n", i);
	 			printf("kategoria: %s\n", z->kategoria);
	 			printf("znacka: %s\n", z->znacka);
	 			printf("predajca: %s\n", z->predajca);
	 			printf("cena: %d\n", z->cena);
	 			printf("rok vyroby: %d\n", z->rok_vyroby);
	 			printf("stav vozidla: %s\n", z->stav_vozidla);
	 			i++;
	 			nasiel = 1;
 			}
			z = z->dalsi;
 		}
 		
 		if(nasiel == 0) printf("V ponuke su len auta s vyssou cenou.");
	}
	
  getch();		// caka na stlacenie lubovolnej klavesy 	
}


//-----------------------------------------------------------------------


void zmaz(Tauta **z, Tauta **k)
{
	
	char text[20];
	char ltext[20];
	char znac[200];
	char lznac[200];
	int n = 0; int dlz, i, j;
	Tauta *pom, *nasiel, *pred;
	
	nasiel = NULL; pred = NULL;
	
	if (*z != NULL)				// ak bol zoznam nacitany zo suboru
	{
		printf("text znacky: ");		// vstup pre vyhladanie v znacke
		scanf("%19s", text);
		dlz = strlen(text);
		
		for (i=0;i<=dlz;i++) { ltext[i]=tolower(text[i]);}		// skonvertuj zadany retazec na male pismena 
		
		//printf("%s\n", ltext);				// pomocny vypis po konverzii
		
		pom = *z;							// zacneme na zaciatku 1. prvkom
		pom->dalsi = (*z)->dalsi;
		
		while(true)
		{			
			strcpy(znac, pom->znacka);
			dlz = strlen(znac);
			for (i=0;i<=dlz;i++) { lznac[i]=tolower(znac[i]);}		// skonvertuj retazec znacka na male pismena
			//printf("%s\n", lznac);					// pomocny vypis po konverzii

			if( (strstr(lznac,ltext)) != NULL)			// vyhladaj zadany text v znacke daneho prvku
			{
				// nasiel podretazec v znacke - tento budem mazat

				if ((pom->dalsi == (*z)->dalsi) && ((*z)->dalsi == NULL) && (*z == *k))		// tento OK !
				{
					// som na 1. a zaroven aj poslednom prvku
					
					//printf("som na 1. aj poslednom prvku\n");
				    free((void*)pom); 			// odstránenie aj posledneho prvku zoznamu   
					pom = NULL;
					*z = pom;
					*k = pom;
					n++;
					break;			
				}

				if ((pom->dalsi == (*z)->dalsi) && ((*z)->dalsi != NULL))					// tento OK !
				{
					// som na 1. prvku zoznamu a existuje aj 2. prvok
					
					//printf("som na 1. ale je aj 2. prvok\n");
					*z = pom->dalsi;			// prestav smernik zaciatku na 2. prvok
				    free((void*)pom); 			// odstránenie prvku   
					pom = *z;						
					pred = NULL;
					n++;						// pocet vymazanych prvkov
				}

				if ((pom == *k) && (*k != *z))												// tento OK !
				{
					// som na konci zoznamu - posledny prvok a posledny nie je aj 1.
					
					//printf("som na poslednom prvku a ten nie je zaroven 1. \n");
					pred->dalsi = NULL;			// predchadzajuci prvok dalsi nastav na NULL
					*k = pred;
				    free((void*)pom); 			// odstránenie prvku   
					pom = *k;
					n++;						// pocet vymazanych prvkov
					break; 						// som na konci - vyskoc
				}
				
				if((pom->dalsi != (*z)->dalsi) && (pom->dalsi != (*k)->dalsi))				// teno OK
				{
					// nie je na 1. prvku ani na poslednom prvku
					
					//printf("som niekde v strede\n");
					pred->dalsi = pom->dalsi;	// predchadzajuci prvok pred bude ukazovat na nasledujuci po aktualnom pom	
				    free((void*)pom); 			// odstránenie prvku   
					n++;
					pom = pred->dalsi;			// pom bude ukazovat na dalsi prvok
					//printf("4-skoncene\n");
				}
			}
			else		// ak nenasiel zadany retazec v znacke chod dalej na dalsi prvok
			{
				if(pom->dalsi != NULL)		// ak nie je uz na konci  
				{
					pred = pom;
					pred->dalsi = pom->dalsi;
					pom = pom->dalsi;
				}
				else break;			// inak vyskoc
			}
		}
				
		printf("Vymazalo sa %d zaznamov\n",n);
	}
	
  getch();   // caka na stlacenie lubovolnej klavesy 
}



//-----------------------------------------------------------------------


void pridaj(Tauta **z, Tauta **k) 
{

	char meno[200];				// pomocna premenna pre nacitanie znakov zo vstupu
	int znak, i, riad, j, dlz;	
	Tauta *pred, *novy; 
	

	if (*z != NULL)				// ak bol zoznam nacitany zo suboru
	{
		printf("pridat na poziciu: ");		// vstup pozicie
		scanf("%d", &i) ;
		
		novy = (Tauta *)malloc(sizeof(Tauta));
		
		if(i <= 1)			// --- pridat na poziciu 1 --- zadal 1 alebo mensie cislo
		{			
			novy->dalsi = *z;		// novy prvok bude ukazovat na doterajsi prvy prvok co bol zaciatok zoznamu
			*z = novy;			   	// smernik na zaciatok zoznamu bude ukazovat na novy prvok      
			pred = *z;
		}
		else				// --- pridat na poziciu vyssiu ako 1 alebo na koniec ---
		{
			j = 1;  			// zacnem hladat poziciu od 1
			pred = *z;			// pomocny smernik nastav na zaciatok zoznamu na 1. prvok
			
			while((pred->dalsi != NULL) && (j != (i-1)))	// najdem pedchadzajuci prvok ako zadany alebo posledny   
			{
				pred = pred->dalsi;
				j++;
			}
			printf("som na %d zazname\n",j);			 	// pomocny vypis 

			// napr. ak bola zadana 2 , novy prvok ma byt v poradi 2.,  1. prvok ukazuje na terajsi 2. prvok, ktory ale bude 3. prvkom
			// smernik pred je na 1. prvku ak bola zadana 2
			
			if(pred->dalsi != NULL) 	// novy prvok nebude posledny prvok zoznamu
			{
				novy->dalsi = pred->dalsi;			// novy prvok bude ukazovat na terajsi 2. , na ten teraz ukazuje 1. prvok  
				pred->dalsi = novy;					// 1. prvok bude ukazovat na novy prvok, ktory bude 2.
				pred = pred->dalsi;					// smernik pred nastavim na novy prvok
			}
			else						// novy prvok bude posledny prvok zoznamu
			{
				novy->dalsi = NULL;					// novy bude posledny takze bude ukazovat na NULL
				pred->dalsi = novy;					// posledny prvok bol NULL , teraz bude ukazovat na novy
				(*k) = novy;						// smernik k (koniec zoznamu) treba nastavit aby ukazoval na novy prvok, ktory bude posledny
			}
		}

	}


	if (*z == NULL)				// ak NEbol este zoznam nacitany zo suboru
	{
		novy = (Tauta *)malloc(sizeof(Tauta));
		
		novy->dalsi = NULL;			// novy bude prvy aj posledny takze bude ukazovat na NULL
		*z = novy;
		*k = novy; 
	}
	
	// --- zadat nove udaje ----
	
	printf("kategoria: ");
	fflush(stdin);
	fgets(meno,49,stdin);
	dlz = strlen(meno);
	dlz--;  					// odstranime '\n' ktore sa tam zo vstupu dostava tym ze ho nahradime \0
	meno[dlz] = '\0';
	strcpy(novy->kategoria, meno);
	
	printf("znacka: ");
	fflush(stdin);
	fgets(meno,49,stdin);		// nacita aj prazdne znaky , pocet max 49, nie zo suboru ale zo stdin bude citat (klavesnica)
	dlz = strlen(meno);
	dlz--;  					// odstranime '\n' ktore sa tam zo vstupu dostava tym ze ho nahradime \0
	meno[dlz] = '\0';
	strcpy(novy->znacka, meno);
	
	printf("predajca: ");
	fflush(stdin);
	fgets(meno,99,stdin);
	dlz = strlen(meno);
	dlz--;
	meno[dlz] = '\0';
	strcpy(novy->predajca, meno);
	
	printf("cena: ");		
	fflush(stdin);
	scanf("%8s", meno);
	novy->cena = atoi(meno); 
	
	printf("rok vyroby: ");
	fflush(stdin);
	scanf("%4s",meno);
	novy->rok_vyroby = atoi(meno);

	printf("stav vozidla: ");
	fflush(stdin);
	fgets(meno,199,stdin);
	dlz = strlen(meno);
	dlz--;
	meno[dlz] = '\0';
	strcpy(novy->stav_vozidla, meno);
		
	
  getch();   // caka na stlacenie lubovolnej klavesy 	
}


//-----------------------------------------------------------------------

void nacitaj(FILE *fr, Tauta **z, Tauta **k)
{
	char meno[200];
	int znak, i, riad, j, porcislo, dlz, n; 
	Tauta *p; 
	 
	// ------- otvaranie suboru -------
	
	if ((fr = fopen("auta.txt","r")) == NULL)		// testovanie otvorenia suboru
	{
		printf ("Zaznamy neboli nacitane\n"); 		// vypise ak sa subor nepodarilo otvorit
	}	
	else 
	{
		// ------- dealokacia zoznamu -------
		
		if (*z != NULL)		 // *z ukazuje na prvy prvok v zozname, zoznam nie je prazdny - vynuluj - dealokacia zoznamu
		{
			j=1;
			while  (*z != NULL) 
			{
				//printf("zacinam uvolnovat Tauta");		// pomocny vypis
		    	p = *z;
		    	//printf(" %d\n",j);						// pomocny vypis
		    	(*z) = (*z)->dalsi;
		    	free((void*)p);
		    	p = NULL;
		    	if (*z == NULL) break;   			// ak je uz posledny prvok v zozname Tauta
			}
			*k = *z;    		// ukazovatele k, z nastavíme na NULL 
			n = 0;
		}
				
		// ------- alokacia pamate pre zoznam -------
				
		*z = (Tauta *)malloc(sizeof(Tauta));		// alokuj pamat pre pridanie prvého prvku do prázdneho zoznamu 
		if (*z == NULL)
		{
			printf("Nepodarilo sa alokovat pamat pre Tauta\n");
			fclose(fr);
			exit;			
		}
		(*z)->dalsi = NULL; 		// nastav poiner na dalsi prvok na NULL pri prvom prvku Tauta
		
		p = *z;
		*k = *z;  			// smeriky nastav k koniec = z zaciatok pri 1. prvku Tauta


		// ------------ citanie zo suboru ------------
		
		i = 0; riad = 0; porcislo = 0; n = 0;			
		
		// --- 1. 5. a 6. riadok musim previest na int , ostatne riadky 2. 3. 4. a 7. budu retazce ---
		
		while(znak != EOF)
		{
			do
			{
				znak = fgetc(fr) ;
				if (znak == EOF) break;
				if (znak == '$') 				// novy zaznam v subore
				{
					n = n+1; 					// pocita zaznamy v subore
					riad = 0;					// nastav riadkovanie na zaciatok pre novy zaznam
					porcislo = porcislo+1;		// nastav poradove cislo zaznamu 
				}
				
				if (znak == '\n')				// novy riadok v zazname suboru
				{
					meno[i] = '\0';   			// ukonci pole znakov ako retazec
					i=0;						// vynuluj i na zaciatok retazca - budem nacitavat znaky pre novy riadok
					riad = riad+1;				// zvys pocitadlo riadkov o 1
					
					//printf("riadok %d meno: %s\n", riad, meno); 	// pomocny vypis na test  

					dlz = strlen(meno);			// zisti dlzku retazca v premennej meno

					if(porcislo == 1) 			// ak ide o prvy zaznam v subore uz mam alokovany 1. prvok zoznamu 
					{
						// zapisuj do 1. prvku Tauta
						switch(riad)
						{
						case 1:  break;
						case 2: {strcpy(p->kategoria, meno); break;}
						case 3: {strcpy(p->znacka, meno); break;}
						case 4: {strcpy(p->predajca, meno); break;}
						case 5: {p->cena = atoi(meno); break;}
						case 6: {p->rok_vyroby = atoi(meno); break;}
						case 7: {strcpy(p->stav_vozidla, meno); break;}
						default: break;
						}
					}
					else			// dalsie zaznamy v subore - treba alokovat miesto pre novy prvok v zozname
					{
						switch(riad)  
						{
						case 1: 
						{							
							p = (Tauta *)malloc(sizeof(Tauta));	// alokuj pamat pre dalsi prvok Tauta
							p->dalsi = NULL;					// v pridanom prvku zoznamu nastav smernik na dalsi prvok = NULL
						    (*k)->dalsi = p;  					// nastav smernik k->dalsi , ktory je NULL aby ukazoval na novy prvok zoznamu, ktory bude teraz posledny
						    (*k) = p;							// nastav smernik k na novy prvok (posledny) zoznamu
							break;
						}
						case 2: {strcpy(p->kategoria, meno); break;}
						case 3: {strcpy(p->znacka, meno); break;}
						case 4: {strcpy(p->predajca, meno); break;}
						case 5: {p->cena = atoi(meno); break;}
						case 6: {p->rok_vyroby = atoi(meno); break;}
						case 7: {strcpy(p->stav_vozidla, meno); break;}
						default: break;
						}
					}
				}
				
				if ((znak != EOF) && (znak != '\0') && (znak != '$') && (znak != '\n'))		// ak nie je riadiaci znak tak zapis znak do premennej meno 
				{
					meno[i] = znak; 
					i++;             	// posun sa na dalsie miesto v premennej meno kde sa zapise nasledujuci znak
				}

			} while(znak != '\n');
			
		};
		
		printf ("Nacitalo sa %d zaznamov\n", n);	//vypise pocet nacitanych zaznamov		
	}
	
  if (fr != NULL) fclose(fr);	// zavri subor ak bol otvoreny
	
  getch();		// caka na stlacenie lubovolnej klavesy 
}


//-----------------------------------------------------------------------

void vypis(Tauta *z)
{
	int i = 1;
	
	if (z != NULL)	
	{
 		while(z != NULL)
 		{
 			printf("%d.\n", i);
 			printf("kategoria: %s\n", z->kategoria);
 			printf("znacka: %s\n", z->znacka);
 			printf("predajca: %s\n", z->predajca);
 			printf("cena: %d\n", z->cena);
 			printf("rok vyroby: %d\n", z->rok_vyroby);
 			printf("stav vozidla: %s\n", z->stav_vozidla);
 			z = z->dalsi;
 			i++;
 		}
	}
	
  getch();		// caka na stlacenie lubovolnej klavesy 	
}


