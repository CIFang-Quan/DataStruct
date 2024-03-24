#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define Infinity 1 << 30

#ifndef _SkipList_H
#define _SkipList_H

#define MAX_LEVEL 1 << 2
struct SkipNode;
typedef struct SkipNode *Position;
typedef struct SkipNode *SkipList;

SkipList Initialize(void);
int RandomLevel(void);
SkipList Insert(ElementType Item, SkipList L);
Position Find(ElementType Item, SkipList L);
Position FindMin(SkipList L);
Position FindMax(SkipList L);
SkipList Remove(ElementType Item, SkipList L);
void Destroy(SkipList L);

#endif
