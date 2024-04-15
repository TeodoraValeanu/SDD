#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Prajitura Prajitura;
typedef struct MaxHeap MaxHeap;

struct Prajitura {
	int prioritate;
	char* denumire;
	float pret;
};

struct MaxHeap {
	//contine vectorul+dimensiune
	int dimensiune;
	Prajitura* vector;
};

void afisarePrajitura(Prajitura prajitura) {
	printf("\n %d. Prajitura %s costa %f lei.",
		prajitura.prioritate, prajitura.denumire, prajitura.pret);
}

Prajitura initPrajitura(int prioritate, char* denumire, float pret) {
	Prajitura prajitura;
	prajitura.pret = pret;
	prajitura.prioritate = prioritate;
	prajitura.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(prajitura.denumire, denumire);

	return prajitura;
}

void afisareMaxHeap(MaxHeap maxHeap) {
	for (int i = 0; i < maxHeap.dimensiune; i++) {
		afisarePrajitura(maxHeap.vector[i]);
	}
}


void filtrare(MaxHeap maxHeap, int index) {
	//intai verificam daca vectorul nu e gol
	if (maxHeap.dimensiune > 0) {
		int pozSt = 2 * index + 1;
		int pozDr = 2 * index + 2;
		int pozMax = index;//initial va fi egal cu insusi parintele
		if (pozSt < maxHeap.dimensiune && maxHeap.vector[pozMax].prioritate < maxHeap.vector[pozSt].prioritate)
		{
			pozMax = pozSt;
		}

		if (pozDr < maxHeap.dimensiune && maxHeap.vector[pozMax].prioritate < maxHeap.vector[pozDr].prioritate)
		{
			pozMax = pozDr;
		}

		if (pozMax != index) {
			//facem interschimbare - vector de poz max cu vector de poz min
			Prajitura aux = maxHeap.vector[pozMax];
			maxHeap.vector[pozMax] = maxHeap.vector[index];
			maxHeap.vector[index] = aux;
			if (pozMax <= maxHeap.dimensiune / 2 - 1) {
				//daca pozitia maxima se afla in partea stanga a vectorului
				filtrare(maxHeap, pozMax);
			}
		}
	}
}

void extragere(MaxHeap* maxHeap, Prajitura* prajitura) {
	//alocam dimens
	//facem  deref pt ca e transmis prin pointer
	*prajitura = initPrajitura(maxHeap->vector[0].prioritate, maxHeap->vector[0].denumire,
		maxHeap->vector[0].pret);//deep copy
	Prajitura aux = maxHeap->vector[0];
	maxHeap->vector[0] = maxHeap->vector[maxHeap->dimensiune - 1];
	maxHeap->vector[maxHeap->dimensiune - 1] = aux;
	maxHeap->dimensiune--;
	filtrare(*maxHeap, 0);
}

void main() {
	MaxHeap maxHeap;
	maxHeap.dimensiune = 6;
	maxHeap.vector = (Prajitura*)malloc(sizeof(Prajitura) * maxHeap.dimensiune);
	maxHeap.vector[0] = initPrajitura(10, "Profiterol", 20);
	maxHeap.vector[1] = initPrajitura(11, "Amandina", 21.5);
	maxHeap.vector[2] = initPrajitura(15, "Cheesecake", 14);
	maxHeap.vector[3] = initPrajitura(17, "Ecler", 17);
	maxHeap.vector[4] = initPrajitura(20, "Lavacake", 30);
	maxHeap.vector[5] = initPrajitura(12, "Negresa", 23);

	afisareMaxHeap(maxHeap);

	for (int i = maxHeap.dimensiune / 2 - 1; i >= 0; i--) {
		filtrare(maxHeap, i);
	}
	printf("\n");
	afisareMaxHeap(maxHeap);

	printf("\n");
	Prajitura prajitura;
	while (maxHeap.dimensiune != 0) {
		extragere(&maxHeap, &prajitura);
		afisarePrajitura(prajitura);
		free(prajitura.denumire);
	}

	printf("\n\n Prajiturile ordonate crescator dupa prioritate:");//heap
	for (int i = 0; i < 6; i++) {
		afisarePrajitura(maxHeap.vector[i]);
		free(maxHeap.vector[i].denumire);
	}

	free(maxHeap.vector);
}