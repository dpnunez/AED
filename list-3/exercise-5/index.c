#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CREATE_VALUE 1
#define EXIT_VALUE 0

typedef struct {
	char nome[30];
	int idade;
	int altura;
} Pessoa;



void showMenu(int *pOption);
void createPessoa(Pessoa **pBuffer, int *pCounter);
void listPessoas(Pessoa *pBuffer, int listLength);

int main() {
	int option;
	int *counter = NULL;
	Pessoa *pBuffer = NULL;

	counter = malloc(sizeof(int));
	if(counter == NULL) {
		printf("Erro ao alocar o contador");
		return 1;
	}

	*counter = 0;


	do {
		showMenu(&option);
		if(option == EXIT_VALUE) break;
		createPessoa(&pBuffer, counter);
		// listPessoas(pBuffer, *counter); // To print list
	} while(1);

	free(counter);
	free(pBuffer);
	return 0;
}

void showMenu(int *pOption) {
	printf("Deseja inserir uma nova pessoa? (sim: %d; nao: %d)", CREATE_VALUE, EXIT_VALUE);
	scanf("%d", pOption);
}

void createPessoa(Pessoa **pBuffer, int *pCounter) {
	if(*pCounter == 0) {
		*pBuffer = malloc(sizeof(Pessoa));
	} else {
		*pBuffer = realloc(*pBuffer, sizeof(Pessoa) * (*pCounter + 1));
	}

	if(*pBuffer == NULL) {
		printf("Erro ao tentar alocar memória");
		exit(1);
	}


	// Sintaxe mais simples para acessar valores e endereços de ponteiros para ponteiros
	printf("Nome: ");
	scanf("%s", (*pBuffer)[*pCounter].nome);
	printf("Idade: ");
	scanf("%d", &(*pBuffer)[*pCounter].idade);
	printf("Altura: ");
	scanf("%d", &(*pBuffer)[*pCounter].altura);

	*pCounter += 1;
}

void listPessoas(Pessoa *pBuffer, int listLength) {
	int i;

	printf("Lista de pessoas: \n\n");

	for(i=0; i<listLength; i++) {
		printf("Nome: %s\n", pBuffer[i].nome);
		printf("idade: %d\n", pBuffer[i].idade);
		printf("altura: %d\n", pBuffer[i].altura);
	}

	printf("============\n\n");
}