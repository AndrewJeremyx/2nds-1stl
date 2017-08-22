#include <stdio.h>
#include <stdlib.h>

void *IntSum(void *A,void *B)
{
	int *C;

	C = (int*) malloc(sizeof(int));
	*C = *((int*)A) + *((int*)B);
	return (void*)C;
}

void *IntMultiplication(void *A,void *B)
{
	int *C;

	C = (int*) malloc(sizeof(int));
	*C = *((int*)A) * *((int*)B);
	return (void*)C;
}

void* IntScan()
{
	int *A;

	A = (int*)malloc(sizeof(int));
	scanf("%d",A);
	return (void*)A;
}

void IntPrint(void* A)
{
	printf("%+d",*((int*)A));
}

void* IntNeutralElemSum()
{
	int *A;
	A = (int*)malloc(sizeof(int));
	return (void*)A;
}

void IntDestruct(void* A)
{
	free(A);
}