#include <stdio.h>
#include <stdlib.h>

void *FloatSum(void *A,void *B)
{
	float *C;

	C = (float*) malloc(sizeof(float));
	*C = *((float*)A) + *((float*)B);
	return (void*)C;
}

void *FloatMultiplication(void *A,void *B)
{
	float *C;

	C = (float*) malloc(sizeof(float));
	*C = *((float*)A) * *((float*)B);
	return (void*)C;
}

void* FloatScan()
{
	float *A;

	A = (float*)malloc(sizeof(float));
	scanf("%f",A);
	return (void*)A;
}

void FloatPrint(void* A)
{
	printf("%+.2f",*((float*)A));
}

void* FloatNeutralElemSum()
{
	float *A;
	A = (float*)malloc(sizeof(float));
	return (void*)A;
}

void FloatDestruct(void* A)
{
	free(A);
}