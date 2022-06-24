#ifndef  HEAPS_H
#define HEAPS_H

#include <stdio.h>
#include <vector>

#define MAX 100

using namespace std;

//����������ݽṹ
class BinNode{
public:
	int Element;
	BinNode* LeftChild;
	BinNode* NextSibling;

public:
	BinNode* merge(BinNode* T1, BinNode* T2);
	BinNode* Search(BinNode* T,int X);
};

class BinTrees {
public:
	int Size;
	BinNode* Trees[MAX];

public:
	BinTrees* InserBinHeap(BinTrees* T,int X);
	BinTrees* MergeBinHeap(BinTrees* T1, BinTrees* T2);
	int DeleteMinBinHeap(BinTrees* T); //ɾ����������Сֵ
	BinNode* SearchBinHeap(BinTrees* T, int X);
};


//������ݽṹ
class SKHeap{
public:
    int value;
    SKHeap* leftHeap;
    SKHeap* rightHeap;

public:
    SKHeap* build(int value);
    SKHeap* insert(SKHeap* heap, int value);
    SKHeap* merge(SKHeap* tarHeap, SKHeap* objHeap);
    SKHeap* deletemin(SKHeap* heap, int value);
	SKHeap* search(SKHeap* heap, int value)
};








#endif // ! HEAPS_H


