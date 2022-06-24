#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 63
#define MAX_LEN 64
#define INF 1001


typedef struct WeightedTree
{
    int weight;
    struct WeightedTree* left, * right;
} WeightedTree;

typedef struct MinHeap
{
    WeightedTree** data;
    int size;
    int capacity;
} MinHeap;

// Node of the queue
typedef struct QueueNode
{
    WeightedTree* data;
    struct QueueNode* next;
} QueueNode;

// For prefix checking in level order
typedef struct Queue
{
    QueueNode* head;
    QueueNode* tail;
}Queue;

// Queue
Queue* CreateQueue();
void Enqueue(Queue* queue, WeightedTree* tree);
WeightedTree* Dequeue(Queue* queue);
void FreeQueue(Queue* queue);

// Heap
MinHeap* CreateMinHeap(int n);
void PercDown(MinHeap* heap, int p);
WeightedTree* DeleteMin(MinHeap* heap);
void Insert(MinHeap* heap, WeightedTree* tree);
void FreeHeap(MinHeap* heap);

int GetWPL(WeightedTree* tree, int depth);
WeightedTree* BuildHuffmanTree(MinHeap* heap);
WeightedTree* BuildWeightedTree(char code[MAX_N][MAX_LEN], int N, int* f);
void FreeWeightedTree(WeightedTree* tree);
int CheckPrefixAndOptimal(WeightedTree* tree, int optimalWpl);

int main()
{
    clock_t start, end;
    start = clock();
    int N, M, i, j;
    int f[MAX_N] = { 0 };
    char code[MAX_N][MAX_LEN];

    scanf("%d", &N);

    MinHeap* heap = CreateMinHeap(N);   // Initialize an empty heap

    for (i = 0; i < N; ++i)
    {
        scanf("%*s %d", &f[i]);

        //Fill the heap content simultaneously, though it will not be a MinHeap yet
        heap->data[++heap->size] = (WeightedTree*)malloc(sizeof(WeightedTree));
        heap->data[heap->size]->weight = f[i];
        heap->data[heap->size]->left = heap->data[heap->size]->right = NULL;
    }

    // Adjust array data to MinHeap with time complexity of O(N)
    for (i = N / 2; i >= 1; i--)
        PercDown(heap, i);

    //Use huffman algorithm to generate a optimal length
    WeightedTree* huffmanTree = BuildHuffmanTree(heap);

    int huffman = GetWPL(huffmanTree, 0);

    scanf("%d", &M);

    //Compare the length of students given code and check prefix 
    for (i = 0; i < M; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            scanf("%*s %s", code[j]);
        }

        // Build WeightedTree according to the code input
        WeightedTree* tree = BuildWeightedTree(code, N, f);

        if (CheckPrefixAndOptimal(tree, huffman))   // Check if the code satisfy optimal and prefix requirement
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        // Free the memory that is mallocated
        FreeWeightedTree(tree);
    }

    end = clock();
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    // Free the memory that is mallocated
    FreeHeap(heap); 
    FreeWeightedTree(huffmanTree);
    return 0;
}

int CheckPrefixAndOptimal(WeightedTree* tree, int optimalWpl)
{
    WeightedTree* tmp;
    Queue* queue = CreateQueue();
    Enqueue(queue, tree);
    int wpl = 0;

    while (queue->tail)//queue is not empty
    {
        tmp = Dequeue(queue);

        //Check isPrefix
        if (tmp->weight != INF) // The path to this node is a code
        {
            if (tmp->left || tmp->right) // isPrefix 
            {
                wpl = INF;
                break;
            }
        }

        if (tmp->left)
            Enqueue(queue, tmp->left);
        if (tmp->right)
            Enqueue(queue, tmp->right);
    }

    if (wpl != INF)
        wpl = GetWPL(tree, 0);
    FreeQueue(queue);

    return wpl == optimalWpl;
}


// Build Tree according to the code given
WeightedTree* BuildWeightedTree(char code[MAX_N][MAX_LEN], int N, int* f)
{
    WeightedTree* tree = (WeightedTree*)malloc(sizeof(WeightedTree));
    tree->left = tree->right = NULL;
    tree->weight = INF; // Set the weight to INF to denote that the path to it is not a code

    WeightedTree* tmp = tree;
    int i, j;
    for (i = 0; i < N; ++i)
    {
        tmp = tree;
        for (j = 0; code[i][j] != '\0'; ++j)    // While it is not the end of the code
        {
            if (code[i][j] == '0')  // '0' means a left child
            {
                if (!tmp->left) // If child not exists, create it
                {
                    tmp->left = (WeightedTree*)malloc(sizeof(WeightedTree));
                    tmp->left->left = NULL;
                    tmp->left->right = NULL;
                    tmp->left->weight = INF;
                }
                tmp = tmp->left;
            }
            else // '1' means a right child
            {
                if (!tmp->right)    // If child not exists, create it
                {
                    tmp->right = (WeightedTree*)malloc(sizeof(WeightedTree));
                    tmp->right->left = NULL;
                    tmp->right->right = NULL;
                    tmp->right->weight = INF;
                }
                tmp = tmp->right;
            }
        }
        tmp->weight = f[i]; // Set the weight of the code node to its frequency
    }

    return tree;
}

// Use Huffman algorithm to build huffman tree
WeightedTree* BuildHuffmanTree(MinHeap* heap)
{
    WeightedTree* node;

    while (heap->size > 1)
    {
        node = (WeightedTree*)malloc(sizeof(WeightedTree));
        node->left = DeleteMin(heap);
        node->right = DeleteMin(heap);
        node->weight = node->left->weight + node->right->weight;
        Insert(heap, node);
    }

    return DeleteMin(heap); // return the root of the huffman tree
}

// Release memory recursively
void FreeWeightedTree(WeightedTree* tree)
{
    if (!tree) return;
    FreeWeightedTree(tree->left);
    FreeWeightedTree(tree->right);
    free(tree);
}

// Compute WPL recursively for huffman tree
int GetWPL(WeightedTree* tree, int depth)
{
    if (!tree)
        return INF;

    if (!tree->left && !tree->right)
        return depth * tree->weight;
    else
        return GetWPL(tree->left, depth + 1) + GetWPL(tree->right, depth + 1);
}

//MinHeap

// Create an empty MinHeap
MinHeap* CreateMinHeap(int n)
{
    MinHeap* heap;
    heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (WeightedTree**)malloc(sizeof(WeightedTree*) * (MAX_N + 1));
    heap->capacity = MAX_N;
    heap->size = 0;

    heap->data[0] = (WeightedTree*)malloc(sizeof(WeightedTree));
    heap->data[0]->weight = -1; // sentinel
    heap->data[0]->left = heap->data[0]->right = NULL;

    return heap;
}

// Adjust pth node in heap to deeper to make it a MinHeap
void PercDown(MinHeap* heap, int p)
{
    int parent, child;
    WeightedTree* tmp = heap->data[p];
    int n = heap->size;
    for (parent = p; 2 * parent <= n; parent = child)
    {
        child = 2 * parent;
        if (child + 1 <= n && heap->data[child + 1]->weight < heap->data[child]->weight)    // Find the smaller Node
            child++;

        if (tmp->weight > heap->data[child]->weight)    // Move node to higher to make space for the tmp
        {
            heap->data[parent] = heap->data[child];
        }
        else // Find the proper place
        {
            break;
        }
    }
    heap->data[parent] = tmp;
}

// Insert a WeightedTree to heap
void Insert(MinHeap* heap, WeightedTree* tree)
{
    int i = ++heap->size;
    if (i <= heap->capacity)
    {
        for (; heap->data[i / 2]->weight > tree->weight; i /= 2)    // Find proper place to insert it
        {
            heap->data[i] = heap->data[i / 2];  // move the original nodes to make space for new node
        }
        heap->data[i] = tree;
    }
}

// Delete the min node in heap
WeightedTree* DeleteMin(MinHeap* heap)
{
    WeightedTree* minTree = NULL;
    if (heap->size)
    {
        minTree = heap->data[1];    // The min is at the 1th place
        heap->data[1] = heap->data[heap->size--];   // Move the last node to 1th node
        PercDown(heap, 1);  // Adjust the 1th node
    }

    return minTree;
}

// Release memory
void FreeHeap(MinHeap* heap)
{
    free(heap->data);
    free(heap);
}

// Queue

// Create an empty queue
Queue* CreateQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    return queue;
}

// Enqueue WeightedTree
void Enqueue(Queue* queue, WeightedTree* tree)
{
    // Create new node for WeightedTree
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = tree;
    node->next = NULL;

    if (queue->tail)    // If the queue has elements
    {
        queue->tail->next = node;
        queue->tail = node;
    }
    else // If it is an empty queue
    {
        queue->head = queue->tail = node;
    }
}

WeightedTree* Dequeue(Queue* queue)
{
    WeightedTree* result = NULL;
    QueueNode* tmp;
    if (queue->head)    // If the queue is not empty
    {
        tmp = queue->head;
        queue->head = tmp->next;
        if (!tmp->next)
            queue->tail = NULL;

        result = tmp->data;
        free(tmp);  // Release memory
    }

    return result;
}

void FreeQueue(Queue* queue)
{
    QueueNode* p = queue->head;
    QueueNode* tmp = p;

    while (p)
    {
        tmp = p->next;
        free(p);
        p = tmp;
    }
    free(queue);
}