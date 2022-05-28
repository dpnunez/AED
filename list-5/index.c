#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define generate_value 1
#define exit_value 2

// Helpers
void buildRandomVector(int vector[], int n);
void printVector(int vector[], int n);
void menu(int *option);
void swap(int *a, int *b);
void resetVector(int original[], int sortable[], int n);
void generateSortLog(int vector[], int originalVector[], int size);

// Sort algo.
void selectionSort(int arr[], int n);
void insertionSort(int vector[], int n);
void quickSort(int dataVector[], int left, int right);

int main() {
	int 
		size,
		option;

	int *vector = NULL;
	int *originalVector = NULL;
	
	// setup seed
	srand(time(NULL));

	do {
		menu(&option);

		switch(option) {
			case generate_value:
				printf("Insira o tamanho do array: ");
				scanf("%d", &size);
				if(!vector) {
					vector = malloc(sizeof(int) * size);
					originalVector = malloc(sizeof(int) * size);
				} else {
					vector = realloc(vector, sizeof(int) * size);
					originalVector = realloc(vector, sizeof(int) * size);
				}
				buildRandomVector(originalVector, size);
				resetVector(originalVector, vector, size);
				printf("Vetor gerado: ");
				printVector(vector, size);
				break;
			case exit_value:
				free(vector);
				exit(1);
				break;
			default: 
				printf("Nao mapeada");
		}

		generateSortLog(vector, originalVector, size);
	} while(1);

	return 0;
}

void buildRandomVector(int vector[], int n) {
	int i;
	for(i=0; i<n; i++) {
		vector[i] = rand()  % 100;
	}
}

void printVector(int vector[], int n) {
	int i;

	printf("[");
	for(i=0; i<n; i++) {
		if(i + 1 == n) {
			printf("%d", vector[i]);
		} else {
			printf("%d, ", vector[i]);
		}
	}
	printf("]");
}

void menu(int *option) {
	printf("\n\n\n------\n");
	printf("| %d. Gerar novo array\n", generate_value);
	printf("| %d. Sair\n", exit_value);
	printf("------\nInsira sua opcao: ");

	scanf("%d", option);
	printf("\n\n");
}

void resetVector(int original[], int sortable[], int n) {
	int i;
	for(i=0; i<n; i++)
		sortable[i] = original[i];
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
 
void selectionSort(int vector[], int n) {
	int temp_start, i, min_idx;
	for (temp_start = 0; temp_start < n-1; temp_start++) {
		min_idx = temp_start;
		for (i = temp_start+1; i < n; i++)
			if (vector[i] < vector[min_idx])
				min_idx = i;

		swap(&vector[min_idx], &vector[temp_start]);
	}
}

void insertionSort(int vector[], int n) {
  int auxIndex, current;
  for (int i = 1; i < n; i++) {
    current = vector[i];
    auxIndex = i - 1;
    while (auxIndex >= 0 && vector[auxIndex] > current) {
      vector[auxIndex + 1] = vector[auxIndex];
      auxIndex--;
    }
    vector[auxIndex + 1] = current;
  }
}

void quickSort(int dataVector[], int left, int right) {
  int pivot, temp;
  int i = left, j = right;
  pivot = dataVector[(left + right) / 2];

  do {
    while (dataVector[i] < pivot) { 
      i++;
    }
    while (dataVector[j] > pivot) { 
      j--;
    }
    if (i <= j) {
			swap(&dataVector[i], &dataVector[j]);
      i++;
      j--;
    }
  } while (i <= j);
  if (left < j) {
    quickSort(dataVector, left, j);
  }
  if (right > j) {
    quickSort(dataVector, i, right);
  }
}

void generateSortLog(int vector[], int originalVector[], int size) {
	printf("\n\n---RELATÓRIO DE ALGORITIMOS---\n");

	printf("Selection sort: ");
	selectionSort(vector, size);
	printVector(vector, size);
	resetVector(originalVector, vector, size);

	printf("\nInsertion sort: ");
	insertionSort(vector, size);
	printVector(vector, size);
	resetVector(originalVector, vector, size);

	printf("\nQuick Sort: ");
	quickSort(vector, 0, size-1);
	printVector(vector, size);
	resetVector(originalVector, vector, size);
}
