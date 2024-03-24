#include "redblack.h"

typedef enum ColorType
{
    Red,
    Black
} ColorType;

struct RedBlackNode
{
    ElementType Element;
    RedBlackTree Parent;
    RedBlackTree Left;
    RedBlackTree Right;
    ColorType Color;
};

static Position NullNode = NULL;

RedBlackTree Initialize(void)
{
    RedBlackTree T;
    if (NullNode == NULL)
    {
        NullNode = malloc(sizeof(struct RedBlackNode));
        if (NullNode == NULL){
            FatalError("Out of space!!!");
        }
        NullNode->Left = NullNode->Right = NullNode;
        NullNode->Color = Black;
        NullNode->Element = 12345;
    }
    T = malloc(sizeof(struct RedBlackNode));
    if (T == NULL){
        FatalError("Out of space!!!");
    }
    T->Element = NegInfinity;
    T->Left = T->Right = NullNode;
    T->Color = Black;
    return T;
}

void Output(ElementType Element)
{
    printf("%d\n", Element);
}

static void DoPrint(RedBlackTree T)
{
    if (T != NullNode)
    {
        DoPrint(T->Left);
        Output(T->Element);
        DoPrint(T->Right);
    }
}

void PrintTree(RedBlackTree T)
{
    DoPrint(T->Right);
}

static RedBlackTree MakeEmptyRec(RedBlackTree T)
{
    if (T != NullNode)
    {
        MakeEmptyRec(T->Left);
        MakeEmptyRec(T->Right);
        free(T);
    }
    return NullNode;
}

RedBlackTree MakeEmpty(RedBlackTree T)
{
    T->Right = MakeEmptyRec(T->Right);
    return T;
}

Position Find(ElementType X, RedBlackTree T)
{
    if (T == NullNode){
        return NullNode;
    }
    if (X < T->Element){
        return Find(X, T->Left);
    }
    else if (X > T->Element){
        return Find(X, T->Right);
    }
    else{
        return T;
    }
}

Position FindMin(RedBlackTree T)
{
    T = T->Right;
    while (T->Left != NullNode){
        T = T->Left;
    }
    return T;
}

Position FindMax(RedBlackTree T)
{
    while (T->Right != NullNode){
        T = T->Right;
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

static Position Rotate(ElementType Item, Position Parent)
{

    if (Item < Parent->Element){
        return Parent->Left = Item < Parent->Left->Element ? SingleRotateWithLeft(Parent->Left) : SingleRotateWithRight(Parent->Left);
    }
    else{
        return Parent->Right = Item < Parent->Right->Element ? SingleRotateWithLeft(Parent->Right) : SingleRotateWithRight(Parent->Right);
    }
}

static void HandleReorient(ElementType Item, RedBlackTree T)
{
    Position X, P, GP, GGP;
    X->Color = Red;
    X->Left->Color = Black;
    X->Right->Color = Black;
    if (P->Color == Red)
    {
        GP->Color = Red;
        if ((Item < GP->Element) != (Item < P->Element)){
            P = Rotate(Item, GP);
        }
        X = Rotate(Item, GGP);
        X->Color = Black;
    }
    T->Right->Color = Black;
}

RedBlackTree Insert(ElementType Item, RedBlackTree T)
{
    Position X, P, GP, GGP;
    X = P = GP = T;
    NullNode->Element = Item;
    while (X->Element != Item)
    {
        GGP = GP;
        GP = P;
        P = X;
        if (Item < X->Element){
            X = X->Left;
        }
        else{
            X = X->Right;
        }
        if (X->Left->Color == Red && X->Right->Color == Red){
            HandleReorient(Item, T);
        }
    }
    if (X != NullNode){
        return NullNode;
    }
    X = malloc(sizeof(struct RedBlackNode));
    if (X == NULL){
        FatalError("Out of space!!!");
    }
    X->Element = Item;
    X->Left = X->Right = NullNode;
    if (Item < P->Element){
        P->Left = X;
    }
    else{
        P->Right = X;
    }
    X->Parent = P;
    HandleReorient(Item, T);
    return T;
}

void FixUp(RedBlackTree T, Position X) {
    while (X != T->Right && X->Color == Black) {
        if (X == X->Parent->Left) {
            Position W = X->Parent->Right;
            if (W->Color == Red) {
                W->Color = Black;
                X->Parent->Color = Red;
                SingleRotateWithLeft(X->Parent);
                W = X->Parent->Right;
            }
            if (W->Left->Color == Black && W->Right->Color == Black) {
                W->Color = Red;
                X = X->Parent;
            } else {
                if (W->Right->Color == Black) {
                    W->Left->Color = Black;
                    W->Color = Red;
                    SingleRotateWithRight(W);
                    W = X->Parent->Right;
                }
                W->Color = X->Parent->Color;
                X->Parent->Color = Black;
                W->Right->Color = Black;
                SingleRotateWithLeft(X->Parent);
                X = T->Right;
            }
        } else {
            Position W = X->Parent->Left;
            if (W->Color == Red) {
                W->Color = Black;
                X->Parent->Color = Red;
                SingleRotateWithRight(X->Parent);
                W = X->Parent->Left;
            }
            if (W->Right->Color == Black && W->Left->Color == Black) {
                W->Color = Red;
                X = X->Parent;
            } else {
                if (W->Left->Color == Black) {
                    W->Right->Color = Black;
                    W->Color = Red;
                    SingleRotateWithLeft(W);
                    W = X->Parent->Left;
                }
                W->Color = X->Parent->Color;
                X->Parent->Color = Black;
                W->Left->Color = Black;
                SingleRotateWithRight(X->Parent);
                X = T->Right;
            }
        }
    }
    X->Color = Black;
}

Position DeleteNode(RedBlackTree T, ElementType Item, Position X) {
    if (X == NullNode) return NullNode; // Item not found, do nothing

    if (Item < X->Element) {
        X->Left = DeleteNode(T, Item, X->Left);
    } else if (Item > X->Element) {
        X->Right = DeleteNode(T, Item, X->Right);
    } else if (X->Left != NullNode && X->Right != NullNode) { // Two children
        Position Y = FindMin(X->Right);
        X->Element = Y->Element;
        X->Right = DeleteNode(T, Y->Element, X->Right);
    } else {
        Position temp = X;
        X = (X->Left != NullNode) ? X->Left : X->Right;
        if (T->Right == temp) {
            T->Right = X;
        }
        free(temp);
    }
    if (X != NullNode) {
        FixUp(T, X);
    }
    return X;
}

RedBlackTree Remove(ElementType Item, RedBlackTree T) {
    if (T == NullNode){
        return T;
    }
    T->Right = DeleteNode(T, Item, T->Right);
    if (T->Right != NullNode){
        T->Right->Color = Black;
    }
    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}
