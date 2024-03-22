#include "treap.h"

struct TreapNode
{
    ElementType Element;
    Treap Left;
    Treap Right;
    int Priority;
};

Position NullNode = NULL;

Treap Initialize(void)
{
    if (NullNode == NULL)
    {
        NullNode = malloc(sizeof(struct TreapNode));
        if (NullNode == NULL)
        {
            FatalError("Out of space!!!");
        }
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Priority = Infinity;
    }
    return NullNode;
}

int Random(void)
{
    return rand() - 1;
}

Treap MakeEmpty(Treap T)
{
    if (T != NullNode)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NullNode;
}

void PrintTree(Treap T)
{
    if (T != NullNode)
    {
        PrintTree(T->Left);
        printf("%d ", T->Element);
        PrintTree(T->Right);
    }
}

Position Find(ElementType X, Treap T)
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

PositionFindMin(Treap T)
{
    if (T == NullNode)
    {
        return NullNode;
    }
    else if (T->Left == NullNode)
    {
        return T;
    }
    else
    {
        return FindMin(T->Left);
    }
}

PositionFindMax(Treap T)
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

Treap Insert(ElementType Item, Treap T)
{
    if (T == NullNode)
    {
        T = malloc(sizeof(struct TreapNode));
        if (T == NULL)
        {
            FatalError("Out of space!!!");
        }
        else
        {
            T->Element = Item;
            T->Priority = Random();
            T->Left = T->Right = NullNode;
        }
    }
    else if (Item < T->Element)
    {
        T->Left = Insert(Item, T->Left);
        if (T->Left->Priority < T->Priority)
        {
            T = SingleRotateWithLeft(T);
        }
    }
    else if (Item > T->Element)
    {
        T->Right = Insert(Item, T->Right);
        if (T->Right->Priority < T->Priority)
        {
            T = SingleRotateWithRight(T);
        }
    }
    return T;
}

Treap Remove(ElementType Item, Treap T)
{
    if (T != NullNode)
    {
        if (Item < T->Element)
        {
            T->Left = Remove(Item, T->Left);
        }
        else if (Item > T->Element)
        {
            T->Right = Remove(Item, T->Right);
        }
        else
        {
            if (T->Left->Priority < T->Right->Priority)
            {
                T = SingleRotateWithLeft(T);
            }
            else
            {
                T = SingleRotateWithRight(T);
            }
            if (T != NullNode)
            {
                T = Remove(Item, T);
            }
            else
            {
                free(T->Left);
                T->Left = NullNode;
            }
        }
    }
    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}
