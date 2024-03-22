#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

#ifndef _LeftHeap_H
#define _LeftHeap_H

struct TreeNode;
typedef struct TreeNode *PriorityQueue;

PriorityQueue Initialize(void);
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);
PriorityQueue Insert(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin(PriorityQueue H);

#endif
