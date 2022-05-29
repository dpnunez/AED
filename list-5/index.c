#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <sys/time.h>

#define generate_value 1
#define exit_value 2

// Helpers
void buildRandomVector(int vector[], int n);
void printVector(int vector[], int n);
void menu(int *option);
void swap(int *a, int *b);
void resetVector(int original[], int sortable[], int n);
void generateSortLog(int vector[], int originalVector[], int size);
void merge(int dataVector[], int size, int left, int middle, int right);
void checkOrder(int dataVector[], int vectorSize);

// Sort algo.
void selectionSort(int arr[], int n);
void insertionSort(int vector[], int n);
void quickSort(int dataVector[], int left, int right);
void mergeSort(int dataVector[], int size, int left, int right);

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
					originalVector = realloc(originalVector, sizeof(int) * size);
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

void quickSort(int vector[], int left, int right) {
	int pivot, i, j;
	i = left;
	j = right;
	pivot = vector[(left + right) / 2];
	do {
		while (vector[i]<pivot)
			i++;
		while (pivot<vector[j])
			j--;
		if (i <= j) {
			swap(&vector[i], &vector[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (left<j)
		quickSort(vector, left, j);
	if (i<right)
		quickSort(vector, i, right);
}

void mergeSort(int dataVector[], int size, int left, int right) {
  if (left >= right) {
    return;
  }

  int middle = (left + right) / 2;

  mergeSort(dataVector, size, left, middle);     
  mergeSort(dataVector, size, middle + 1, right); 

  if (dataVector[middle] <= dataVector[middle + 1]) { 
    return;
  }
  merge(dataVector, size, left, middle, right); 
}

void merge(int dataVector[], int size, int left, int middle, int right) {
  int auxIndex = left, startVector = left, middleIndex = middle + 1;
  int vectorAux[size];

  for (int i = left; i <= right; i++) { 
    vectorAux[i] = dataVector[i];
  }

  while (startVector <= middle && middleIndex <= right) {
    if (vectorAux[startVector] <= vectorAux[middleIndex]) {
      dataVector[auxIndex] = vectorAux[startVector];
      startVector++;
    } else {
      dataVector[auxIndex] = vectorAux[middleIndex];
      middleIndex++;
    }
    auxIndex++;
  }

  while (startVector <= middle) {
    dataVector[auxIndex] = vectorAux[startVector];
    auxIndex++;
    startVector++;
  }

  while (middleIndex <= right) {
    dataVector[auxIndex] = vectorAux[middleIndex];
    auxIndex++;
    middleIndex++;
  }
}

void checkOrder(int dataVector[], int vectorSize) {
  for (int i = 0; i < vectorSize - 1; i++) {
    if (dataVector[i] > dataVector[i + 1]) {
      printf("\n  -Lista não ordenada!!\n");
      return;
    }
  }
  printf("\n  -Lista ordenada com sucesso\n");
  return;
}


void generateSortLog(int vector[], int originalVector[], int size) {
	struct timeval begin, end;
  long seconds;
  long microseconds;
  double elapsed;

	printf("\n\n---RELATÓRIO DE ALGORÍTIMOS---\n");

	printf("Selection sort: ");
	gettimeofday(&begin, 0);
	selectionSort(vector, size);
	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	printf("\n  -WallTime: %.3f ms.", elapsed * 1000);
	checkOrder(vector, size);
	resetVector(originalVector, vector, size);

	printf("\nInsertion sort: ");
	gettimeofday(&begin, 0);
	insertionSort(vector, size);
	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	printf("\n  -WallTime: %.3f ms.", elapsed * 1000);
	checkOrder(vector, size);
	resetVector(originalVector, vector, size);

	printf("\nQuick sort: ");
	gettimeofday(&begin, 0);
	quickSort(vector, 0, size-1);
	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	printf("\n  -WallTime: %.3f ms.", elapsed * 1000);
	checkOrder(vector, size);
	resetVector(originalVector, vector, size);

	printf("\nMerge sort: ");
	gettimeofday(&begin, 0);
	mergeSort(vector, size, 0, size - 1);
	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	printf("\n  -WallTime: %.3f ms.", elapsed * 1000);
	checkOrder(vector, size);
	resetVector(originalVector, vector, size);
}
