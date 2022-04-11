#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD_VALUE 1
#define REMOVE_VALUE 2
#define FIND_VALUE 3
#define LIST_VALUE 4
#define EXIT_VALUE 5


void menu(int *pOption);

int main() {
	int *option = NULL;
	option = malloc(sizeof(int));
	
	if(!option) { 
		printf("Erro ao alocar os dados iniciais");
		return 1;
	}


	while(1) {
		menu(option);

		switch(*option) {
			case ADD_VALUE:
				// createContact(&pBuffer);
				break;
			case REMOVE_VALUE:
				// deleteContact(&pBuffer);
				break;
			case FIND_VALUE:
				// searchContact(&pBuffer);
				break;
			case LIST_VALUE:
				// printContacts(&pBuffer);
				break;
			case EXIT_VALUE:
				// free(pBuffer);
				// return 0;
				break;
		}

		printf("option é: %d", *option);
	}
}


void menu(int *pOption) {
	printf("[%d] - ADICIONAR CONTATO\n", ADD_VALUE);
	printf("[%d] - REMOVER CONTACT\n", REMOVE_VALUE);
	printf("[%d] - BUSCAR POR NOME\n", FIND_VALUE);
	printf("[%d] - LISTAR\n", LIST_VALUE);
	printf("[%d] - SAIR\n\n", EXIT_VALUE);

	scanf("%d", pOption);
}