#include "aatree.h"
#include <stdlib.h>
#include "fatal.h"

Position NullNode = NULL;

struct AANode
{
    ElementType Element;
    AATree Left;
    AATree Right;
    int Level;
};

AATree Initialize(void)
{
    if (NullNode == NULL)
    {
        NullNode = malloc(sizeof(struct AANode));
        if (NullNode == NULL)
        {
            FatalError("Out of space!!!");
        }
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Level = 0;
    }
    return NullNode;
}

AATree MakeEmpty(AATree T)
{
    if (T != NullNode)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NullNode;
}

Position Find(ElementType X, AATree T)
{
    if (T == NullNode)
    {
        return NullNode;
    }
    if (X < T->Element)
    {
        return Find(X, T->Left);
    }
    else if (X > T->Element)
    {
        return Find(X, T->Right);
    }
    else
    {
        return T;
    }
}

Position FindMin(AATree T)
{
    if (T != NullNode)
    {
        while (T->Left != NullNode)
        {
            T = T->Left;
        }
    }
    return T;
}

Position FindMax(AATree T)
{
    if (T != NullNode)
    {
        while (T->Right != NullNode)
        {
            T = T->Right;
        }
    }
    return T;
}

static Position SingleRotateWithLeft(Position K2)
{
    Position K1;
    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;
    return K1;
}

static Position SingleRotateWithRight(Position K1)
{
    Position K2;
    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;
    return K2;
}

AATree Skew(AATree T)
{
    if (T->Left->Level == T->Level)
    {
        T = SingleRotateWithLeft(T);
    }
    return T;
}

AATree Split(AATree T)
{
    if (T->Right->Right->Level == T->Level)
    {
        T = SingleRotateWithRight(T);
        T->Level++;
    }
    return T;
}

AATree Insert(ElementType Item, AATree T) {
    if (T == NullNode) {
        T = malloc(sizeof(struct AANode));
        if (T == NULL) {
            FatalError("Out of space!!!");
        }
        T->Element = Item;
        T->Level = 1;
        T->Left = T->Right = NullNode;
    }
    else {
        if (Item < T->Element) {
            T->Left = Insert(Item, T->Left);
        } else if (Item > T->Element) {
            T->Right = Insert(Item, T->Right);
        }
    }
    T = Skew(T);
    T = Split(T);
    return T;
}


AATree Remove(ElementType Item, AATree T)
{
    static Position DeletePtr, LastPtr;
    if (T != NullNode)
    {
        LastPtr = T;
        if (Item < T->Element)
        {
            T->Left = Remove(Item, T->Left);
        }
        else
        {
            DeletePtr = T;
            T->Right = Remove(Item, T->Right);
        }
        if (T == LastPtr)
        {
            if (DeletePtr != NullNode && Item == DeletePtr->Element)
            {
                DeletePtr->Element = T->Element;
                DeletePtr = NullNode;
                T = T->Right;
                free(LastPtr);
            }
        }
        else if (T->Left->Level < T->Level - 1 || T->Right->Level < T->Level - 1)
        {
            if (T->Right->Level > --T->Level)
            {
                T->Right->Level = T->Level;
            }
            T = Skew(T);
            T->Right = Skew(T->Right);
            T->Right->Right = Skew(T->Right->Right);
            T = Split(T);
            T->Right = Split(T->Right);
        }
    }
    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}
