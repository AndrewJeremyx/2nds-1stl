#ifndef LINEARFORM_H_
#define LINEARFORM_H_
struct LinearForm;
struct LinearForm *LinearFormCreate(unsigned int);
void LinearFormSetCoordinates(struct LinearForm *,void* (*Scan)());
unsigned int LinearFormGetDim(struct LinearForm*);
struct LinearForm *LinearFormSum(struct LinearForm*,struct LinearForm*,void* (*Sum)(void*,void*));
struct LinearForm *LinearFormMultiply(struct LinearForm *,void *,void* (*Multiply)(void*,void*));
void LinearFormDestruct(struct LinearForm*,void (*Destruct)(void*));
void LinearFormPrint(struct LinearForm*,void (*Print)(void*));
void* LinearFormArg(struct LinearForm*,void* (*Scan)(),void* (*Multiply)(void*,void*),void* (*Sum)(void*,void*),void* (*NeutralElemSum)(),void (*Destruct)(void*));
#endif
