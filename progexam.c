#include "mylib.h"


//rights reserved Bocchini Fabio && Luchini Chiara 


int main()
{
	char sScelta[1];
	int nScelta;
	
	system("clear");
	
	printf("Tanto tempo fa, in una galassia lontana lontana... \n\nIn un mondo parallelo e fantastico, il Mago Oberon \"Calzino Bucato\" deve attraversare a piedi un percorso denso di insidie per poter arrivare finalmente a casa, nella sua torre magica, dove rilassarsi con un bel bicchiere di ippocrasso. \nIn questo gioco ideerete e creerete il percorso che poi dovrete affrontare nei panni del mago Oberon affrontando mostri feroci e raccogliendo tesori\n\n");
	printf("Premi un tasto per continuare\n");
	
	getchar();
	
	do{
		system("clear");
		
		printf("Benvenuto in 	Ippocrasso's Mighty Quest\n");	
		printf("Menù:\n\n");
		printf("1 -> Crea percorso\n");
		printf("2 -> Muovi Oberon\n");
		printf("3 -> Termina gioco\n\n");
		printf("Inserisci il numero corrispondente per scegliere un'opzione: ");
		scanf("%s", sScelta);
		
		nScelta = atoi(sScelta);
			
		switch(nScelta)
		{
			case 1:
				crea_percorso();
				break;
				
			case 2:
				muovi_Oberon();
				break; 
				
			case 3:
				break;
			
			default: 
				printf ("\nErrore! Opzione del menù incorretta\n");
				while(getchar()!='\n');
				getchar();
		}
		
	} while(nScelta !=3);
	
	termina_gioco();
		
	return 0;
}
