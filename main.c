#include <stdio.h>
#include <stdlib.h>
#include "int.h"
#include "linearform.h"
#include "float.h"
#include "linearspace.h"
unsigned int ScanSymbol()   //Scan Symbol and return index('A'=0,'B'=1,...)
{   
    char Symbol[2];
    scanf("%s",Symbol);
    return (unsigned int)(*Symbol-'A'); 
}

void MenuCreate(struct LinearSpace *Space,void* (*Scan)())    
{
    unsigned int dim;
    scanf("%u",&dim);
    struct LinearForm *A = LinearFormCreate(dim);
    SpaceNewForm(Space);
    LinearFormSetCoordinates(A,Scan);
    SpaceFillForm(Space,A);
}

void MenuSum(struct LinearSpace *Space,void* (*Sum)(void*,void*))
{
    unsigned int a,b; 

    a = ScanSymbol();
    b = ScanSymbol();

    if (a < SpaceGetLen(Space) && b < SpaceGetLen(Space) && LinearFormGetDim(SpaceGetForm(Space,b)) == LinearFormGetDim(SpaceGetForm(Space,b)))
    {
        SpaceNewForm(Space);
        struct LinearForm *A = LinearFormSum(SpaceGetForm(Space,a),SpaceGetForm(Space,b),Sum);
        SpaceFillForm(Space,A);
    }
    else if (LinearFormGetDim(SpaceGetForm(Space,a)) != LinearFormGetDim(SpaceGetForm(Space,b)))
        printf("Error.Dimension Error\n");
    else 
        printf("Error.WrongVectorName\nExample: Summa A B\n");
}

void MenuMultiply(struct LinearSpace *Space,void* (*Multiply)(void*,void*),void* (*Scan)(),void (*Destruct)(void*))
{
    unsigned int a;
    void * scalar;
   
    a = ScanSymbol();

    if (a < SpaceGetLen(Space))
    {
        SpaceNewForm(Space);
        scalar = Scan();
        struct LinearForm *A = LinearFormMultiply(SpaceGetForm(Space,a),scalar,Multiply);
        SpaceFillForm(Space,A);
        Destruct(scalar);
    }
    else
        printf("Error.WrongVectorName\nExample: Multiply A 2\n");
}

void MenuPrint(struct LinearSpace *Space,void (*Print)(void*))
{
    unsigned int a;
    
    a = ScanSymbol();

    if (a < SpaceGetLen(Space))
    {
        LinearFormPrint(SpaceGetForm(Space,a),Print);
        printf("\n");
    }
    else 
        printf("Error.WrongVectorName\nExample: PrintOne A\n");
}

void MenuPrintAll(struct LinearSpace *Space,void (*Print)(void*))
{
    for(int i =0;i<SpaceGetLen(Space);i++)
    {
        printf("%c %2u   ",'A'+i,LinearFormGetDim(SpaceGetForm(Space,i)));
        LinearFormPrint(SpaceGetForm(Space,i),Print);
        printf("\n");
    }
}

void MenuPrintArg(struct LinearSpace *Space,void* (*Scan)(),void* (*Multiply)(void*,void*),void* (*Sum)(void*,void*),
                                                void* (*NeutralElemSum)(),void (*Print)(void*),void (*Destruct)(void*))
{
    unsigned int a;
    void* Result;
    
    a = ScanSymbol();

    if (a < SpaceGetLen(Space))
    {
        Result = LinearFormArg(SpaceGetForm(Space,a),Scan,Multiply,Sum,NeutralElemSum,Destruct);
        Print(Result);
        Destruct(Result);
        printf("\n");
    }
    else 
        printf("Error.WrongVectorName\nExample: PrintArg A\n");
}


int StrEqual(char *A,char *B,unsigned int len)  // Boolean Function that determine equality of strings
{
    for (int i = 0;i<len;++i)
    {
        if(A[i]!=B[i])
            return 0;
    }
    return 1;
}
int main()
{
   struct LinearSpace* Space = SpaceCreate();
   char choose[10];
   
   void* (*Sum)(void*,void*) = IntSum;
   void* (*Scan)() = IntScan;
   void* (*Multiply)(void*,void*) = IntMultiplication;
   void (*Print)(void*) = IntPrint;
   void* (*NeutralElemSum)() = IntNeutralElemSum;
   void (*Destruct)(void*) = IntDestruct;
   
   printf("Choose Mode: Float or Int\n");
   scanf("%s",choose);
   if (StrEqual(choose,"Float",5))
    {
        Sum = FloatSum;
        Scan= FloatScan;
        Multiply= FloatMultiplication;
        Print= FloatPrint;
        NeutralElemSum = FloatNeutralElemSum;
        Destruct = FloatDestruct;
    }
    while (!StrEqual(choose,"Exit",4))
    {
        printf(">");
        scanf("%s",choose);
        if (StrEqual(choose,"Create",6))
            MenuCreate(Space,Scan);
        else if (StrEqual(choose,"Summa",5))
            MenuSum(Space,Sum);
        else if (StrEqual(choose,"Multiply",8))
            MenuMultiply(Space,Multiply,Scan,Destruct);
        else if (StrEqual(choose,"PrintOne",8))
            MenuPrint(Space,Print);
        else if (StrEqual(choose,"PrintAll",8))
            MenuPrintAll(Space,Print);
        else if (StrEqual(choose,"PrintArg",8))
            MenuPrintArg(Space,Scan,Multiply,Sum,NeutralElemSum,Print,Destruct);
        else if (StrEqual(choose,"Exit",4))
            printf("Good Bye\n");
        else if (StrEqual(choose,"Help",4))
        {
            printf("Create [dimension] [0] [1] ... [dimension-1]\n");
            printf("Summa [form1] [form2]\n");
            printf("Multiply [form] [scalar]\n");
            printf("PrintOne [form]\n");
            printf("PrintAll\n");
            printf("PrintArg [form] [0] [1] ... [dimension-2]\n");
            printf("Exit\n");
        }
        else 
            printf("Error. Unknown command(use Help)\n");
    }
    SpaceDestruct(Space,Destruct);
    return 0;
}
