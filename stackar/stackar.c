#include "stackar.h"

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

int IsEmpty(Stack S)
{
    return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
    return S->TopOfStack == S->Capacity - 1;
}

Stack CreateStack(int MaxElements)
{
    Stack S;
    if (MaxElements < 3){
        Error("Stack size is too small");
    }
    S = malloc(sizeof(struct StackRecord));
    if (S == NULL){
        FatalError("Out of space!!!");
    }
    S->Array = malloc(sizeof(ElementType) * MaxElements);
    if (S->Array == NULL){
        FatalError("Out of space!!!");
    }
    S->Capacity = MaxElements;
    MakeEmpty(S);

    return S;
}

void MakeEmpty(Stack S)
{
    S->TopOfStack = EmptyTOS;
}

void DisposeStack(Stack S)
{
    if (S != NULL)
    {
        free(S->Array);
        free(S);
    }
}

void Push(ElementType X, Stack S)
{
    if (IsFull(S)){
        Error("Full stack");
    }
    else{
        S->Array[++S->TopOfStack] = X;
    }
}

ElementType Top(Stack S)
{
    if (!IsEmpty(S)){
        return S->Array[S->TopOfStack];
    }
    Error("Empty stack");
    return 0;
}

void Pop(Stack S)
{
    if (IsEmpty(S)){
        Error("Empty stack");
    }
    else{
        S->TopOfStack--;
    }
}

ElementType
TopAndPop(Stack S)
{
    if (!IsEmpty(S)){
        return S->Array[S->TopOfStack--];
    }
    Error("Empty stack");
    return 0;
}
