#include "heaps.h"
#include <iostream>

#define infinity 100000

using namespace std;


BinNode* BinNode:: merge(BinNode* T1, BinNode* T2) {//case����ȷ��T1,T2�ǿ�

	if (T1->Element > T2->Element)
		return merge(T2, T1);
	T2->NextSibling = T1->LeftChild;
	T1->LeftChild = T2;
}
BinNode* BinNode:: Search(BinNode* T, int X) {
	BinNode* result = NULL;
	if (X == T->Element)return T;
	if (T->LeftChild != NULL) {
		result = Search(T->LeftChild, X);
		if (result != NULL)return result;
	}
	if (T->NextSibling != NULL) {
		result = Search(T->NextSibling, X);
		return result;
	}
}

BinTrees* BinTrees:: InserBinHeap(BinTrees* T, int X) {
	BinNode p;
	p.Element = X;
	BinTrees A;
	A.Trees[0] = &p;
	A.Size = 1;
	T->MergeBinHeap(T, &A);
	free(&A);
	free(&p);
	return T;
}
BinTrees* BinTrees:: MergeBinHeap(BinTrees* T1, BinTrees* T2) {
	BinNode *S1, *S2, *Carry = NULL;//carry��ʾ��λ
	T1->Size += T2->Size;
	int i, j;
	for (i = 0, j = 1; j <= T1->Size; i++, j *= 2) {
		S1 = T1->Trees[i];
		S2 = T2->Trees[i];
		switch (4 * !!Carry + 2 * !!S2 + !!S1) {//��Ҫ�Ǳ���ĸ��Ƿǿ�
			case 0://000
			case 1://001
				break;
			case 2://010
				T1->Trees[i] = S2;
				T2->Trees[i] = NULL;
				break;
			case 3://011
				T1->Trees[i] = NULL;
				T2->Trees[i] = NULL;
				Carry = S1->merge(S1, S2);
				break;
			case 4://100
				T1->Trees[i] = Carry;
				Carry = NULL;
				break;
			case 5://101
				T1->Trees[i] = S1->merge(S1, Carry);
				Carry = NULL;
				break;
			case 6://110
				T1->Trees[i] = S2->merge(S2, Carry);
				Carry = NULL;
				T2->Trees[i] = NULL;
				break;
			case 7://111
				T1->Trees[i] = S2->merge(S2, S1);
				T2->Trees[i] = NULL;
				break;
		}
	}
	return T1;
}
int BinTrees:: DeleteMinBinHeap(BinTrees* T) {
	BinTrees DTS;//ɾ��Min�������γ��µĶ������
	BinNode *S, *OldRoot;
	int min = infinity;
	int i, j, point;
	if (T == NULL || T->Size == 0) {//TΪ��
		return -infinity;
	}
	for (i = 0, j = 1; j < T->Size; i++, j *= 2) {
		if (T->Trees[i] && T->Trees[i]->Element < min) {
			min = T->Trees[i]->Element;
			point = i;
		}
	}
	S = T->Trees[point];
	T->Trees[point] = NULL;
	OldRoot = S;
	S = S->LeftChild;
	free(OldRoot);

	DTS.Size = (1 << point) - 1;
	for (j = point - 1; j >= 0; j--) {
		DTS.Trees[j] = S;
		S = S->NextSibling;
		DTS.Trees[j]->NextSibling = NULL;
	}
	T->Size -= DTS.Size + 1;
	T = T->MergeBinHeap(T, &DTS);
	return min;
}
BinNode* BinTrees:: SearchBinHeap(BinTrees* T, int X) {
	BinNode* S;
	BinNode* result = NULL;
	int i, j;

	for (i = 0, j = 1; j <= T->Size; i++, j *= 2) {  /* for each tree in H */
		S = T->Trees[i];
		if (X >= S->Element) {  /* if need to search inside this tree */
			result = S->Search(S, X);
			if (result != NULL) return result;
		}
	}
	return result;
}


SKHeap* SKHeap :: build(int value) {
    SKHeap* heap = (SKHeap*)malloc(sizeof(struct SKHeap));
    heap->leftHeap = NULL;
    heap->rightHeap = NULL;
    heap->value = value; //the value of initial root
    return heap;
}

//insertion is merging a heap with a new heap with only one element
SKHeap* SKHeap :: insert(SKHeap* heap, int value) {
    SKHeap* newHeap = build(value);
    return merge(heap, newHeap); 
}

SKHeap* SKHeap :: merge(SKHeap* tarHeap, SKHeap* objHeap) {
    SKHeap* newHeap, tempHeap;
    if(tarHeap == NULL) {
        return objHeap;
    } else if(objHeap == NULL) {
        return tarHeap; //handle the condition that one of the hep is empty
    } else {
        if(tarHeap->value > objHeap->value) {
            newHeap = tarHeap->rightHeap;
        	tarHeap->rightHeap = tarHeap->leftHeap; //reverse right and left heap
			tarHeap->leftHeap = merge(newHeap, objHeap); //recursively merging
			return tarHeap;
        } else {
			newHeap = objHeap->rightHeap;
        	objHeap->rightHeap = objHeap->leftHeap; //reverse right and left heap
			objHeap->leftHeap = merge(newHeap, tarHeap); //recursively merging
			return objHeap;
		} // switch two heaps if the root of target heap is bigger trahn objected one       
    }
}

SKHeap* SKHeap :: search(SKHeap* heap, int value) {
	SKHeap* result;
    if(heap->value > value) {
	   result = NULL;
   } else if(heap->value == value) {
	   result = heap;
   } else {
	   result = search(heap->leftHeap, value);
	   if(result == NULL) {
		   result = search(heap->rightHeap, value);
	   }
   }
   return result;
}

SKHeap* SKHeap :: deletemin(SKHeap* heap, int value) {
    return merge(heap->leftHeap, heap->rightHeap); //delete the root and merge its children    
}