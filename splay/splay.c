#include "splay.h"

struct SplayNode
{
    ElementType Element;
    SplayTree Left;
    SplayTree Right;
};

typedef struct SplayNode *Position;
static Position NullNode = NULL;

SplayTree Initialize(void)
{
    if (NullNode == NULL)
    {
        NullNode = malloc(sizeof(struct SplayNode));
        if (NullNode == NULL)
        {
            FatalError("Out of space!!!");
        }
        NullNode->Left = NullNode->Right = NullNode;
    }
    return NullNode;
}

static SplayTree Splay(ElementType Item, Position X);

SplayTree MakeEmpty(SplayTree T)
{
    if (T != NullNode)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NullNode;
}

void PrintTree(SplayTree T)
{
    if (T != NullNode)
    {
        PrintTree(T->Left);
        printf("%d ", T->Element);
        PrintTree(T->Right);
    }
}

SplayTree Find(ElementType X, SplayTree T)
{
    return Splay(X, T);
}

SplayTree FindMin(SplayTree T)
{
    return Splay(NegInfinity, T);
}

SplayTree FindMax(SplayTree T)
{
    return Splay(Infinity, T);
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

SplayTree Splay(ElementType Item, Position X)
{
    static struct SplayNode Header;
    Position LeftTreeMax, RightTreeMin;
    Header.Left = Header.Right = NullNode;
    LeftTreeMax = RightTreeMin = &Header;
    NullNode->Element = Item;
    while (Item != X->Element)
    {
        if (Item < X->Element)
        {
            if (Item < X->Left->Element)
            {
                X = SingleRotateWithLeft(X);
            }
            if (X->Left == NullNode)
            {
                break;
            }
            RightTreeMin->Left = X;
            RightTreeMin = X;
            X = X->Left;
        }
        else
        {
            if (Item > X->Right->Element)
            {
                X = SingleRotateWithRight(X);
            }
            if (X->Right == NullNode)
            {
                break;
            }
            LeftTreeMax->Right = X;
            LeftTreeMax = X;
            X = X->Right;
        }
    }
    LeftTreeMax->Right = X->Left;
    RightTreeMin->Left = X->Right;
    X->Left = Header.Right;
    X->Right = Header.Left;
    return X;
}

SplayTree Insert(ElementType Item, SplayTree T)
{
    static Position NewNode = NULL;
    if (NewNode == NULL)
    {
        NewNode = malloc(sizeof(struct SplayNode));
        if (NewNode == NULL)
        {
            FatalError("Out of space!!!");
        }
    }
    NewNode->Element = Item;
    if (T == NullNode)
    {
        NewNode->Left = NewNode->Right = NullNode;
        T = NewNode;
    }
    else
    {
        T = Splay(Item, T);
        if (Item < T->Element)
        {
            NewNode->Left = T->Left;
            NewNode->Right = T;
            T->Left = NullNode;
            T = NewNode;
        }
        else if (T->Element < Item)
        {
            NewNode->Right = T->Right;
            NewNode->Left = T;
            T->Right = NullNode;
            T = NewNode;
        }
        else
        {
            return T;
        }
    }
    NewNode = NULL;
    return T;
}

SplayTree Remove(ElementType Item, SplayTree T)
{
    Position NewTree;
    if (T != NullNode)
    {
        T = Splay(Item, T);
        if (Item == T->Element)
        {
            if (T->Left == NullNode)
            {
                NewTree = T->Right;
            }
            else
            {
                NewTree = T->Left;
                NewTree = Splay(Item, NewTree);
                NewTree->Right = T->Right;
            }
            free(T);
            T = NewTree;
        }
    }

    return T;
}

ElementType Retrieve(SplayTree T)
{
    return T->Element;
}
