#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
struct Node {
    ElementType Element;
    Position Next;
};

List Read(); /* details omitted */
void Print( List L ); /* details omitted */
List Reverse( List L );

int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}

/* Your function will be put here */
List Reverse( List L ){
    List head = L->Next;
    List p = head->Next;
    List q = head;
    
    if (head == NULL || p == NULL){
        return L;
    }
    
    
    while(p){
        q->Next = p->Next;
        p->Next = head;
        head = p;
        p = q->Next;
    }
    L->Next = head;
    return L;
}