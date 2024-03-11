#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include<stdlib.h>
#include<string.h>


typedef struct Produs Produs; //nu mai punem struct Produs ci direct Produs

struct Produs {
	float pret;
	int cod;
	char* denumire;

	//vom citi un produs dintr-un fisier, vom afisa produsul la consola

};



void citireVector(const char* numeFisier, int** vector, int* dimensiune) //deoarece vector are deja *, mai punem * - int* e tipul lui, ca sa marcam
//transmiterea prin pointer mai adaugam o *
{	//cand folosim vector si dimens nu uitam dereferentierea pt a extrage valori
	//dereferentiere:
	FILE* streamFisier = NULL; //ne permite sa accesam fisierul
	streamFisier = fopen(numeFisier, "r");
	//validam ca am facut deschiderea corect
	if (streamFisier != NULL) {
		fscanf(streamFisier, "%d", dimensiune); //dimensiune este deja primit ca adresa, nu avem nevoie de dereferentiere
		//alocam spatiu vectorului
		*vector = (int*)malloc(sizeof(int) * (*dimensiune));//pentru a prioritiza avem parantezele; avem nevoie de cast
		//citim element cu element din fisier
		for (int i = 0; i < (*dimensiune); i++)
		{
			fscanf(streamFisier, "%d", (*vector) + i); //sau &(*vector)[i]
		}
	}
	fclose(streamFisier);
}

//definim functia care va citi un produs din fisier
//file* - putem gestiona deschiderea in main
Produs preluareProdusDinFisier(FILE* file) {
	Produs produs;
	if (file != NULL) {
		//declaram un buffer - dimensiune compusa din 3 parti
		//strlen(sir) + "\0" + "\n"
		char buffer[20];
		//facem cast
		fgets(buffer, 10, file); //buffer="7.5\n"
		produs.pret = atof(buffer);

		fgets(buffer, 10, file); //valoarea din buffer este "1\n"
		produs.cod = atoi(buffer);

		//citim ultima linie
		fgets(buffer, 15, file);
		//taiem \n
		char* denumire = strtok(buffer, "\n");
		//alocam memorie
		produs.denumire =(char*) malloc(sizeof(char) * (strlen(denumire) + 1));
		strcpy(produs.denumire, denumire);
	}

	return produs;
}


//daca lasam functia sub main trebuie sa o initializam deasupra lui main
void afisareProdus(Produs produs)
{
	printf("\n Produsul %s are codul %d si pretul %.2f lei.", produs.denumire, produs.cod, produs.pret);

}

void citireProduseDinFisier(FILE* file, Produs** vectorProduse, int* nrProduse) {
	if (file != NULL) {
		while (!feof(file))  //cat timp nu am ajuns la final file end of file(feof), citesc
		{
			*vectorProduse = (Produs*)realloc((*vectorProduse), (1 + (*nrProduse)) * sizeof(Produs)); //pe cine realocam si cu cat
			(*vectorProduse)[*nrProduse] = preluareProdusDinFisier(file); //dereferentiere
			(*nrProduse)++;
			//daca vectorul are un Produs, vrem sa il realocam pentru 1+1 Produse
		}
	}
}

void citireMatriceProduse(Produs*** matriceProduse, int nrLinii, int nrColoane) {
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane; j++)
		{
			printf("Pretul pentru pozitia(%d,%d): ", i, j);
			scanf("%f", &(*matriceProduse)[i][j].pret);//scanf asteapta o adresa

			printf("Codul pentru pozitia(%d,%d): ", i, j);
			scanf("%f", &(*matriceProduse)[i][j].cod);

			printf("Denumirea pentru pozitia(%d,%d): ", i, j);
			(*matriceProduse)[i][j].denumire = (char*)malloc(sizeof(char) * 20);
			scanf("%f", (*matriceProduse)[i][j].denumire);
		}
	}
}

void citireMatriceDeLaTastatura(Produs*** matriceProduse, int* nrLinii, int* nrColoane) {
	printf("\n Nr linii: ");
	scanf("%d", nrLinii); //prin adresa, nrLinii e deja adresa
	printf("\n Nr coloane: ");
	scanf("%d", nrColoane);

	//alocam memorie pt matrice
	*matriceProduse = (Produs**)malloc(sizeof(Produs*) * (*nrLinii));
	for (int i = 0; i < (*nrLinii); i++)
	{
		(*matriceProduse)[i] = (Produs*)malloc(sizeof(Produs) * (*nrColoane));
	}

	citireMatriceProduse(matriceProduse, &nrLinii, &nrColoane );//deja e adresa
}

void afisareMatriceProduse(Produs** matriceProduse, int nrLinii, int nrColoane) {
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane; j++)
		{
			afisareProdus(matriceProduse[i][j]);
		}
	}

}


//vom citi 2 nr intregi dintr-un fisier
//deschidem, citim, inchidem
void main() {
	int val1, val2;
	FILE* streamFisier = NULL;
	//r de la read
	//streamul se initializeaza cu apelul functiei
	//streamFisier = fopen("Fisier.txt", "r");
	//if (streamFisier != NULL) {
	//	fscanf(streamFisier, "%d", &val1); //modificam valoarea de la adresa &val
	//	fscanf(streamFisier, "%d", &val2);
	//	//la fscanf dam intotdeauna adrese, nu valori
	//}

	//fclose(streamFisier);

	//printf("\n Val1 = %d, val2 = %d", val1, val2);

	////citire vector
	//int* vector = NULL;
	//int dimensiune;

	//citireVector("Vector.txt", &vector, &dimensiune);//avem transmitere prin referinta/pointer - deoarece modificam valorile prin citire
	////la afisare - transmitere prin valoare

	////parcurgere vector
	//for (int i = 0; i < dimensiune; i++)
	//{
	//	printf("\n vector[%i]=%d", i, vector[i]);
	//}

	////dezalocam deoarece avem pointer
	//free(vector);

	//apelul functiei
	FILE* file = NULL;
	file = fopen("Produs.txt", "r");
	Produs produs = preluareProdusDinFisier(file);

	afisareProdus(produs);


	//citim un vector de produse

	Produs* vectorProduse = NULL;
	int nrProduse = 0;
	file = NULL;
	file = fopen("Produse.txt", "r");
	
	citireProduseDinFisier(file, &vectorProduse, &nrProduse);

	for (int i = 0; i < nrProduse; i++)
	{
		afisareProdus(vectorProduse[i]);
		free(vectorProduse[i].denumire);
	}

	free(vectorProduse);//evitam memory leaks


	Produs** matriceProduse = NULL; //initializam matricea
	int nrLinii, nrColoane;
	citireMatriceDeLaTastatura(&matriceProduse, &nrLinii, &nrColoane);//transmitere prin adresa - nu avem valori pt ele
	afisareMatriceProduse(matriceProduse, nrLinii, nrColoane);
}
