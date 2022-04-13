#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD_VALUE 1
#define REMOVE_VALUE 2
#define FIND_VALUE 3
#define LIST_VALUE 4
#define EXIT_VALUE 5

#define name_length 10


// vars sizes
#define option_size sizeof(int)
#define counter_size sizeof(int)
#define loop_counter_size sizeof(int)
#define start_size sizeof(void *)
#define end_size sizeof(void *)
#define name_size ((name_length + 1) * sizeof(char))
#define phone_size (sizeof(int))
#define age_size (sizeof(int))
#define next_size (sizeof(void *))
#define previous_size (sizeof(void *))

// pBuffer structure
#define option_address 0
#define counter_address (option_size)
#define loop_counter_address (option_size + counter_size)
#define start_address (option_size + counter_size + loop_counter_size)
#define end_address (option_size + counter_size + loop_counter_size + end_size)

// person structure
#define name_address 0
#define phone_address (name_size)
#define age_address (name_size + phone_size)
#define next_address (name_size + phone_size + age_size)
#define previous_address (name_size + phone_size + age_size + next_size)


void printPBuffer(void *pBuffer);
void menu(int *pOption);
void *getBufferRef(void *pBuffer, size_t data_address);
void readPerson(void *person);
void SORT(void *pBuffer, void *personToAdd);
void RESET(void *pBuffer);
void PUSH(void *pBuffer);
void LIST(void *pBuffer);


int main() {
	void *pBuffer = malloc(option_size + counter_size + loop_counter_size + start_size + end_size);

	if(pBuffer == NULL) {
		printf("Erro ao alocar pBuffer");
		exit(1);
	}
	RESET(pBuffer);


	// printPBuffer(pBuffer);


	while(1) {
		menu(pBuffer);
		switch(*(int *)getBufferRef(pBuffer, option_address)) {
			case ADD_VALUE:
				PUSH(pBuffer);
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
		LIST(pBuffer);
	}
}


void *getBufferRef(void *pBuffer, size_t data_address) {
	return pBuffer + data_address;
}

void menu(int *pOption) {
	printf("[%d] - ADICIONAR CONTATO\n", ADD_VALUE);
	printf("[%d] - REMOVER CONTACT\n", REMOVE_VALUE);
	printf("[%d] - BUSCAR POR NOME\n", FIND_VALUE);
	printf("[%d] - LISTAR\n", LIST_VALUE);
	printf("[%d] - SAIR\n\n", EXIT_VALUE);

	scanf("%d", pOption);
}


void RESET(void *pBuffer) {
	*(int *)getBufferRef(pBuffer, option_address) = 0;
	*(int *)getBufferRef(pBuffer, counter_address) = 0;
	*(int *)getBufferRef(pBuffer, loop_counter_address) = 0;
	*(void **)getBufferRef(pBuffer, start_address) = NULL;
	*(int **)getBufferRef(pBuffer, end_address) = NULL;
}

void PUSH(void *pBuffer) {
	void *person = (void *)malloc(name_size + phone_size + age_size + next_size + previous_size);

	readPerson(person);

	*(void **)(getBufferRef(person, next_address)) = NULL;
	*(void **)(getBufferRef(person, previous_address)) = NULL;


	if(*(void **)getBufferRef(pBuffer, start_address) == NULL) {
			*(void **)(getBufferRef(pBuffer, start_address)) = person;
    	*(void **)(getBufferRef(pBuffer, end_address)) = person;

			return;
	}

	SORT(pBuffer, person);
}

void SORT(void *pBuffer, void *personToAdd) {
	void *currentPerson = *(void **)(getBufferRef(pBuffer, end_address));
	void *personToAddName = (char *)(getBufferRef(personToAdd, name_address));

	while(currentPerson != NULL) {
		char *currentPersonName = (char *)(getBufferRef(currentPerson, name_address));

		if(strcmp(currentPerson, personToAddName) <= 0) {
			if(*(void **)getBufferRef(currentPerson, next_address) == NULL) {
				// Adicionando no final da fila
				*(void **)(getBufferRef(personToAdd, previous_address)) = currentPerson;
				*(void **)(getBufferRef(personToAdd, next_address)) = NULL;

				*(void **)(getBufferRef(currentPerson, next_address)) = personToAdd;
				*(void **)(getBufferRef(pBuffer, end_address)) = personToAdd;
				return;
			}

			// Adicionando no meio da fila;
			*(void **)(getBufferRef(personToAdd, previous_address)) = currentPerson;
			*(void **)(getBufferRef(personToAdd, next_address)) = *(void **)(getBufferRef(currentPerson, next_address));

			void *tempPerson = *(void **)(getBufferRef(currentPerson, next_address));
			*(void **)(getBufferRef(currentPerson, next_address)) = personToAdd;
			*(void **)(getBufferRef(tempPerson, previous_address)) = personToAdd;
			
			return;
		}
		currentPerson = *(void **)(getBufferRef(currentPerson, previous_address));
	}

	// Tratando adicao no inicio
	currentPerson = *(void **)(getBufferRef(pBuffer, start_address));

	*(void **)(getBufferRef(personToAdd, next_address)) = currentPerson;
	*(void **)(getBufferRef(currentPerson, previous_address)) = personToAdd;
	*(void **)(getBufferRef(pBuffer, start_address)) = personToAdd;
}

void LIST(void *pBuffer) {
	void *person = *(void **)(getBufferRef(pBuffer, start_address));

	while(person) {
		printf("\n%s \n", (char *)(getBufferRef(person, name_address)));

		person = *(void **)(getBufferRef(person, next_address));
	}
}

void readPerson(void *person) {
	printf("\nInserir o nome: ");
	scanf("%s", (char *)getBufferRef(person, name_address));

	// Prever quando o nome estoura o person todo
	while (strlen((char *)getBufferRef(person, name_address)) > 10) {
    printf("*********************************************** \n");
    printf("* Insira um nome com no máximo 10 caracteres! *\n");
    printf("*********************************************** \n");
    printf("Inserir o nome: ");
    scanf("%s", (char *)getBufferRef(person, name_address));
  }

	printf("\nInserir a idade: ");
	scanf("%s", (char *)getBufferRef(person, age_address));

	printf("\nInserir a telefone: ");
	scanf("%s", (char *)getBufferRef(person, phone_address));
}

void printPBuffer(void *pBuffer) {
	printf("\n");
	printf("option: %d\n", *(int *)getBufferRef(pBuffer, option_address));
	printf("counter: %d\n", *(int *)getBufferRef(pBuffer, counter_address));
	printf("loop: %d", *(int *)getBufferRef(pBuffer, loop_counter_address));
	// printf("start: ", *(int *)getBufferRef(pBuffer, start_address));
	// printf("end: ", *(int *)getBufferRef(pBuffer, end_address));
	printf("\n\n");
}

