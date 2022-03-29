#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD_VALUE 1
#define REMOVE_VALUE 2
#define FIND_VALUE 3
#define LIST_VALUE 4
#define EXIT_VALUE 5

#define option_size sizeof(int)
#define list_counter_size sizeof(int)
#define loop_counter_size sizeof(int)
#define name_size (sizeof(char) * 10)

void getOption(int *option);

int main() {
	void *pBuffer = NULL;
	pBuffer = malloc(
		option_size +
		list_counter_size +
		loop_counter_size +
		name_size
	);

	if(pBuffer == NULL) {
		printf("Erro ao alocar pBuffer");
		return 1;
	}


	do {
		getOption(pBuffer);

		printf("Option é : %d", *(int *)pBuffer);

		switch(*(int *)pBuffer) {
			case ADD_VALUE:
				createContact(&pBuffer);
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
				return 0;
				break;
		}
	} while(1);
}


void getOption(int *option) {
	printf("[%d] - ADICIONAR CONTATO\n", ADD_VALUE);
	printf("[%d] - REMOVER CONTACT\n", REMOVE_VALUE);
	printf("[%d] - BUSCAR POR NOME\n", FIND_VALUE);
	printf("[%d] - LISTAR\n", LIST_VALUE);
	printf("[%d] - SAIR\n\n", EXIT_VALUE);

	printf("Inserir opçao:");
	scanf("%d", option);
}