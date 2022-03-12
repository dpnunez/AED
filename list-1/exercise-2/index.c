#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_VALUE 4

void readOption(int *option);
void addName(char **list);
void removeName(char **list);
void printList(char *list);

int main() {
	int option;
  char* list = NULL;
  list = malloc(1 * sizeof(char));
  list[0] = '\0';


	do {
		readOption(&option);
		
		switch (option) {
			case 1:
				addName(&list);
				break;
			case 2:
				removeName(&list);
				break;
			case 3:
				printList(list);
				break;
			case EXIT_VALUE:
				free(list);
        exit(0);
        break;
			default:
				printf("Comando nao mapeado");
				break;
		}

		printf("-----------------------------");
	} while(1);
}



void readOption(int *option) {
	printf("\n\n1) Adicionar nome\n2) Remover nome\n3) Listar\n4) Sair\n\nOpcao: ");
	scanf("%d", option);
}

void printList(char *list) {
	if (strlen(list) > 0) {
    printf("\nList names: %s\n", list);
  } else {
    printf("\n*****************************");
    printf("\n* A lista encontra-se vazia *");
    printf("\n*****************************\n");
  }
}


// https://stackoverflow.com/questions/13431108/changing-address-contained-by-pointer-using-function
void addName(char **list) {
	char current_name[50];
	int new_list_length;
	int is_first_name;

	printf("Insira o novo nome: ");
	scanf("%s", current_name);

	if(!strlen(*list)) {
		is_first_name = 1;
	} else {
		is_first_name = 0;
	}

	
	if(is_first_name) {
		new_list_length = (strlen(current_name) + 1);
		*list = realloc(*list, (strlen(current_name) + 1) * sizeof(char)); // + 1 because \0;
		strcat(*list, current_name);
	} else {
		new_list_length = (strlen(*list) + 2 + strlen(current_name));
		*list = realloc(*list, new_list_length * sizeof(char));
		strcat(*list, ",");
		strcat(*list, current_name);
	}

	strcat(*list, "\0");
}

void removeName(char **list) {
	char name_to_remove[50];
	char 
		*occurrence, 
		*temp_reallocation = NULL, 
		*is_not_last_name;
	int name_length, new_list_length, i = 0;

	printf("Insira o nome a ser removido: ");
	scanf("%s", name_to_remove);

	name_length = strlen(name_to_remove);
	occurrence = strstr(*list, name_to_remove);

	if(occurrence == NULL) {	/* Nome nao aparece na lista */
		return;
	}

	is_not_last_name = strstr(occurrence, ",");

	if (is_not_last_name != NULL) {
		temp_reallocation = occurrence + name_length + 1;
	}

	while(temp_reallocation != NULL && *temp_reallocation != '\0') {
		*occurrence = *temp_reallocation;
		occurrence++;
		temp_reallocation++;
	}

	if (is_not_last_name == NULL && occurrence != *list) {
			*(occurrence - 1) = '\0';
	} else {
		*(occurrence) = '\0';
	}

	*list = realloc(*list, (strlen(*list) + 1) * sizeof(char));
}
