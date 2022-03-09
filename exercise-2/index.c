#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_VALUE 4

int readOption(int *option);
void addName(char **ist);
void removeName();
void printList(char *list);

int main() {
	char *list = NULL;
	int option;

	list = malloc(1 * sizeof(char));
	list[0] = '\0';

	do {
		readOption(&option);

		switch (option) {
			case 1:
				addName(&list);
				break;
			case 2:
				printf("Remover nome");
				break;
			case 3:
				printList(list);
				break;
			case 4:
				printf("Saindo do programa");
				break;
			default:
				printf("Comando nao mapeado");
				break;
		}
	} while(option != EXIT_VALUE);

	return 0;
}



int readOption(int *option) {
	printf("\n\n1) Adicionar nome\n2) Remover nome\n3) Listar\n4) Sair\n\nOpcao: ");
	scanf("%d", option);
}

void printList(char *list) {
	if (strlen(list) == 0) {
		printf("\n\n=== Lista Vazia ===\n\n");
		return;
	}
	printf("\nLista: \n%s\n\n", list);
}


// https://stackoverflow.com/questions/13431108/changing-address-contained-by-pointer-using-function
void addName(char **list) {
	char currentName[50];
	int isFirstName;

	printf("Insira o novo nome: ");
	scanf("%s", currentName);

	if(!strlen(*list)) {
		isFirstName = 1;
	} else {
		isFirstName = 0;
	}

	
	if(isFirstName) {
		*list = realloc(*list, (strlen(currentName) + 1) * sizeof(char)); // + 1 because \0;
		strcat(*list, currentName);
	} else {
		*list = realloc(*list, (strlen(*list) + 2 + strlen(currentName)) * sizeof(char));
		strcat(*list, ",");
		strcat(*list, currentName);
	}

	strcat(*list, "\0");

}