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
#define start_size sizeof(void *)
#define end_size sizeof(void *)
#define name_size ((name_length + 1) * sizeof(char))
#define phone_size (sizeof(int))
#define age_size (sizeof(int))
#define next_size (sizeof(void *))
#define previous_size (sizeof(void *))
#define search_name_size (sizeof(char) * 10)
#define search_flag_size sizeof (int)

// pBuffer structure
#define option_address 0
#define counter_address (option_size)
#define search_name_address (option_size + counter_size)
#define start_address (option_size + counter_size + search_name_size)
#define end_address (option_size + counter_size + search_name_size + start_size)
#define search_flag_address (option_size + counter_size + search_name_size + start_size + end_size)

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
void *FIND(void *pBuffer, char *name);
void SEARCH(void *pBuffer);
void POP(void *pBuffer);
void CLEAR(void *pBuffer);
void SHOW(void *person);
int EMPTY(void *pBuffer);



int main() {
	void *pBuffer = malloc(option_size + counter_size + search_name_size + start_size + end_size + search_flag_size);

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
				POP(pBuffer);
				break;
			case FIND_VALUE:
				SEARCH(pBuffer);
				break;
			case LIST_VALUE:
				LIST(pBuffer);
				break;
			case EXIT_VALUE:
				CLEAR(pBuffer);
				return 0;
		}
		
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

	printf("Insira uma opcao: ");
	scanf("%d", pOption);
}


void RESET(void *pBuffer) {
	*(int *)getBufferRef(pBuffer, option_address) = 0;
	*(int *)getBufferRef(pBuffer, counter_address) = 0;
	*(int *)getBufferRef(pBuffer, search_name_address) = '\0';
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

	// Tratando adição no inicio
	currentPerson = *(void **)(getBufferRef(pBuffer, start_address));

	*(void **)(getBufferRef(personToAdd, next_address)) = currentPerson;
	*(void **)(getBufferRef(currentPerson, previous_address)) = personToAdd;
	*(void **)(getBufferRef(pBuffer, start_address)) = personToAdd;
}

void LIST(void *pBuffer) {
	void *person = *(void **)(getBufferRef(pBuffer, start_address));

	while(person) {
		SHOW(person);

		person = *(void **)(getBufferRef(person, next_address));
	}
	printf("_________________\n\n\n");
}

void SEARCH(void *pBuffer) {
	char *name = (char *)getBufferRef(pBuffer, search_name_address);
	int *searchFlag = (int *)getBufferRef(pBuffer, search_flag_address);
	void *person;

	if(EMPTY(pBuffer)) {
		printf("\n\n=====Lista vazia=====\n\n");
		return;
	}

	*searchFlag = 0;

	printf("Insira o nome do contato: ");
	scanf("%s", name);

	printf("\n\n");

	person = FIND(*(void **)getBufferRef(pBuffer, start_address), name);

	while(person) {
		SHOW(person);

		person = FIND(*(void **)getBufferRef(person, next_address), name);
		*searchFlag = 1;
	}
	printf("_________________\n\n");
	
	if(!*searchFlag) printf("Contato nao encontrado");
	return;
}

void *FIND(void *initial, char *name) {
	void *person = initial;

	while(person) {
		if(strcmp(name, getBufferRef(person, name_address)) == 0) {
			return person;
		}
		person = *(void **)getBufferRef(person, next_address);
	}

	return NULL;

	printf("\n\nContato nao encontrado!\n\n");
}

int EMPTY(void *pBuffer) {
	if(getBufferRef(pBuffer, start_address) == NULL && getBufferRef(pBuffer, end_address) == NULL) return 1;
	return 0;
}

void SHOW(void *person) {
	printf("_________________\n");
	printf("| Nome: %s\n", (char *)getBufferRef(person, name_address));
	printf("| Idade: %d\n", *(int *)getBufferRef(person, age_address));
	printf("| Telefone: %d\n", *(int *)getBufferRef(person, phone_address));
}

void POP(void *pBuffer) {
	char *name = (char *)getBufferRef(pBuffer, search_name_address);
	int *searchFlag = (int *)getBufferRef(pBuffer, search_flag_address);
	void *person;
	void *auxPerson;

	if(EMPTY(pBuffer)) {
		printf("\n\n=====Lista vazia=====\n\n");
		return;
	}

	*searchFlag = 0;

	printf("Insira o nome do contato: ");
	scanf("%s", name);

	printf("\n\n");

	person = FIND(*(void **)getBufferRef(pBuffer, start_address), name);

	while(person) {
		if(person == *(void **)getBufferRef(pBuffer, start_address)) {
			// Primeira pessoa
			*(void **)getBufferRef(pBuffer, start_address) = *(void **)getBufferRef(person, next_address);
				if(person == *(void **)getBufferRef(pBuffer, end_address)) {
					// Única pessoa da lista
					*(void **)getBufferRef(pBuffer, end_address) = NULL;
				}
			free(person);
		} else if(person == *(void **)getBufferRef(pBuffer, end_address)) {
			// Ultima pessoa
			auxPerson = *(void **)getBufferRef(person, previous_address);
			*(void **)getBufferRef(pBuffer, end_address) = auxPerson;
			*(void **)getBufferRef(auxPerson, next_address) = NULL;
			free(person);
		} else {
			// Meio
			auxPerson = *(void **)getBufferRef(person, previous_address);
			*(void **)getBufferRef(auxPerson, next_address) = *(void **)getBufferRef(person, next_address);

			auxPerson =  *(void **)getBufferRef(person, next_address);
			*(void **)getBufferRef(auxPerson, previous_address) = *(void **)getBufferRef(person, previous_address);

			free(person);
		}

		*searchFlag = 1;
		person = FIND(*(void **)getBufferRef(pBuffer, start_address), name);
	}
}

void CLEAR(void *pBuffer) {
	void *person = *(void **)getBufferRef(pBuffer, start_address);
	void *auxPerson;

	while(person) {
		auxPerson = *(void **)getBufferRef(person, next_address);
		free(person);

		person = auxPerson;
	}

	free(pBuffer);
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
	scanf("%d", (int *)getBufferRef(person, age_address));

	printf("\nInserir a telefone: ");
	scanf("%d", (int *)getBufferRef(person, phone_address));
}

void printPBuffer(void *pBuffer) {
	printf("\n");
	printf("option: %d\n", *(int *)getBufferRef(pBuffer, option_address));
	printf("counter: %d\n", *(int *)getBufferRef(pBuffer, counter_address));
	// printf("start: ", *(int *)getBufferRef(pBuffer, start_address));
	// printf("end: ", *(int *)getBufferRef(pBuffer, end_address));
	printf("\n\n");
}

