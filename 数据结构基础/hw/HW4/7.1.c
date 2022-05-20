#include<stdio.h>
#include<stdlib.h>

struct treeT
{
    int value;
    int depth;
    struct treeT* leftNode;
    struct treeT* rightNode;
};
typedef struct treeT* treePtr; 

struct linkT
{
    int value;
    struct linkT* nextNode;
};
typedef struct linkT* linkPtr;


treePtr buildTree(int a[], int b[], int n);
void zigzagTree(treePtr tree);
treePtr tryBuildTree(treePtr tree, int a[], int b[], int n);
void setTreeDepth(treePtr tree, int depth);
linkPtr linkTreeByDepth(treePtr tree, int depth, linkPtr link);
void zigzagPrint(linkPtr link, int depth);

int main(){
    int n, a[30], b[30], i;
    treePtr tree;
    scanf("%d", &n);
    for(i = 0; i<n; i++) {
        scanf("%d", a+i);
    }
    for(i = 0; i<n; i++) {
        scanf("%d", b+i);
    }

    tree = buildTree(a, b, n);
    zigzagTree(tree);

}

treePtr buildTree(int a[], int b[], int n)
{
    return tryBuildTree(NULL, a, b, n);
}
void zigzagTree(treePtr tree)
{
    setTreeDepth(tree, 0);
    struct linkT link;
    linkPtr linkptr = &link;
    link.value = 0;

    while(1) {
        link.nextNode = NULL;
        linkTreeByDepth(tree, link.value, linkptr);
        if(link.nextNode == NULL) {
            break;
        } else if(link.value) {
            printf(" ");
        }
        zigzagPrint(link.nextNode, link.value); 
        link.value++;
    }

}

treePtr tryBuildTree(treePtr tree, int a[], int b[], int n) 
{
    if(n == 0) return tree;

    int i = 0, j;
    treePtr newTree = (treePtr)malloc(sizeof(struct treeT));
    newTree->value = a[0];
    newTree->leftNode = tree;
    while(i < n && a[0] != b[i++]);
    newTree->rightNode = tryBuildTree(NULL, a + 1, b, i - 1);
    return tryBuildTree(newTree, a+i, b+i, n - i);
}

void setTreeDepth(treePtr tree, int depth) {
    if(tree == NULL) return;
    tree->depth = depth;
    setTreeDepth(tree->leftNode, depth + 1);
    setTreeDepth(tree->rightNode, depth + 1);
}

linkPtr linkTreeByDepth(treePtr tree, int depth, linkPtr link) {
    if(tree == NULL || tree->depth > depth) {
        return link;
    } else if(tree->depth == depth) {
        link->nextNode = (linkPtr)malloc(sizeof(struct linkT));
        link = link->nextNode;
        link->value = tree->value;
        link->nextNode = NULL;
        return link;
    } else if(tree->depth < depth) {
        link = linkTreeByDepth(tree->leftNode, depth, link);
        return linkTreeByDepth(tree->rightNode, depth, link);
    }
}

void zigzagPrint(linkPtr link, int depth) {
    if(link == NULL) return;
    if(link->nextNode == NULL) {
        printf("%d", link->value);
        return;
    }
    if(depth % 2 == 0) {
        zigzagPrint(link->nextNode, depth);
        printf(" %d", link->value);
    } else {
        printf("%d ", link->value);
        zigzagPrint(link->nextNode, depth);
    }
}