#include "hashsep.h"

struct ListNode
{
    ElementType Element;
    Position Next;
};

typedef Position List;

struct HashTbl
{
    int TableSize;
    List *TheLists;
};

static int NextPrime(int N)
{
    int i;
    if (N % 2 == 0)
    {
        N++;
    }
    for (;; N += 2)
    {
        for (i = 3; i * i <= N; i += 2)
            if (N % i == 0)
            {
                break;
            }
        if (N % i == 0)
        {
            continue;
        }
        return N;
    }
}

Index Hash(ElementType Key, int TableSize)
{
    return Key % TableSize;
}

HashTable InitializeTable(int TableSize)
{
    HashTable H;
    int i;
    if (TableSize < 3)
    {
        Error("Table size too small");
        return NULL;
    }
    H = malloc(sizeof(struct HashTbl));
    if (H == NULL)
    {
        FatalError("Out of space!!!");
    }
    H->TableSize = NextPrime(TableSize);
    H->TheLists = malloc(sizeof(List) * H->TableSize);
    if (H->TheLists == NULL)
    {
        FatalError("Out of space!!!");
    }
    for (i = 0; i < H->TableSize; i++)
    {
        H->TheLists[i] = malloc(sizeof(struct ListNode));
        if (H->TheLists[i] == NULL)
        {
            FatalError("Out of space!!!");
        }
        else
        {
            H->TheLists[i]->Next = NULL;
        }
    }
    return H;
}

Position Find(ElementType Key, HashTable H)
{
    Position P;
    List L;
    L = H->TheLists[Hash(Key, H->TableSize)];
    P = L->Next;
    while (P != NULL && P->Element != Key)
    {
        P = P->Next;
    }
    return P;
}

void Insert(ElementType Key, HashTable H)
{
    Position Pos, NewCell;
    List L;
    Pos = Find(Key, H);
    if (Pos == NULL)
    {
        NewCell = malloc(sizeof(struct ListNode));
        if (NewCell == NULL)
        {
            FatalError("Out of space!!!");
        }
        else
        {
            L = H->TheLists[Hash(Key, H->TableSize)];
            NewCell->Next = L->Next;
            NewCell->Element = Key;
            L->Next = NewCell;
        }
    }
}

ElementType Retrieve(Position P)
{
    return P->Element;
}

void DestroyTable(HashTable H)
{
    int i;
    for (i = 0; i < H->TableSize; i++)
    {
        Position P = H->TheLists[i];
        Position Tmp;
        while (P != NULL)
        {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->TheLists);
    free(H);
}
