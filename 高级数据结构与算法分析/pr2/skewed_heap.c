#include<stdio.h>
#include<stdlib.h>

typedef struct SKHeap *SKHeapPtr;
struct SKHeap {
    int value;
    SKHeapPtr leftHeap;
    SKHeapPtr rightHeap;
};

SKHeapPtr build(int value);
SKHeapPtr insert(SKHeapPtr heap, int value);
SKHeapPtr merge(SKHeapPtr tarHeap, SKHeapPtr objHeap);
SKHeapPtr deletemin(SKHeapPtr heap, int value);

/*
void test(void);


int main() {
    test();
}

void test() {
    int num, value, i;
    SKHeapPtr heap;

    scanf("%d", &num);
    for(i=0; i<num; i++) {
        scanf("%d", &value);
        heap = insert(heap, value);
    }
    scanf("%d", &num);
    for(i=0; i<num; i++) {
        scanf("%d", &value);
        heap = delete(heap, value);
    }
}
*/

SKHeapPtr build(int value) {
    SKHeapPtr heap = (SKHeapPtr)malloc(sizeof(struct SKHeap));
    heap->leftHeap = NULL;
    heap->rightHeap = NULL;
    heap->value = value; //the value of initial root
    return heap;
}

//insertion is merging a heap with a new heap with only one element
SKHeapPtr insert(SKHeapPtr heap, int value) {
    SKHeapPtr newHeap = build(value);
    return merge(heap, newHeap); 
}

SKHeapPtr merge(SKHeapPtr tarHeap, SKHeapPtr objHeap) {
    SKHeapPtr newHeap, tempHeap;
    if(tarHeap == NULL) {
        return objHeap;
    } else if(objHeap == NULL) {
        return tarHeap; //handle the condition that one of the hep is empty
    } else {
        if(tarHeap->value > objHeap->value) {
            tempHeap = tarHeap;
            tarHeap = objHeap;
            objHeap = tempHeap;
        }// switch two heaps if the root of target heap is bigger trahn objected one
        newHeap = tarHeap->rightHeap;
        tarHeap->rightHeap = tarHeap->leftHeap; //reverse right and left heap
        tarHeap->leftHeap = merge(newHeap, objHeap); //recursively merging
        return tarHeap;
    }
}

SKHeapPtr deletemin(SKHeapPtr heap, int value) {
    return merge(heap->leftHeap, heap->rightHeap); //delete the root and merge its children    
}