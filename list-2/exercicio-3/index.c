#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD_VALUE 1
#define REMOVE_VALUE 2
#define FIND_VALUE 3
#define LIST_VALUE 4
#define EXIT_VALUE 5

#define COUNTER_SIZE sizeof(int)
#define NAME_SIZE sizeof(char) * 10
#define AGE_SIZE sizeof(int)
#define NUMBER_SIZE sizeof(int)

void getOption(int *option);
void createContact(void **contact_list);
void printContacts(void **contact_list);
void *findContact(void **contact_list, char *contact_name);
void searchContact(void **contact_list);
void deleteContact(void **contact_list);
int isLastContact(void **contact_list, void *contact_to_delete);

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
				deleteContact(&pBuffer);
				break;
			case FIND_VALUE:
				searchContact(&pBuffer);
				break;
			case LIST_VALUE:
				printContacts(&pBuffer);
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

// Length = quantidade de contatos
// Size = tamanho em bytes da lista
void createContact(void **contact_list) {
	int contact_size = NAME_SIZE + AGE_SIZE + NUMBER_SIZE;
	int current_list_length = *(int *)(*contact_list);
	int current_list_size = COUNTER_SIZE + (current_list_length * contact_size);
	int next_contact_list_size = current_list_size + contact_size;

	*contact_list = realloc(*contact_list, next_contact_list_size);
	void *cursor = (*contact_list + (contact_size * current_list_length) + COUNTER_SIZE);

	printf("Nome: ");
	scanf("%s", (char *)cursor);
	cursor += NAME_SIZE;

	printf("Idade: ");
	scanf("%d", (int *)cursor);
	cursor += AGE_SIZE;

	printf("Telefone: ");
	scanf("%d", (int *)cursor);

	*(int *)(*contact_list) += 1;
	printf("Adicionado com sucesso\n\n");
}

void printContacts(void **contact_list) {
	int index;
	int current_list_length = *(int *)(*contact_list);
	int contact_size = NAME_SIZE + AGE_SIZE + NUMBER_SIZE;
	void *cursor = NULL;

	printf("\n\n\n===Lista de contatos: ===\n");
	for(index = 0; index < current_list_length; index++) {
		printf("Contato %d: \n", index + 1);
		
		cursor = (char *)(*contact_list + COUNTER_SIZE + (index * contact_size));
		printf("  |Nome: %s\n", (char *)cursor);

		cursor += NAME_SIZE;
		printf("  |Idade: %d\n", *(int *)cursor);

		cursor += AGE_SIZE;
		printf("  |Telefone: %d\n\n\n", *(int *)cursor);
	}
	printf("=========================\n\n\n");
}

void searchContact(void **contact_list) {
	char *contact_name = (char *)malloc(sizeof(char) * 10);
	void *contact = NULL;

	if (contact_name == NULL) {
		printf("Ocorreu um erro ao buscar o usuário");
		return;
	}

	printf("Insira o nome do usuário: ");
	scanf("%s", contact_name);

	contact = findContact(contact_list, contact_name);
	if(!contact) {
		printf("Contato nao encontrado\n\n");
		return;
	}

	printf("  |Nome: %s\n", (char *)contact);

	contact += NAME_SIZE;
	printf("  |Idade: %d\n", *(int *)contact);

	contact += AGE_SIZE;
	printf("  |Telefone: %d\n\n\n", *(int *)contact);

	free(contact_name);
}

void *findContact(void **contact_list, char *contact_name) {
	int current_list_length = *(int *)(*contact_list);
	int contact_size = NAME_SIZE + AGE_SIZE + NUMBER_SIZE;

	int index;
	char *cursor_name = (char *)(*contact_list + COUNTER_SIZE);

	for(index = 0; index < current_list_length; index++) {
		cursor_name += contact_size;
		if(strstr(cursor_name, contact_name)) {
			return cursor_name;
		}
	}

	cursor_name = NULL;
	return cursor_name;
}

void deleteContact(void **contact_list) {
	char *contact_name = (char *)malloc(sizeof(char) * 10);
	void *contact_to_delete, *contacts_to_move;

	int contact_size = NAME_SIZE + AGE_SIZE + NUMBER_SIZE;
	int current_list_length = *(int *)(*contact_list);
	int current_list_size = COUNTER_SIZE + (current_list_length * contact_size);

	printf("Insira o nome do contato a ser deletado: ");
	scanf("%s", contact_name);

	contact_to_delete = findContact(contact_list, contact_name);
	if(!contact_to_delete) {
		printf("Contato nao encontrado\n");
		return;
	}

	contacts_to_move = (contact_to_delete + contact_size);

	if(isLastContact(contact_list, contact_to_delete)) {
		*contact_list = realloc(*contact_list, current_list_size - contact_size);
	} else {
		printf("NAO É O ULTIMO");
	}
	*(int *)(*contact_list) -= 1;
	free(contact_name);
}


int isLastContact(void **contact_list, void *contact_to_delete) {
	int contact_size = NAME_SIZE + AGE_SIZE + NUMBER_SIZE;
	int current_list_length = *(int *)(*contact_list);
	return (*contact_list + COUNTER_SIZE) + ((current_list_length - 1) * contact_size) == contact_to_delete;
} 