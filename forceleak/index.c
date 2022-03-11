#include<stdlib.h>
#include<stdio.h>

int main() {
	int *numbers;
	numbers = malloc(sizeof(int));

	printf("Olá mundo");

	numbers[0] = 2;

	free(numbers);
	return 0;
}