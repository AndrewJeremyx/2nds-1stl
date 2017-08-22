#include <stdio.h>
#include <stdlib.h>
#include "linearform.h"

struct LinearSpace
{
	struct LinearForm ** forms;
	unsigned int len;
};

struct LinearSpace *SpaceCreate()
{
	struct LinearSpace* A = (struct LinearSpace*)malloc (sizeof(struct LinearSpace));
	A->len = 0;
	A->forms = NULL;
	return A;
}

unsigned int SpaceGetLen(struct LinearSpace *A)
{
	return A->len;
}

void SpaceNewForm(struct LinearSpace *A)
{
	++(A->len);
	A->forms = (struct LinearForm**)realloc(A->forms,(A->len)*sizeof(struct LinearForm*));
}

void SpaceFillForm(struct LinearSpace *A,struct LinearForm *B)
{
	A->forms[A->len-1] = B;
	printf("LinearForm saved in %c\n",A->len-1 + 'A');
}
struct LinearForm* SpaceGetForm(struct LinearSpace *A,unsigned int index)
{
	return A->forms[index];
}

void SpaceDestruct(struct LinearSpace *A,void (*Destruct)(void*))
{
	for (int i=0;i<A->len;i++)
	{
		LinearFormDestruct(A->forms[i],Destruct);
	}
	free(A->forms);
	free(A);
}
