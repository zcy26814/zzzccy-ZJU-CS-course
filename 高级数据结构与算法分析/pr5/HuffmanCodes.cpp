#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 63
#define MAX_LEN 64
#define INF 1001


typedef struct WeightedTree
{
    int weight;
    // int depth;
    struct WeightedTree* left, * right;
} WeightedTree;

typedef struct MinHeap
{
    WeightedTree** data;
    int size;
    int capacity;
} MinHeap;


typedef struct QueueNode
{
    WeightedTree* data;
    struct QueueNode* next;
} QueueNode;

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

int GetWPL(WeightedTree* tree, int depth);
WeightedTree* BuildHuffmanTree(MinHeap* heap);
WeightedTree* BuildWeightedTree(char code[MAX_N][MAX_LEN], int N, int* f);
int CheckPrefixAndOptimal(WeightedTree* tree, int optimalWpl);

int main()
{
    int N, M, i, j;
    int f[MAX_N] = { 0 };
    char code[MAX_N][MAX_LEN];

    scanf("%d", &N);

    MinHeap* heap = CreateMinHeap(N);

    for (i = 0; i < N; ++i)
    {
        scanf("%*s %d", &f[i]);
        heap->data[++heap->size] = (WeightedTree*)malloc(sizeof(WeightedTree));
        heap->data[heap->size]->weight = f[i];
        // heap->data[heap->size]->depth = 0;
        heap->data[heap->size]->left = heap->data[heap->size]->right = NULL;
    }

    // Adjust array data to MinHeap with time complexity of O(N)
    for (i = N / 2; i >= 1; i--)
        PercDown(heap, i);


#ifdef DEBUG
    for (int i = 0; i <= heap->size; ++i)
    {
        printf("%d ", heap->data[i]->weight);
    }
    printf("\n");
#endif // DEBUG

    //Use huffman algorithm to generate a optimal length
    WeightedTree* huffmanTree = BuildHuffmanTree(heap);
    // int huffman = GetWPL(huffmanTree);
    int huffman = GetWPL(huffmanTree, 0);

    scanf("%d", &M);



    //Compare the length of students given code and check prefix

    //To check prefix, maybe a flag of 
    for (i = 0; i < M; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            scanf("%*s %s", code[j]);
        }
        WeightedTree* tree = BuildWeightedTree(code, N, f);

        if (CheckPrefixAndOptimal(tree, huffman))
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }


    return 0;
}

int CheckPrefixAndOptimal(WeightedTree* tree, int optimalWpl)
{
    WeightedTree* tmp;
    Queue* queue = CreateQueue();
    Enqueue(queue, tree);
    int wpl;

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

    wpl = GetWPL(tree, 0);
    FreeQueue(queue);

    return wpl == optimalWpl;
}

WeightedTree* BuildWeightedTree(char code[MAX_N][MAX_LEN], int N, int* f)
{
    WeightedTree* tree = (WeightedTree*)malloc(sizeof(WeightedTree));
    tree->left = tree->right = NULL;
    tree->weight = INF;

    WeightedTree* tmp = tree;
    int i, j;
    for (i = 0; i < N; ++i)
    {
        tmp = tree;
        for (j = 0; code[i][j] != '\0'; ++j)
        {
            if (code[i][j] == '0')
            {
                if (!tmp->left)
                {
                    tmp->left = (WeightedTree*)malloc(sizeof(WeightedTree));
                    tmp->left->left = NULL;
                    tmp->left->right = NULL;
                    tmp->left->weight = INF;
                }
                tmp = tmp->left;
            }
            else
            {
                if (!tmp->right)
                {
                    tmp->right = (WeightedTree*)malloc(sizeof(WeightedTree));
                    tmp->right->left = NULL;
                    tmp->right->right = NULL;
                    tmp->right->weight = INF;
                }
                tmp = tmp->right;
            }
        }
        tmp->weight = f[i];
    }

    return tree;
}

WeightedTree* BuildHuffmanTree(MinHeap* heap)
{
    WeightedTree* node;

    while (heap->size > 1)
    {
        node = (WeightedTree*)malloc(sizeof(WeightedTree));
        node->left = DeleteMin(heap);

#ifdef DEBUG
        for (int i = 0; i <= heap->size; ++i)
        {
            printf("%d ", heap->data[i]->weight);
        }
        printf("\n");
#endif // DEBUG

        node->right = DeleteMin(heap);

#ifdef DEBUG
        for (int i = 0; i <= heap->size; ++i)
        {
            printf("%d ", heap->data[i]->weight);
        }
        printf("\n");
#endif // DEBUG

        node->weight = node->left->weight + node->right->weight;
        Insert(heap, node);

#ifdef DEBUG
        for (int i = 0; i <= heap->size; ++i)
        {
            printf("%d ", heap->data[i]->weight);
        }
        printf("\n");
#endif // DEBUG

    }

    return DeleteMin(heap);
}

// int GetWPL(WeightedTree *tree)
// {
//     int wpl = 0;
//     if (tree)
//     {

//     }
//     else
//         return INF;
// }

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
MinHeap* CreateMinHeap(int n)
{
    MinHeap* heap;
    heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (WeightedTree**)malloc(sizeof(WeightedTree*) * (MAX_N + 1));
    heap->capacity = MAX_N;
    heap->size = 0;

    heap->data[0] = (WeightedTree*)malloc(sizeof(WeightedTree));
    heap->data[0]->weight = -1;//sentinel
    heap->data[0]->left = heap->data[0]->right = NULL;

    return heap;
}

void PercDown(MinHeap* heap, int p)
{
    int parent, child;
    WeightedTree* tmp = heap->data[p];
    int n = heap->size;
    for (parent = p; 2 * parent <= n; parent = child)
    {
        child = 2 * parent;
        if (child + 1 <= n && heap->data[child + 1]->weight < heap->data[child]->weight)
            child++;

        if (tmp->weight > heap->data[child]->weight)
        {
            heap->data[parent] = heap->data[child];
        }
        else
        {
            break;
        }
    }
    heap->data[parent] = tmp;
}

void Insert(MinHeap* heap, WeightedTree* tree)
{
    int i = ++heap->size;
    if (i <= heap->capacity)
    {
        for (; heap->data[i / 2]->weight > tree->weight; i /= 2)
        {
            heap->data[i] = heap->data[i / 2];
        }
        heap->data[i] = tree;
    }
}

WeightedTree* DeleteMin(MinHeap* heap)
{
    WeightedTree* minTree = NULL;
    if (heap->size)
    {
        minTree = heap->data[1];
        heap->data[1] = heap->data[heap->size--];
        PercDown(heap, 1);
    }

    return minTree;
}

// Queue
Queue* CreateQueue()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = queue->tail = NULL;
    return queue;
}
void Enqueue(Queue* queue, WeightedTree* tree)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = tree;
    node->next = NULL;

    if (queue->tail)
    {
        queue->tail->next = node;
        queue->tail = node;
    }
    else
    {
        queue->head = queue->tail = node;
    }
}

WeightedTree* Dequeue(Queue* queue)
{
    WeightedTree* result = NULL;
    QueueNode* tmp;
    if (queue->head)
    {
        tmp = queue->head;
        queue->head = tmp->next;
        if (!tmp->next)
            queue->tail = NULL;

        result = tmp->data;
        free(tmp);
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