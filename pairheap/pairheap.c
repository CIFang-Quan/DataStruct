#include "pairheap.h"

struct PairNode
{
    ElementType Element;
    Position LeftChild;
    Position NextSibling;
    Position Prev;
};

Position CompareAndLink(Position First, Position Second);
PairHeap CombineSiblings(Position FirstSibling);

PairHeap Initialize(void)
{
    return NULL;
}

PairHeap MakeEmpty(PairHeap H)
{
    if (H != NULL)
    {
        MakeEmpty(H->LeftChild);
        MakeEmpty(H->NextSibling);
        free(H);
    }
    return NULL;
}

PairHeap Insert(ElementType Item, PairHeap H, Position *Loc)
{
    Position NewNode;

    NewNode = malloc(sizeof(struct PairNode));
    if (NewNode == NULL)
    {
        FatalError("Out of space!!!");
    }
    NewNode->Element = Item;
    NewNode->LeftChild = NewNode->NextSibling = NULL;
    NewNode->Prev = NULL;

    *Loc = NewNode;
    if (H == NULL)
    {
        return NewNode;
    }
    else
    {
        return CompareAndLink(H, NewNode);
    }
}

PairHeap DecreaseKey(Position P, ElementType Delta, PairHeap H)
{
    if (Delta < 0)
    {
        Error("DecreaseKey called with negative Delta");
        return H;
    }
    P->Element -= Delta;
    if (P == H)
    {
        return H;
    }
    if (P->NextSibling != NULL)
    {
        P->NextSibling->Prev = P->Prev;
    }
    if (P->Prev != NULL)
    {
        if (P->Prev->LeftChild == P)
        {
            P->Prev->LeftChild = P->NextSibling;
        }
        else
        {
            P->Prev->NextSibling = P->NextSibling;
        }
    }
    P->NextSibling = NULL;
    return CompareAndLink(H, P);
}

PairHeap DeleteMin(ElementType *MinItem, PairHeap H)
{
    Position NewRoot = NULL;

    if (IsEmpty(H))
    {
        Error("Pairing heap is empty!");
    }
    else
    {
        *MinItem = H->Element;
        if (H->LeftChild != NULL)
        {
            NewRoot = CombineSiblings(H->LeftChild);
        }
        free(H);
    }
    return NewRoot;
}

Position CompareAndLink(Position First, Position Second)
{
    if (Second == NULL)
        return First;
    else if (First->Element <= Second->Element)
    {
        Second->Prev = First;
        First->NextSibling = Second->NextSibling;
        if (First->NextSibling != NULL)
        {
            First->NextSibling->Prev = First;
        }
        Second->NextSibling = First->LeftChild;
        if (Second->NextSibling != NULL)
        {
            Second->NextSibling->Prev = Second;
        }
        First->LeftChild = Second;
        return First;
    }
    else
    {
        Second->Prev = First->Prev;
        First->Prev = Second;
        First->NextSibling = Second->LeftChild;
        if (First->NextSibling != NULL)
        {
            First->NextSibling->Prev = First;
        }
        Second->LeftChild = First;
        return Second;
    }
}

PairHeap CombineSiblings(Position FirstSibling)
{
    int NumSiblings = 0;
    for (Position temp = FirstSibling; temp != NULL; temp = temp->NextSibling)
    {
        NumSiblings++;
    }

    Position *TreeArray = (Position *)malloc((NumSiblings + 1) * sizeof(Position));
    if (TreeArray == NULL)
    {
        FatalError("Out of space!!!");
    }

    int i, j;
    for (i = 0; FirstSibling != NULL; i++)
    {
        TreeArray[i] = FirstSibling;
        FirstSibling->Prev->NextSibling = NULL;
        FirstSibling = FirstSibling->NextSibling;
    }
    TreeArray[i] = NULL;

    for (i = 0; i + 1 < NumSiblings; i += 2)
    {
        TreeArray[i] = CompareAndLink(TreeArray[i], TreeArray[i + 1]);
    }
    j = i - 2;

    if (j == NumSiblings - 3)
    {
        TreeArray[j] = CompareAndLink(TreeArray[j], TreeArray[j + 2]);
    }

    for (; j >= 2; j -= 2)
    {
        TreeArray[j - 2] = CompareAndLink(TreeArray[j - 2], TreeArray[j]);
    }
    Position root = TreeArray[0];
    free(TreeArray);
    return root;
}

ElementType FindMin(PairHeap H)
{
    if (!IsEmpty(H))
    {
        return H->Element;
    }
    Error("Priority Queue is Empty");
    return 0;
}

int IsEmpty(PairHeap H)
{
    return H == NULL;
}

int IsFull(PairHeap H)
{
    return 0;
}

void Destroy(PairHeap H)
{
    MakeEmpty(H);
}
