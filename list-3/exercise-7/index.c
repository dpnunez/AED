#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD_VALUE 1
#define REMOVE_VALUE 2
#define FIND_VALUE 3
#define LIST_VALUE 4
#define EXIT_VALUE 5

#define name_length 30
#define list_length 10

#define option_size sizeof(int)
#define counter_size sizeof(int)
#define loop_counter_size sizeof(int)
#define name_size (sizeof(char) * name_length)

#define option_address 0
#define counter_address (option_size)
#define loop_counter_address (option_size + counter_size)
#define name_address (option_size + counter_size + loop_counter_size)

typedef struct {
	char name[name_length];
	int age;
	int phone;
} Person;

void getOption(int *option);
void createPerson(void *pBuffer);
void *getBufferRef(void *pBuffer, size_t data_address);
void listPersons(void *pBuffer);
void findPerson(void *pBuffer);
void deletePerson(void *pBuffer);
void deletePersonOccurrence(void *pBuffer);

Person personList[list_length];

int main() {
	void *pBuffer = NULL;
	pBuffer = malloc(
		option_size +
		counter_size +
		loop_counter_size +
		name_size
	);

	if(pBuffer == NULL) {
		printf("Erro ao alocar pBuffer");
		return 1;
	}


	do {
		getOption(pBuffer);

		switch(*(int *)pBuffer) {
			case ADD_VALUE:
				createPerson(pBuffer);
				break;
			case REMOVE_VALUE:
				deletePerson(pBuffer);
				break;
			case FIND_VALUE:
				findPerson(pBuffer);
				break;
			case LIST_VALUE:
				listPersons(pBuffer);
				break;
			case EXIT_VALUE:
				free(pBuffer);
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

	printf("Inserir opção:");
	scanf("%d", option);
}

void createPerson(void *pBuffer) {
	int *counter = (int *)(getBufferRef(pBuffer, counter_address));

	if(*counter == list_length) {
		printf("Lista cheia!! \n\n");
		return;
	}

	printf("Nome: ");
	scanf("%s", personList[*counter].name);
	printf("Idade: ");
	scanf("%d", &personList[*counter].age);
	printf("Telefone: ");
	scanf("%d", &personList[*counter].phone);

	*counter += 1;
}

void listPersons(void *pBuffer) {
	int *counter = (int *)(getBufferRef(pBuffer, counter_address));
	int *index = (int *)(getBufferRef(pBuffer, loop_counter_address));

	printf("Lista de contatos: \n\n");

	for(*index = 0; *index < *counter; *index+=1) {
		printf("_________________\n");
		printf("| Nome: %s\n", personList[*index].name);
		printf("| Idade: %d\n", personList[*index].age);
		printf("| Telefone: %d\n", personList[*index].phone);
	}
	printf("_________________\n\n\n");
}

void *getBufferRef(void *pBuffer, size_t data_address) {
	return pBuffer + data_address;
}


void deletePerson(void *pBuffer) {
	char *nameBuffer = (char *)(getBufferRef(pBuffer, name_address));
	int *counter = (int *)(getBufferRef(pBuffer, counter_address));

	if(*counter==0) {
		printf("\n\nLista vazia!!\n\n");
		return;
	}

	printf("Insira a pessoa a ser deletada: ");
	scanf("%s", nameBuffer);

	deletePersonOccurrence(pBuffer);
}

void deletePersonOccurrence(void *pBuffer) {
	int *counter = (int *)(getBufferRef(pBuffer, counter_address));
	int *index = (int *)(getBufferRef(pBuffer, loop_counter_address));
	char *nameBuffer = (char *)(getBufferRef(pBuffer, name_address));

	for(*index=0; *index<*counter; *index+=1) {
		if(strstr(personList[*index].name, nameBuffer)) {
			// Person to delete;
			while(*index != *counter - 1) {
				strcpy(personList[*index].name, personList[*index + 1].name);
				personList[*index].age = personList[*index + 1].age;
				personList[*index].phone = personList[*index + 1].phone;

				*index+=1;
			}
			*counter-=1;
			deletePersonOccurrence(pBuffer);
		}
	}
}

void findPerson(void *pBuffer) {
	int *counter = (int *)(getBufferRef(pBuffer, counter_address));
	int *index = (int *)(getBufferRef(pBuffer, loop_counter_address));
	char *nameBuffer = (char *)(getBufferRef(pBuffer, name_address));

	printf("Insira o nome a ser pesquisado: ");
	scanf("%s", nameBuffer);

	for(*index=0; *index<*counter; *index+=1) {
		if(strstr(personList[*index].name, nameBuffer)) {
			printf("_________________\n");
			printf("| Nome: %s\n", personList[*index].name);
			printf("| Idade: %d\n", personList[*index].age);
			printf("| Telefone: %d\n", personList[*index].phone);
		}
	}
	printf("_________________\n\n\n");

}