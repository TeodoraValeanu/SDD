#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Prajitura Prajitura;
typedef struct Nod Nod;

struct Prajitura {
	int id;
	char* denumire;
	float pret;
};

struct Nod {
	Prajitura prajitura; //inf utila
	Nod* copilStanga;
	Nod* copilDreapta;
};

void afisarePrajitura(Prajitura prajitura) {
	printf("\n %d. Prajitura %s costa %f lei.", prajitura.id, prajitura.denumire, prajitura.pret);
}

Prajitura initPrajitura(int id, char* denumire, float pret) {
	Prajitura prajitura;
	prajitura.pret = pret;
	prajitura.id = id;
	prajitura.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(prajitura.denumire, denumire);

	return prajitura;
}

//parametri = ce inseram,  unde inseram - Nod* transmisa prin valoare/ Nod** ca o si actualizam - idem capul listei
void inserareInArbore(Prajitura prajitura, Nod** radacina ) {
	//daca radacina e null - nu avem niciun nod, deci nodul introdus va fi radacina
	if (*radacina == NULL) {
		//daca e null, facem prima inserare
		//intai alocam nod nou cu cast la tipul de data
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->prajitura = prajitura; //asta e inf utila
		nou->copilStanga = NULL;
		nou->copilDreapta = NULL;
		*radacina = nou; //acum trebuie ca radacina sa pointeze catre nou
	}
	//acum verif daca id-ul ce urmeaza introdus e mai mic sau mai mare decat radacina
	else if (prajitura.id < (*radacina)->prajitura.id) {
		//acum apelam recursiv
		inserareInArbore(prajitura, &(*radacina)->copilStanga); //deoarece copilStanga e Nod*, adaugam & pt ca e adresa

	}
	else {
		inserareInArbore(prajitura, &(*radacina)->copilDreapta);
	}

}

void parcurgereInordine(Nod* radacina) {
	if (radacina != NULL) {
		parcurgereInordine(radacina->copilStanga);
		afisarePrajitura(radacina->prajitura);//inf utila
		parcurgereInordine(radacina->copilDreapta);
	}
}

void parcurgerePostordine(Nod* radacina) {
	if (radacina != NULL) {
		parcurgerePostordine(radacina->copilStanga);
		parcurgerePostordine(radacina->copilDreapta);
		afisarePrajitura(radacina->prajitura);//inf utila
	}
}

Prajitura cautarePrajitura(int id, Nod* radacina) { //returneaza o Prajitura
	if (!radacina) {//daca rad e null
		return initPrajitura(-1, "Neinitializat", 0.0f);
	}
	else if (radacina->prajitura.id == id) {
		//daca id-ul este cel cautat, returnam cu deep copy 
		return initPrajitura(radacina->prajitura.id, radacina->prajitura.denumire, radacina->prajitura.pret);
	}
	else if (id < radacina->prajitura.id) {
		//daca id-ul este mai mic facem cautare pe stanga (apel recursiv pe stg)
		return cautarePrajitura(id, radacina->copilStanga);
	}
	else {
		return cautarePrajitura(id, radacina->copilDreapta);
	}
}

void dezalocare(Nod** radacina) {
	if (*radacina) {//daca e dif de null
		dezalocare(&(*radacina)->copilStanga); //adresa  pt ca avem Nod**
		dezalocare(&(*radacina)->copilDreapta);
		free((*radacina)->prajitura.denumire);
		free(*radacina);
	}
	
}


void main() {
	//intai declaram o radacina, pornim de la NULL ca la capul listei
	Nod* radacina = NULL;
	inserareInArbore(initPrajitura(5, "Profiterol", 20), &radacina);
	inserareInArbore(initPrajitura(2, "Amandina", 21.5), &radacina);
	inserareInArbore(initPrajitura(7, "Cheesecake", 14), &radacina);
	inserareInArbore(initPrajitura(4, "Ecler", 19), &radacina);
	inserareInArbore(initPrajitura(8, "LavaCake", 16), &radacina);
	inserareInArbore(initPrajitura(6, "Negresa", 30), &radacina);

	printf("\n Parcurgere inordine:");
	parcurgereInordine(radacina);
	printf("\n\n Parcurgere postordine:");
	parcurgerePostordine(radacina);

	Prajitura prajituraCautata = cautarePrajitura(6, radacina); //cautam praj cu id 6
	printf("\n\n Prajitura cautata este:");
	afisarePrajitura(prajituraCautata);
	free(prajituraCautata.denumire); //evitam memory leak
	dezalocare(&radacina);

	printf("\n\n");
}