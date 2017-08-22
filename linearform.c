#include <stdio.h>
#include <stdlib.h>

struct LinearForm
{
	unsigned int dimension;
	void **coordinates;
};

struct LinearForm *LinearFormCreate(unsigned int dim)
{
	struct LinearForm *A = (struct LinearForm*) malloc(sizeof(struct LinearForm));
	A->dimension = dim;
	A->coordinates = malloc(sizeof(void*)*dim);
	return A;
}

void LinearFormSetCoordinates(struct LinearForm *A,void* (*Scan)())
{
	for (int i=0;i<A->dimension;i++)
	{
		A->coordinates[i] = Scan();
	}
}

struct LinearForm *LinearFormSum(struct LinearForm *A,struct LinearForm *B,void* (*Sum)(void*,void*))
{
	struct LinearForm *C;
	C = LinearFormCreate(A->dimension);
	for (int i=0;i<A->dimension;i++)
	{
		C->coordinates[i] = Sum(A->coordinates[i],B->coordinates[i]);
	}
	return C;
}

struct LinearForm *LinearFormMultiply(struct LinearForm *A,void *scalar,void* (*Multiply)(void*,void*))
{
	struct LinearForm *B;

	B = LinearFormCreate(A->dimension);
	for (int i=0;i<A->dimension;i++)
	{
		B->coordinates[i] = Multiply(A->coordinates[i],scalar);
	}
	return B;
}

void LinearFormDestruct(struct LinearForm* A,void (*Destruct)(void*))
{
	for (int i=0;i<A->dimension;i++)
	{
		Destruct(A->coordinates[i]);
	}
	free(A->coordinates);
	free(A);
}

void LinearFormPrint(struct LinearForm* A,void (*Print)(void*))
{
	for (int i=0;i<A->dimension-1;i++)
	{
		Print(A->coordinates[i]);
		printf("*x%d",i+1);
	}
	Print(A->coordinates[A->dimension-1]);
}

void* LinearFormArg(struct LinearForm* A,void* (*Scan)(),void* (*Multiply)(void*,void*),void* (*Sum)(void*,void*),
																			void* (*NeutralElemSum)(),void (*Destruct)(void*))
{
	void** Arguments[A->dimension-1];
	void * ResultSum = NeutralElemSum();
	void * BufferSum;
	void * BufferMultiply;
	for (int i=0;i<A->dimension-1;i++)
	{
		Arguments[i] = Scan();
		BufferMultiply = Multiply(Arguments[i],A->coordinates[i]);
		BufferSum = Sum(ResultSum,BufferMultiply);
		Destruct(Arguments[i]);
		Destruct(BufferMultiply);
		Destruct(ResultSum);
		ResultSum = BufferSum;
	}
	BufferSum = Sum(ResultSum,A->coordinates[A->dimension-1]);
	Destruct(ResultSum);
	ResultSum = BufferSum;
	return ResultSum;
}

unsigned int LinearFormGetDim(struct LinearForm* A)
{
	return A->dimension;
}
