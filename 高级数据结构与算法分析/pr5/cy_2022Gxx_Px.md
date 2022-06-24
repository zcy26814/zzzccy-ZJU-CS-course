<div class="cover" style="page-break-after:always;font-family:Consolas;width:100%;height:100%;border:none;margin: 0 auto;text-align:center;" line-height=height>
	<h1 cid="n1123" mdtype="heading" contenteditable="true" class="md-end-block md-heading" style="padding-top:40%; font-size: 50px"><span md-inline="plain" class="md-plain">XXX</span></h1>
	<p cid="n1219" mdtype="paragraph" contenteditable="true" class="md-end-block md-p" style="font: 18px 'Microsoft yahei'"><span md-inline="plain" class="md-plain"> </span><span md-inline="strong" class="md-pair-s"><span class="md-meta md-before"></span><strong><span md-inline="plain" class="md-plain" >Authors:</span></strong><span class="md-meta md-after"></span></span><span md-inline="plain" class="md-plain"> Authors</span></p>
	<p cid="n1218" mdtype="paragraph" contenteditable="true" class="md-end-block md-p" style="padding-bottom: 40%; font: 18px 'Microsoft yahei'"><span md-inline="strong" class="md-pair-s "><span class="md-meta md-before"></span><strong><span md-inline="plain" class="md-plain">Date: </span></strong><span class="md-meta md-after"></span></span><span md-inline="plain" class="md-plain"> 2022/mm/dd</span></p>
</div>

## Chapter 1: Introduction



## Chapter 2: Data Structure / Algorithm Specification

### Data Structure
#### The Build of the Tree
##### Minheap
The most common way to build a Huffman Tree is through minimal heap. Because of the featureof minimal heap, it is very easy to get the smallest element (in this case, the least weighted node). And we can use this feature to easily merge the two smallest nodes.
The struct of the minheap:
```c
typedef struct MinHeap
{
    WeightedTree** data;
    int size;
    int capacity;
} MinHeap;
```
Other relevant operation of the minheap:
```c
void PercDown(MinHeap* heap, int p);// Adjust pth node in heap to deeper to make it a MinHeap`
`void Insert(MinHeap* heap, WeightedTree* tree);// Insert a WeightedTree to heap`
`WeightedTree* DeleteMin(MinHeap* heap)// Delete the min node in heap`
`void FreeHeap(MinHeap* heap);// Release memory`
```

##### The Build of the Huffman Tree and Weighted Tree
For weighted tree:
We build the weighted tree according to the code given. 
Firstly, we set the weight to INF to denote that the path to it is not a code. And then the binary code word for a character is represented by a simple path from the root node to the leaf of the character, where 0 means "turn to the left child" and 1 means "turn to the right child"
For Huffman tree:
We find the two nodes with the least weight by DeleteMin twice and take them as the two children of the new node. The weight of the new node is equal to the sum of the weights of the two children.
Finally, the new node is inserted into the minimum heap.
The main building function of the trees:
```c
// Build Tree according to the code given
WeightedTree* BuildWeightedTree(char code[MAX_N][MAX_LEN], int N, int* f);
// Use Huffman algorithm to build huffman tree
WeightedTree* BuildHuffmanTree(MinHeap* heap)
```
Other relevant operation of the tree:
```c
void FreeWeightedTree(WeightedTree* tree)// Release memory iteratively
```

##### The Queue
The function of the queue is to store the node and for computing WPL in level order.
The struct of the queue and queue node:
```c
typedef struct Queue
{
    QueueNode* head;
    QueueNode* tail;
}Queue;

typedef struct QueueNode
{
    WeightedTree* data;
    struct QueueNode* next;
} QueueNode;
```
Other relevant operation of the queue:
```c
Queue* CreateQueue();// Create an empty queue
void Enqueue(Queue* queue, WeightedTree* tree);// Enqueue WeightedTree
WeightedTree* Dequeue(Queue* queue);// Dequeue WeightedTree
void FreeQueue(Queue* queue);// Release memory
```


### Algorithm
#### General Thought
We use a created tree for each set of input numbers, extending 0 to the left and 1 to the right, assign weight to this node when it is found. And we set the rest of the intermediate nodes to INF where they are created. 
A node whose weight is not INF but still has children does not satisfy the prefix requirement. If the WPL of the tree is not equal to the Optimal WPL, the optimal constraint is not met, meaning that it is not a correct Huffman code.
#### The Calculation of WPL
The value of the WPL is equal to the sum of weighted path lengths of all leaf nodes in the Huffman tree.
We use iterative and recursive approachs to calculate WPL respectively.
##### Recursive version
If it is not a leaf node, the sum of WPL of its left and right nodes is recursively obtained  
If it is a leaf node, the product of depth and weight is returned  
```c
if (!tree->left && !tree->right)
    return depth * tree->weight;
else
    return GetWPL(tree->left, depth + 1) + GetWPL(tree->right, depth + 1);
```
##### Iterative version

#### Check the Prefix Code
Use queue to traverse the tree in level order.  We store the test code in the queue and compare them in pairs. When the first different code element is found and one of the codes has been iterated, the prefix code is not satisfied. 
If there is still node, we check the prefix code the compute the WPL. If the wpl of this tree is the same with optimalWpl got by Huffman algorithm, this should be an optimal encoding way as we have set wpl of code not satisfying prefix rule to INF.



## Chapter 3: Testing Results

* Case 1
  * Input:
  * Expected Result:
  * Actual Result:
  * Status: Pass

* Case 2
  * Input:
  * Expected Result:
  * Actual Result:
  * Status: Pass

* Case 3
  * Input:
  * Expected Result:
  * Actual Result:
  * Status: Pass
* Case 4
  * Input:
  * Expected Result:
  * Actual Result:
  * Status: Pass
* Case 5
  * Input:
  * Expected Result:
  * Actual Result:
  * Status: Pass

| Case  | Input | Expected Result | Actual Result | Status | Purpose |
| ----- | ----- | --------------- | ------------- | ------ | ------- |
| Case1 |       |                 |               |        |         |
| Case2 |       |                 |               |        |         |
| Case3 |       |                 |               |        |         |
| Case4 |       |                 |               |        |         |
| Case5 |       |                 |               |        |         |

## Chapter 4: Analysis and Comments

### Analysis

**Time Complexity:** 



**Space Complexity:** 



### Comments



## Appendix: Source Code



## References



## Author List



## Declaration

​		**We hereby declare that all the work done in this project titled "XXX" is of our independent effort as a group.**

## Signatures