#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ADD_VALUE 1
#define REMOVE_VALUE 2
#define FIND_VALUE 3
#define LIST_VALUE 4
#define EXIT_VALUE 5

#define name_length 10

#define option_size sizeof(int)
#define counter_size sizeof(int)
#define loop_counter_size sizeof(int)
#define start_size sizeof(void *)
#define end_size sizeof(void *)

#define option_address 0
#define counter_address (option_size)
#define loop_counter_address (option_size + counter_size)
#define start_address (option_size + counter_size + loop_counter_size)
#define end_address (option_size + counter_size + loop_counter_size + end_size)


void printPBuffer(void *pBuffer);
void menu(int *pOption);
void *getBufferRef(void *pBuffer, size_t data_address);
void RESET(void *pBuffer);
void PUSH(void *pBuffer);


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