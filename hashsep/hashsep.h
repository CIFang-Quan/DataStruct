#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef unsigned int Index;

#ifndef _HashSep_H
#define _HashSep_H

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);

#endif
