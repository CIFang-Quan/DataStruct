#include "tree.h"
#include <stdlib.h>
#include "fatal.h"

struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T)
{
    if (T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T)
{
    if (T == NULL)
    {
        return NULL;
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

Position FindMin(SearchTree T)
{
    if (T == NULL)
    {
        return NULL;
    }
    while (T->Left != NULL)
    {
        T = T->Left;
    }
    return T;
}

Position FindMax(SearchTree T)
{
    if (T != NULL)
    {
        while (T->Right != NULL)
        {
            T = T->Right;
        }
    }
    return T;
}

SearchTree Insert(ElementType X, SearchTree T)
{
    Position temp = malloc(sizeof(struct TreeNode));
    if (temp == NULL)
    {
        FatalError("Out of space!!!");
    }
    temp->Element = X;
    temp->Left = temp->Right = NULL;

    if (T == NULL)
    {
        return temp;
    }

    Position current = T;
    Position parent = NULL;
    while (current != NULL)
    {
        parent = current;
        if (X < current->Element)
        {
            current = current->Left;
        }
        else if (X > current->Element)
        {
            current = current->Right;
        }
        else
        {
            // Element already exists, no need to insert a duplicate, free allocated memory
            free(temp);
            return T;
        }
    }

    if (X < parent->Element)
    {
        parent->Left = temp;
    }
    else
    {
        parent->Right = temp;
    }

    return T;
}

SearchTree Delete(ElementType X, SearchTree T)
{
    Position current = T;
    Position parent = NULL;
    while (current != NULL && current->Element != X)
    {
        parent = current;
        if (X < current->Element)
        {
            current = current->Left;
        }
        else if (X > current->Element)
        {
            current = current->Right;
        }
    }

    if (current == NULL)
    {
        Error("Element not found");
        return T; // Element X not found in the tree
    }

    // Node with only one child or no child
    if (current->Left == NULL || current->Right == NULL)
    {
        Position newCurr;
        if (current->Left == NULL)
            newCurr = current->Right;
        else
            newCurr = current->Left;

        if (parent == NULL)
            return newCurr;

        if (current == parent->Left)
            parent->Left = newCurr;
        else
            parent->Right = newCurr;

        free(current);
    }
    else
    {
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Position successor = current->Right;
        Position successorParent = current;
        while (successor->Left != NULL)
        {
            successorParent = successor;
            successor = successor->Left;
        }

        current->Element = successor->Element; // Copy the inorder successor's content to this node

        // Delete the inorder successor
        if (successorParent != current)
            successorParent->Left = successor->Right;
        else
            successorParent->Right = successor->Right;

        free(successor);
    }

    return T;
}

ElementType Retrieve(Position P)
{
    return P->Element;
}
