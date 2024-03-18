#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>


typedef struct Masina Masina;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Masina {
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
	Nod* prev;
};

struct LDI {
	Nod* prim;
	Nod* ultim;
};

void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void inserareLaInceput(Masina masina, LDI* ldi) {
	//avem nevoie de inf utila si de lista unde inseram - ca parametri; transmiterea prin adresa
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = NULL;
	nou->next = ldi->prim;
	if (ldi->prim) {
		//daca avem cel putin 1 nod in lista, avem codul urmator
		ldi->prim->prev = nou;
		ldi->prim = nou;
	}
	else {
		//daca nu avem noduri in lista
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void inserareLaFinal(Masina masina, LDI* ldi) {
	//avem nevoie de inf utila si de lista unde inseram - ca parametri; transmiterea prin adresa
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->prev = ldi->ultim;
	nou->next = NULL;
	if (ldi->ultim) {
		//daca avem cel putin 1 nod in lista, avem codul urmator
		ldi->ultim->next = nou; //next de ultim va fi nou
		ldi->ultim = nou;
	}
	else {
		//daca nu avem noduri in lista
		ldi->ultim = nou;
		ldi->prim = nou;
	}
}

void traversareLista(LDI lista, int* nrMasini) {//prin valoare, prin pointer
	while (lista.prim) {
		afisareMasina(lista.prim->inf);
		(*nrMasini)++;
		lista.prim = lista.prim->next;
	}

}

void traversareListaFinal(LDI lista) {//prin valoare
	while (lista.ultim) {
		afisareMasina(lista.ultim->inf);
		lista.ultim = lista.ultim->prev;
	}

}

void dezalocare(LDI* lista)
{
	Nod* copie = lista->prim;
	while (copie) {//cat timp copie diferit de NULL
		free(copie->inf.producator);//stergem informatia utila
		copie = copie->next;
		if (copie) {//daca copie e diferit de NULL
			free(copie->prev);
		}
	}
	free(lista->ultim);
	lista->prim = lista->ultim = NULL; //actualizam prim si ultim
}
//TEMA:refacem fct de dezalocare cand lista e transmisa prin valoare
//vom face return de noua structura/noua lista actualizata
//sa folosim REALLOC ca sa realocam la fiecare iteratie

//conversie lista-vector
//prima data numaram masinile
//definim un vect de masini, alocam memorie, parcurgem lista si luam 
//fiecare masina de pe iteratia curenta si o salvam in vectorul nostru

//lista circulara - pornim de la primul nod si ne oprim la primul nod
//parcurg lista pana la ultimul nod si apoi ultimul de next = cap

void conversieLaVector(LDI lista, Masina** vectorMasini) {
	int nrMasini = 0;//initializam contorul local
	while (lista.prim) {
		(*vectorMasini)[nrMasini] = initMasina(lista.prim->inf.producator, lista.prim->inf.serie); //dereferentiere
		nrMasini++;
		lista.prim = lista.prim->next;//la fiecare iteratie preluam informatia din lista si o punem in vector
	}
}

void traversareListaCirculara(LDI lista) {
	//declaram un auxiliar care pointeaza catre prim
	Nod* aux = lista.prim; 
	while(aux->next!=lista.prim) {
		afisareMasina(aux->inf);
		aux = aux->next;
	}
	afisareMasina(aux->inf);
}

void traversareListaCirculara(LDI lista) {
	//declaram un auxiliar care pointeaza catre prim
	Nod* aux = lista.prim;
	do {
		afisareMasina(aux->inf);//afisam inf utila din prim
		aux = aux->next; //ne deplasam catre urmatorul
	} while (aux != lista.prim); //aux este dif de lista de prim?
}

void main() {
	//intai declaram o lista goala apoi inseram masini
	LDI lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	//apelul:
	inserareLaInceput(initMasina("Ford", 1234), &lista); //am transmis prin referinta deci avem adresa listei
	inserareLaInceput(initMasina("Toyota", 5678), &lista);
	inserareLaInceput(initMasina("Renault", 9101), &lista);
	inserareLaFinal(initMasina("BMW", 1112), &lista);
	
	int nrMasini = 0;
	traversareLista(lista, &nrMasini);
	Masina* vectorMasini = (Masina*)malloc(sizeof(Masina) * nrMasini);//CAST LA MASINA*
	conversieLaVector(lista, &vectorMasini);
	printf("\n\n Afisare masini din vector: ");
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(vectorMasini[i]);
		free(vectorMasini[i].producator);
	}
	free(vectorMasini);

	lista.ultim->next = lista.prim;
	lista.prim->prev = lista.ultim;
	traversareListaCirculara(lista);//transmite prin valoare


	//dezalocare(&lista);

}
//cautari pe lista dublu inlantuita circulara