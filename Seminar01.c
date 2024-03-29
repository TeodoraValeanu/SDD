#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>


//functie cu transmiterea param cu valoare - tipul param este acelasi din main
//il folosim cand nu modificam param
void interschimbare(int nr1, int nr2) {
	//dereferentiere
	int aux;
	aux = nr1;
	nr1 = nr2;
	nr2 = aux;
}


//transmitere prin adresa
//cand modificam anumiti param
void interschimbarePrinPointer(int* nr1, int* nr2) {
	//dereferentiere
	int aux;
	aux = *nr1;
	*nr1 = *nr2;
	*nr2 = aux;
}

//tipul din main + steluta= pt ca e transmis prin pointer
//vector si dimens trebuie dereferentiate
void citireDeLaTastatura(int** vector, int* dimensiune) {
	printf("\n Dimensiune: ");
	scanf("%d", dimensiune); //nu punem & pt ca dimensiunea e deja adresa

	*vector = (int*)malloc((*dimensiune) * sizeof(int));

	for (int i = 0; i < (*dimensiune); i++) {
		printf("vector[%i]=", i);
		//scanf asteapta adresa elementelor - de aceea am pus &
		//* arata valoarea, & arata adresa

		scanf("%d", &(*vector)[i]);
		//deplasare folosindu-ne de index
		//scanf("%d", *vector + i);

	}
}

void afisare(int* vector, int dimensiune)
{
	for (int i = 0; i < dimensiune; i++)
	{
		printf("\n vector[%d]=%d", i, vector[i]);
	}
}

int main() {
	int numarIntreg;
	char caracter;
	float numarReal;

	numarIntreg = 7;
	caracter = 'A';
	numarReal = 70.5f;

	//putem pune %d de la decimal sau %i de la integer;
	// %c pt caracter
	// %.2f numar real cu 2 zecimale
	//la C fata de cpp mentionam tipul si variabila
	//endl vs \n

	printf("%d \n", numarIntreg);
	printf("%c \n", caracter);
	printf("%d \n", caracter);
	printf("%.2f \n", numarReal);

	//sirurile de caractere pot fi alocate dinamic sau static
	//sir de 8 - putem aloca 7 - ultimul e terminatorul de sir \0
	char sirCaractere[8];
	for (int i = 0; i < 8; i++)
	{
		sirCaractere[i] = 97 + i; //literele de la a la a+7 in ascii
	}
	sirCaractere[7] = '\0';
	//nu am alocat memorie corect sau nu am marcat terminatorul de sir - daca apare dubios
	printf("%s \n", sirCaractere);

	char* sirAlocatDinamic;
	sirAlocatDinamic = (char*)malloc(6 * sizeof(char));
	for (int i = 0; i < 6; i++)
	{
		sirAlocatDinamic[i] = 65 + i;
	}
	sirAlocatDinamic[5] = '\0';
	printf("%s \n", sirAlocatDinamic);

	//alocarea si dezalocarea in heap - ca sa evitam memory leaks
	//in cpp: parametri - valoare, referinta, adresa(pointeri)
	//in c param - valoare, pointer
	//transmitere prin valoare - la sf executiei functiei se vor pierde
	//transmitere prin pointer
	//metodele - la nivelul claselor, apelate pe obiecte
	//functiile - globale, in C

	int var1 = 1, var2 = 10;
	interschimbare(var1, var2);
	printf("\n var1 = %d, var2=%d", var1, var2);


	interschimbarePrinPointer(&var1, &var2);
	printf("\n var1 = %d, var2=%d", var1, var2);

	//citirea de la tastatura a unui vector + afisarea lui
	int* vector;
	int dimensiune;
	citireDeLaTastatura(&vector, &dimensiune);

	afisare(vector, dimensiune);
}