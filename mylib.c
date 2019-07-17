#include "mylib.h"

static struct Terra* percorso = NULL;
static struct Terra* ultima_terra = NULL;
static struct Terra* counter = NULL;
static struct Terra* stampa_terra = NULL;
static struct Terra* terra_corrente = NULL;
static struct Terra* terra_distrutta = NULL;
static struct Oberon oberon;

//funzioni per crea_percorso
static void ins_terra();
static void canc_terra();
static void stampa_percorso();
static void chiudi_percorso();

//funzioni per muovi_oberon
static void avanza();
static void prendi_tesoro();
static void usa_pozione();
static void combatti();
static void distruggi_terra();
static void gameOver();

int mostroErrato=0;
int percorsoChiuso=0; 
int numeroTerre=0; 
int distruggiTerra=1;
int giocoFinito=0;
int nTerra;	
int nMostro;
short nTesoro;

int arrayMostro[5] = {0,2,1,3,5};
char nomeMostro[5][10] = {"nessuno","scheletro","lupo","orco","drago"};
char nomeTerra[5][10]= {"deserto","foresta","palude","villaggio","pianura"};

void crea_percorso()
{
	char sCrea[1];
	int nCrea;
	
	do{
		system("clear");
		printf("Menù Creazione percorso\n\n");
		printf("1 -> Inserisci una nuova terra\n");
		printf("2 -> Cancella l'ultima terra inserita\n");
		printf("3 -> Stampa l'intero percorso\n");
		printf("4 -> Chiudi il percorso\n\n");
		printf("Inserisci il numero corrispondente per scegliere un'opzione: ");
		scanf("%s",sCrea);
		
		nCrea = atoi(sCrea);
		
		switch (nCrea)
		{
			case 1:
				ins_terra();
				break;
			
			case 2:
				canc_terra();
				break;
				
			case 3:
				stampa_percorso();
				break;
			
			case 4:
				chiudi_percorso();
				break;
			
			default:
				printf("Errore! Opzione del menù incorretta");
				while(getchar()!='\n');
				getchar();
		};
	}while (nCrea!=4);
}		

void muovi_Oberon()
{
	char sMuovi[1];
	int nMuovi;
	
	terra_corrente = percorso;
	
	oberon.borsa_oro=10;
	oberon.punti_ferita=5;
	oberon.incantesimi=2;
	oberon.pozione_guaritrice=1;
	
	if(!percorsoChiuso)
	{
		printf("Impossibile iniziare a muovere Oberon, il percorso non è stato chiuso\n");
		while(getchar()!='\n');
		getchar();
	}else
	{
		do
		{
			system("clear");
			printf("\nPF: %hu                   Incantesimi: %hu\n",oberon.punti_ferita , oberon.incantesimi);
			printf("\nOro: %hu/500             Pozioni: %hu\n",oberon.borsa_oro , oberon.pozione_guaritrice);
			
			printf("\nTerra: %s          Mostro: %s      Tesoro presente: %hu\n",nomeTerra[terra_corrente->tipo_terra], nomeMostro[terra_corrente->tipo_mostro],terra_corrente->tesoro);
			
			printf("\nCosa vuoi fare?\n");
			printf("1 -> Avanza\n");
			printf("2 -> Prendi il tesoro\n");
			printf("3 -> Usa la pozione\n");
			printf("4 -> Combatti\n");
			printf("5 -> Distruggi la terra\n");
			printf("Inserisci il numero corrispondente per scegliere un'opzione: ");
			scanf("%s",sMuovi);
			
			nMuovi = atoi(sMuovi);
				
			switch(nMuovi)
			{
				case 1:
					avanza();
					break;
				
				case 2:
					prendi_tesoro();
					break;
				
				case 3:
					usa_pozione();
					break;
					
				case 4:
					combatti();
					break;
				
				case 5:
					distruggi_terra();
					break;
				
				default:
					printf("Errore! Opzione del menù incorretta");
					while(getchar()!='\n');
					getchar();
			}
		}while(giocoFinito==0);
	}
}

void ins_terra()
{	
	if(!numeroTerre)
	{
		percorso = malloc (sizeof (struct Terra));
		ultima_terra = percorso;
		numeroTerre++;
	}else
	{
		ultima_terra->terra_successiva = malloc (sizeof (struct Terra));
		ultima_terra = ultima_terra->terra_successiva;
		numeroTerre++;
	}
	do{
		system("clear");
	
		printf("Quale terra vuoi inserire?\n\n");
		printf("1 -> Deserto\n");
		printf("2 -> Foresta\n");
		printf("3 -> Palude\n");
		printf("4 -> Villaggio (non può contenere mostri)\n");
		printf("5 -> Pianura\n");
		printf("Inserisci il numero della terra da inserire\n");
		scanf("%d",&nTerra);
	
		if(nTerra>=1 && nTerra<=5)
		{
			ultima_terra->tipo_terra = nTerra - 1; 
		}else
		{
			printf("Errore, inserisci un'opzione dal menù\n");
			while(getchar()!='\n');
			getchar();
		}
	}while(nTerra<1 || nTerra>5);
		
	do{	
		if(nTerra!=4 && numeroTerre!=1)
		{
			mostroErrato=0;
			
			printf("\nQuale mostro vuoi inserire?\n\n");
			printf("1 -> Nessuno\n");
			printf("2 -> Scheletro (non può essere inserito nella palude)\n");
			printf("3 -> Lupo      (può essere inserito solo nella pianura e nella foresta)\n");
			printf("4 -> Orco      (non può essere inserito nel deserto)\n");
			printf("5 -> Drago\n");
			printf("Inserisci il numero del mostro da inserire\n");
			scanf("%d",&nMostro);
		
			if(nMostro>=1 && nMostro<=5)
			{
				ultima_terra->tipo_mostro = nMostro - 1;
			}else
			{
				printf("Errore, inserisci un'opzione dal menù\n");
				mostroErrato=1;
				
				while(getchar()!='\n');
				getchar();
			}
		}else
		{
	 		printf("Questa Terra non può contenere mostri!\n");
		}
		
		if((nTerra==3 && nMostro==2) || (nTerra==1 && nMostro==4) || (nTerra==(1 || 3 || 4) && nMostro==3))
		{
			printf("Non puoi inserire questo mostro in questa terra!\n");
			mostroErrato=1;
		}	
	}while(mostroErrato==1);

	do{		
		printf("\nQuante monete d'oro vuoi inserire? ");
		scanf("%hu",&nTesoro);
	
		if(nTerra==4 && nTesoro>10)
		{
			printf("Nel villaggio puoi inserire al massimo 10 monete d'oro!\n");
		}else if(nTesoro<0)
		{
			printf("Non puoi inserire un tesoro negativo!\n");
		}else
		{
			ultima_terra->tesoro = nTesoro;
		}
	}while((nTerra==4 && nTesoro>10) || nTesoro<0);
	
	printf ("\nE' stata creata la terra con tipo %s, mostro %s e tesoro %hu\n", nomeTerra[ultima_terra->tipo_terra], nomeMostro[ultima_terra->tipo_mostro], ultima_terra->tesoro);
	while(getchar()!='\n');
	getchar();
}	

void canc_terra()                                                                        
{		                                                                       			 
	if(!numeroTerre)
	{
		printf("Non è stata creata ancora nessuna terra!\n");
	}else if(numeroTerre==1)
	{
		free(percorso);
		percorso=NULL;
		numeroTerre--;
		
		printf("Terra eliminata correttamente\n");
	}else
	{
		counter = percorso;
		
		while(counter->terra_successiva->terra_successiva!=NULL)
		{
			counter = counter->terra_successiva;
		}
		ultima_terra = counter;
		free(ultima_terra->terra_successiva);
		ultima_terra->terra_successiva=NULL;
		numeroTerre--;
		
		printf("Terra eliminata correttamente\n");

	}		
	while(getchar()!='\n');
	getchar();
}

void stampa_percorso()
{
	int nStampa=1;
	
	stampa_terra = percorso;
	
	if (!numeroTerre)
	{
		printf("Non è stata creata ancora nessuna terra!\n");
	}else
	{
		while(stampa_terra != NULL)
		{
			printf("%d° Terra:\n",nStampa);
			printf("Terra:  %s\n",nomeTerra[stampa_terra->tipo_terra]);
			printf("Mostro: %s\n",nomeMostro[stampa_terra->tipo_mostro]);
			printf("Tesoro: %hu\n\n",stampa_terra->tesoro);
			
			stampa_terra = stampa_terra->terra_successiva;
			
			nStampa++;
		}
	}
	printf("Premi un tasto per continuare\n");
	while(getchar()!='\n');
	getchar();
}					

void chiudi_percorso()
{
	if(!numeroTerre)
	{
		printf("\nNon è stata inserita ancora nessuna terra!\n");
	}else if(percorsoChiuso==1)
	{
		printf("\nIl percorso è già stato chiuso\n");
	}else
	{
		percorsoChiuso=1;
		printf("\nIl percorso è stato chiuso correttamente\n");
	}
	while(getchar()!='\n');
	getchar();
}	


void avanza()
{
	if(terra_corrente->terra_successiva==NULL)
	{
		gameOver();
	}else if(terra_corrente->tipo_mostro==4)
	{
		printf("Non puoi avanzare senza aver ucciso il drago!\n");
	}else
	{
		terra_corrente=terra_corrente->terra_successiva;
		printf ("Azione eseguita con successo!\n");
	}	
	while(getchar()!='\n');
	getchar();
}

void prendi_tesoro()                        
{
	if(terra_corrente->tipo_mostro!=0)
	{
		printf("Devi uccidere il mostro prima di poter prendere il tesoro!\n");
	}else if(terra_corrente->tesoro==0)
	{
		printf("Non c'è nessun tesoro da prendere!\n");
	}else
	{
		printf("Hai preso il tesoro!\n");
		oberon.borsa_oro = oberon.borsa_oro + terra_corrente->tesoro;
		terra_corrente->tesoro = 0;
		
		if(oberon.borsa_oro>500)
		{
			printf("La tua borsa non può contenere più di 500 monete d'oro\n");
			oberon.borsa_oro=500;
		}	
	}
	while(getchar()!='\n');
	getchar();
}

void usa_pozione()
{
	if(oberon.punti_ferita==5)
	{
		printf("Non puoi usare la pozione quando hai tutta la vita\n");
	}else if(!oberon.pozione_guaritrice)
	{
		printf("Non hai più la pozione guaritrice\n");
	}else
	{
		printf("Punti ferita recuperati!\n");
		oberon.punti_ferita=5;
		oberon.pozione_guaritrice--;
	}
	while(getchar()!='\n');
	getchar();
}

void combatti()
{
	char sCombatti[1];
	int nCombatti;
	
	int pfMostro = arrayMostro[terra_corrente->tipo_mostro];
	time_t t;

	srand((unsigned) time(&t));
	
	if(terra_corrente->tipo_mostro==0)
	{
		printf("Non ci sono mostri da combattere in questa terra\n");
	}else
	{
		system("clear");
		printf("Vuoi combattere il mostro o usare un incantesimo?\n\n");
		printf("1 -> Combatti\n");
		printf("2 -> Usa un incantesimo\n");
		printf("Cosa vuoi fare?\n");
		scanf("%s",sCombatti);
	
		nCombatti = atoi(sCombatti);
	
		switch(nCombatti)
		{
			case 1:
				do
				{	
					if((rand()%100)>60)
					{
						pfMostro = pfMostro -3;
					}
					if(pfMostro>0 && (rand()%100)>50)
					{ 	
						oberon.punti_ferita = oberon.punti_ferita - arrayMostro[terra_corrente->tipo_mostro];
					}
				}while(pfMostro>0 && oberon.punti_ferita>0);
				
				if (!oberon.punti_ferita)
				{
					printf ("\n\n           GAME OVER!\n");
					gameOver();
				}else
				{
					printf("Hai sconfitto il mostro!\n");
					terra_corrente->tipo_mostro = 0;
				}
				break;
				
			case 2:
				if(!oberon.incantesimi)
				{
					printf("Non hai più incantesimi a disposizione!\n");
				}else
				{
					terra_corrente->tipo_mostro = 0;
					printf("Hai ucciso il mostro usando un incantesimo!\n");
					oberon.incantesimi--;
				}
				break;
				
			default:
				printf("Errore! Opzione del menù incorretta");
		}
	}
	while(getchar()!='\n');
	getchar();
}

void distruggi_terra()
{
	if(terra_corrente->terra_successiva==NULL)
	{
		printf("Non ci sono più terre da poter distruggere!\n");
	}else if (distruggiTerra==0)
	{
		printf("Questo potente incantesimo può essere usato solamente una volta!\n");
	}else
	{
		printf("Hai distrutto una terra grazie ad un potente incantesimo\n");
		
		distruggiTerra=0;
		
		terra_distrutta=terra_corrente->terra_successiva;
	
		terra_corrente->terra_successiva = terra_corrente->terra_successiva->terra_successiva;
	
		free(terra_distrutta);
	}
	while(getchar()!='\n');
	getchar();
} 

void gameOver()
{
	system("clear");
	
	if(oberon.punti_ferita>0)
	{	
		printf("\n\n		COMPLIMENTI SEI ARRIVATO ALLA FINE DEL PERCORSO!\n");
	}else
	{
		printf("\n\n		SEI MORTO\n");
	}	
		printf("\n Hai guadagnato un totale di %hu monete d'oro!\n",oberon.borsa_oro);
		printf("\n\n Premi un tasto qualsiasi per tornare al menù iniziale");
		
		giocoFinito=1;
		
		getchar();
}

void termina_gioco()
{
	while(percorso!=NULL)
	{
		counter=percorso;
		free(percorso);
		percorso=counter->terra_successiva;
	}
}
