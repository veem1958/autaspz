
#include "stdio.h"
#include "stdlib.h"

int scitaj(int *a, int *b)
{
	return ((*a)+(*b));
}

int odcitaj(int *p, int *q)
{
	return ((*p)-(*q));
}

int nasob(int *k, int *l)
{
	return ((*k)*(*l));
}

double delenie(int *k, int *l)
{
	if (*l != 0) return ((double)(*k)/(*l));   // osetri delenie 0, tu treba pretypovat aspon 1 na double aby bol vysledok double
	else return -1;
}


int main()
{

	int x,y,z,navrat; char c;
	int *s; double *w;
	
	int *px; int *py;
	int (*pf_o)(int *,int *);           // ukazovatel na funkciu odcitaj ***
	int (*pf_s)(int *,int *);        // ukazovatel na funkciu scitaj
	int (*pf_n)(int *,int *);        // ukazovatel na funkciu nasob
	double (*pf_d)(int *,int *);     // ukazovatel na funkciu delenie

    pf_o = odcitaj;                              // nastav smernik na adresu funkcie
    pf_s = scitaj;                               // nastav smernik na adresu funkcie
    pf_n = nasob;                                // nastav smernik na adresu funkcie
    pf_d = delenie;                              // nastav smernik na adresu funkcie

    if ((s = (int *)malloc(1*sizeof(int))) == NULL) exit(1);         // alokuj pamat velkosti 1*int na vysledok int vrateny do smernika z funkcie scitaj , ak sa neda tak exit
    if ((w = (double *)malloc(1*sizeof(double))) == NULL) exit(1);   // alokuj pamat velkosti 1*double na vysledok double vrateny do smernika z funkcie delenie
    
    printf("zadaj 2 cisla: \n");
    navrat = scanf("%d %d", &x,&y);
    printf("nacital som %d cisel. \n", navrat);

	px = &x;     // nastav smernik px na adresu premennej x
	py = &y;

    printf("vyber volbu: \n");
    printf("s - scitanie \n");
    printf("o - odcitanie \n");
    printf("n - nasobenie \n");
    printf("d - delenie \n");
    printf("e - exit, koniec \n");
       
    printf("zadane cisla : %d %d \n", *px,*py);

do {

    navrat = scanf("%c", &c);         // nacitaj znak
    
    if(c=='s') 
    {	
		*s = (*pf_s)(px,py);
		printf("sucet cisel je : %d\n", *s);
	}
	
	if(c=='o')
	{
		*s = (*pf_o)(px,py);
		printf("rozdiel cisel je : %d \n", *s);
	}
	
	if(c=='n')
	{
		*s = (*pf_n)(px,py);    
		printf("nasobenie cisel je : %d \n", *s);
	}

	if(c=='d')
	{
		*w = (*pf_d)(px,py);    
		printf("delenie cisel je : %lf \n", *w);
	}
	
} while (c != 'e') ;    // pokial nebolo stlacene pismeno e

	free(s);            // uvolni alokovanu pamat pre s
	free(w);
	
	return 0;
}
