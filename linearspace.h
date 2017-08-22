#ifndef LINEARSPACE_H_   
#define LINEARSPACE_H_
struct LinearSpace;
struct LinearSpace *SpaceCreate();
void SpaceNewForm(struct LinearSpace*);
void SpaceFillForm(struct LinearSpace*,struct LinearForm *);
struct LinearForm* SpaceGetForm(struct LinearSpace*,unsigned int);
unsigned int SpaceGetLen(struct LinearSpace *);
void SpaceDestruct(struct LinearSpace*,void (*Destruct)(void*));
#endif
