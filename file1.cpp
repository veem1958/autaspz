
#include "stdio.h"

int main()
{
	
	FILE *fr;
	char znak, z;        // alebo aj int
	int riadok = 1;
	int pozicia = 1;
	
	printf("Zadaj znak na vyhladanie: ");
	scanf("%c", &znak);
	
	if((fr = fopen("pozicia.txt", "rt")) == NULL) 
	{
		printf("Subor sa nepodarilo otvorit.\n");
		return -1;
	}
	
	//printf("\nZadany znak je : %c \n", znak);       // nemusi toto byt - len na kontrolu
	
	do
	{
		z = fgetc(fr);
		
		//if (pozicia >= 1 && pozicia < 4) printf("znak na %d riadku a %d pozicii je : %c \n", riadok, pozicia, z);     //toto len na kontrolu bolo
		
		if (z == znak) 
		{		
		   break;       // zhoda tak vyskoc
		}

		if (z == '\n') 
		{
			riadok++;
			pozicia = 1;
			//fr++;         // netreba fr++ lebo fgetc automaticky posúva smernik ---- test
		}

		if ((z != znak) && (z != '\n')) 
		{
			//fr++;         // netreba
			pozicia++;
		}
		
	} 
	while (z != EOF);
	
	if (z == EOF)
	{
		printf("Znak sa v subore nenasiel !");
	}
	else
	{	
		printf("Znak je v subore na %d riadku a pozicii %d ", riadok, pozicia );
	}

	fclose(fr);    // zavri subor
	return 0;
}
