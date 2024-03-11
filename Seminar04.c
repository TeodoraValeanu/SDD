#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>

//liste simplu inlantuite
//o functie care afiseaza si initializeaza o masina
//inf utila poate fi preluata

typedef struct Masina Masina;//ca sa nu mai punem struct peste tot la parametri
typedef struct Nod Nod;

struct Masina {
	char* producator;
	int serie;
};

//afisare masina
void afisareMasina(Masina masina) {
	printf("\n Masina %s are seria %d.", masina.producator, masina.serie);
}

//initializare masina
Masina initMasina(const char* producator, int serie) {
	Masina masinaNoua;
	//setam valorile primite ca parametru
	//in cazul valorilor care nu sunt alocate dinamic
	masinaNoua.serie = serie;
	//in cazul valorilor alocate dinamic
	masinaNoua.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy(masinaNoua.producator, producator);

	return masinaNoua;
}

//facem un struct nou care sa contina o Masina (inf utila) + next/adresa urm nod
//o lista este identif prin adresa primului nod/cap
struct Nod {
	Masina inf;
	Nod* next;
};


//inseram la inceputul listei
void inserareLaInceput(Nod** cap, Masina masina) {//nodul capului + inf utila
	//de fiecare data cand inseram - transmitem prin param deci **
	//alocam memorie pt un nod nou
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = masina;//shallow copy/setam inf utila
	nou->next = *cap; //cap este adresa, dar fiindca e transmis prin pointer trb deref
	//actualizam capul listei
	*cap = nou;

}


//functie de traversare
void traversareLista(Nod* cap) {
	while (cap) {
		afisareMasina(cap->inf);
		cap = cap->next;
		//ma deplasez pe urmatorul nod
	}
}

//inserare la final
//ma  deplasez pana la ultimul nod, declar un nod nou, declar noua adresa
//inlocuim adresa ultimului nod(NULL) cu noua adresa
//trebuie sa acoperim  scenariul in care lista este goala - vom modifica adresa primului nod
//daca avem transmitere prin pointer nu putem lua acelasi nod ca sa ne deplasam / pierdem nodurile din stanga
//deci vom lua o copie a nodului

void inserareLaFinal(Nod** cap, Masina masina) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou -> inf = masina;//shallow copy/setam inf utila
	nou -> next = NULL;
	if ((*cap) != NULL) {//daca lista nu e goala
		Nod* aux = *cap;//ne deplasam in interiorul lui while prin el
		while (aux->next) {//cat timp aux diferit de next
			aux = aux->next;//ne deplasam prin noduri
		}
		aux->next = nou;
	}
	else {//daca lista e goala, actualizam capul
		*cap = nou;

	}
}

void dezalocare(Nod** cap) {
	while ((*cap) != NULL) {//daca nu e NULL, trebuie sters
		//mut capul pe urm nod si dezaloc inf utila din el, apoi sterg tot nodul si trec la urmatorul
		Nod* copie = *cap;
		*cap = (*cap)->next;
		free(copie->inf.producator);
		free(copie);
	}
	//se opreste cand capul e NULL deci nu trebuie sa il punem noi NULL
}

int numarAparitiiPeugeot(Nod* cap, char* producator)//transmitem capul prin val pt k nu-l modif
{
	int numar = 0;
	while (cap) {
		if (strcmp(cap->inf.producator, producator) == 0)//comparam inf utila cu un param
		{
			//daca cond e implinita, creste contorul
			numar++;
		}
		cap = cap->next;
	}return numar;
}

void main() {
	Nod* cap = NULL; //avem definita o lista goala
	inserareLaInceput(&cap, initMasina("Renault", 1234));
	inserareLaInceput(&cap, initMasina("Peugeot", 5678));
	inserareLaInceput(&cap, initMasina("Peugeot", 7273));
	inserareLaInceput(&cap, initMasina("Peugeot", 9484));
	inserareLaInceput(&cap, initMasina("Beamer", 9101));
	inserareLaInceput(&cap, initMasina("Chevy", 1213));


	//ne trebuie o functie care sa parcurga/traverseze lista
	//putem lua param transmisi prin valoare - pt ca nu modificam nimic
	//daca vrem sa modificam - luam param trans prin pointeri

	traversareLista(cap);
	//deoarece am transmis prin valoare - nu se modif adresa; se foloseste o copie a parametrului care la final se sterge
	inserareLaFinal(&cap, initMasina("Toyota", 1415));

	traversareLista(cap);

	//dezalocarea listei - la final cap va avea adresa NULL
	dezalocare(&cap);

	//cautam/numaram masinile cu un anume nume
	int nr = numarAparitiiPeugeot(cap, "Peugeot");
	printf("\n Masina Peugeout apare de %d ori", nr);
}

