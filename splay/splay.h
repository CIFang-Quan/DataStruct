#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define Infinity 1 << 30
#define NegInfinity -1 << 30

#ifndef _Splay_H
#define _Splay_H

struct SplayNode;
typedef struct SplayNode *SplayTree;

SplayTree MakeEmpty(SplayTree T);
SplayTree Find(ElementType X, SplayTree T);
SplayTree FindMin(SplayTree T);
SplayTree FindMax(SplayTree T);
SplayTree Initialize(void);
SplayTree Insert(ElementType X, SplayTree T);
SplayTree Remove(ElementType X, SplayTree T);
ElementType Retrieve(SplayTree T);

#endif
