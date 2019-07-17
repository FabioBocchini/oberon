#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void crea_percorso();

void muovi_Oberon();

void termina_gioco();

enum Tipo_terra {Deserto,Foresta,Palude,Villaggio,Pianura};

enum Tipo_mostro {Nessuno,Scheletro,Lupo,Orco,Drago};

struct Oberon {
	short borsa_oro;
	short punti_ferita;
	short incantesimi;
	short pozione_guaritrice;
};
	
struct Terra {
	enum Tipo_terra tipo_terra;
	enum Tipo_mostro tipo_mostro;
	short tesoro;
	struct Terra* terra_successiva;
};
