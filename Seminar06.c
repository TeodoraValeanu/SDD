#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>


typedef struct Masina Masina;
typedef struct Nod Nod;

struct Masina {
	long id;
	char* producator;
	int serie;
};

struct Nod {
	Masina inf;
	Nod* next;
};

void afisareMasina(Masina masina) {
	printf("\n&ld. Masina %s are seria %d.", masina.id, masina.producator, masina.serie);
}

Masina initMasina(long id, const char* producator, int serie) {
	Masina masinaNoua;
	masinaNoua.id = id;
	masinaNoua.serie = serie;
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

void push(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = *cap;
	*cap = nou;
}

void put(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;
	nou->next = NULL;
	if ((*cap) != NULL) {
		Nod* aux = *cap;
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else {
		*cap = nou;
	}
}

Masina pop(Nod** varf) {
	Masina masina;
	masina.id = -1; //in cazul in care nu am ce sa scot, sa am niste valori predef
	masina.serie = -1;
	masina.producator = NULL;
	if (*varf) {
		masina = (*varf)->inf;
		//vreau sa ma mut cu varful pe urm nod
		//pot sa pastrez legatura cu informatia utila
		//dezalocarea pt inf utila NU SE FACE IN FUNCTIA POP = PIERDEM PRODUCATORUL
		//IN SCHIMB, PUTEM DEZALOCA NODUL
		Nod* temp = *varf;
		(*varf) = (*varf)->next;
		free(temp);
	}

	return masina;
}

Masina cautareDupaId(Nod** stiva, long id) {
	Masina masina;
	masina.id = -1; 
	masina.serie = -1;
	masina.producator = NULL;
	Nod* stivaAux = NULL;
	while ((*stiva)!= NULL && (*stiva)->inf.id != id) {
		push(&stivaAux, pop(stiva));
	}

	if (*stiva) {
		masina = pop(stiva);
	}

	while (stivaAux != NULL) {
		push(stiva, pop(&stivaAux));
	}

	return masina;
}

void main() {
	
	Nod* coada = NULL;
	Nod* stiva = NULL;

	Masina masina;
	push(&stiva, initMasina(1, "Renault", 1234));
	push(&stiva, initMasina(2, "Ford", 5678));
	push(&stiva, initMasina(3, "Ford", 5679));
	push(&stiva, initMasina(4, "Ford", 5677));
	push(&stiva, initMasina(5, "Peugeot", 9101));
	push(&stiva, initMasina(6, "Bmw", 1213));
	printf("\n Coada:");

	Masina masina;
	put(&coada, initMasina(1, "Renault", 1234));
	put(&coada, initMasina(2, "Ford", 5678));
	put(&coada, initMasina(3, "Ford", 5679));
	put(&coada, initMasina(4, "Ford", 5677));
	put(&coada, initMasina(5, "Peugeot", 9101));
	put(&coada, initMasina(6, "Bmw", 1213));
	printf("\n Coada:");

	Masina masinaCautata = cautareDupaId(&stiva, 3);
	afisareMasina(masinaCautata);
	free(masinaCautata.producator);

	while (stiva) {
	masina = pop(&stiva);//e  transmis prin adresa - dam adresa stivei
	afisareMasina(masina);
		free(masina.producator);
			
	}

	while (coada) {
		masina = pop(&coada);//e  transmis prin adresa - dam adresa stivei
		afisareMasina(masina);
		free(masina.producator);


}