#include "dskipl.h"

typedef int ElementType;

struct SkipNode
{
    ElementType Element;
    struct SkipNode *Right;
    struct SkipNode *Down;
};

static struct SkipNode *NewNode(ElementType Elem, struct SkipNode *Right, struct SkipNode *Down)
{
    struct SkipNode *Node = (struct SkipNode *)malloc(sizeof(struct SkipNode));
    if (Node == NULL)
    {
        FatalError("Out of space!!!");
    }
    Node->Element = Elem;
    Node->Right = Right;
    Node->Down = Down;
    return Node;
}

SkipList Initialize(void)
{
    Position Tail = NewNode(Infinity, NULL, NULL);
    SkipList L = Tail;
    for (int i = 0; i < MAX_LEVEL; ++i)
    {
        L = NewNode(Infinity, Tail, L);
    }
    return L;
}

int RandomLevel(void)
{
    int lvl = 1;
    while (rand() % 2 && lvl < MAX_LEVEL)
    {
        lvl++;
    }
    return lvl;
}

SkipList Insert(ElementType Item, SkipList L)
{
    Position Current = L;
    Position Updates[MAX_LEVEL];
    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        while (Current->Right->Element < Item)
        {
            Current = Current->Right;
        }
        Updates[i] = Current;
        if (i > 0)
        {
            Current = Current->Down;
        }
    }
    int Level = RandomLevel();
    Position New = NULL;
    for (int i = 0; i < Level; i++)
    {
        New = NewNode(Item, Updates[i]->Right, New);
        Updates[i]->Right = New;
    }
    return L;
}

Position Find(ElementType Item, SkipList L)
{
    Position Current = L;
    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        while (Current->Right->Element < Item)
        {
            Current = Current->Right;
        }
        if (i > 0)
            Current = Current->Down;
    }
    if (Current->Right->Element == Item)
    {
        return Current->Right;
    }
    return NULL;
}

Position FindMin(SkipList L)
{
    Position P = L;
    while (P->Down != NULL)
    {
        P = P->Down;
    }
    if (P->Right && P->Right->Element != Infinity)
    {
        return P->Right;
    }
    return NULL;
}

Position FindMax(SkipList L)
{
    Position P = L;
    while (P->Down != NULL)
    {
        P = P->Down;
    }
    while (P->Right && P->Right->Element != Infinity)
    {
        P = P->Right;
    }
    if (P->Element != Infinity)
    {
        return P;
    }
    return NULL;
}

SkipList Remove(ElementType Item, SkipList L)
{
    Position Current = L, Temp;
    int found = 0;
    for (int i = MAX_LEVEL - 1; i >= 0; i--)
    {
        while (Current->Right != NULL && Current->Right->Element < Item)
        {
            Current = Current->Right;
        }
        if (Current->Right != NULL && Current->Right->Element == Item)
        {
            found = 1;
            Temp = Current->Right;
            Current->Right = Temp->Right;
            if (i == 0)
                free(Temp);
        }
        if (i > 0)
            Current = Current->Down;
    }
    if (!found)
        printf("Item not found.\n");
    return L;
}

void Destroy(SkipList L)
{
    Position P, Temp;
    while (L != NULL)
    {
        P = L->Right;
        while (P != NULL)
        {
            Temp = P->Right;
            free(P);
            P = Temp;
        }
        Temp = L;
        L = L->Down;
        free(Temp);
    }
}