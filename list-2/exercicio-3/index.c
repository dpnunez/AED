#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD_VALUE 1
#define REMOVE_VALUE 2
#define FIND_VALUE 3
#define LIST_VALUE 4
#define EXIT_VALUE 5

#define CONTACT_SIZE sizeof(int) * 2 + sizeof(char) * 10

void getOption(int *option);
void createContact(void **contact_list);

int main() {
	int option;
	void *pBuffer = NULL;

	pBuffer = (void *)malloc(1 * sizeof(int));

	if(pBuffer == NULL) {
		printf("Error ao tentar alocar a memória");
		exit(1);
	}

	*(int *)pBuffer = 0; // pBuffer[0] = 0?

	do {
		getOption(&option);

		switch(option) {
			case ADD_VALUE:
				createContact(&pBuffer);
				break;
			case REMOVE_VALUE:
				break;
			case FIND_VALUE:
				break;
			case LIST_VALUE:
				break;
			case EXIT_VALUE:
				break;
		}
	} while(1);

	return 0;
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

void createContact(void **contact_list) {
	int contact_list_length = *(int *)(*contact_list);
	int contact_list_size = sizeof(int) + (contact_list_length * CONTACT_SIZE);
	int next_contact_list_size = sizeof(int) + ((contact_list_length + 1) * CONTACT_SIZE);

	*contact_list = realloc(*contact_list, next_contact_list_size);

	printf("\nNome:");
	scanf("%s", (char *)(contact_list + contact_list_size));
	printf("\n%s\n", (char *)(contact_list + contact_list_size));
}