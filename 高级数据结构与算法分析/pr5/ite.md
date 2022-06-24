##### Iterative version

In order to achieve iterative method, we introduce a node representing the end of a layer when doing level traversal. At the same time, we use queue to realize the level traversal. For every time it dequeues the node, the depth plus one. And then it enqueue the node back.
To get the depth, we create a new node and initialize its weight with -1.
The main process for iteration:

```c
    while (queue->tail)//queue is not empty
    {
        tmp = Dequeue(queue);
        if (tmp->weight == -1 && queue->head)  // Check if it is the end of the level
        {
            depth++;
            Enqueue(queue, level);
        }
        else if (tmp->weight == -1 && !queue->head) //  If there is no other node except level node
        {
        }
        else
        {
            if (!tmp->left && !tmp->right) // The path to this node is a code
            {
                wpl += tmp->weight * depth;
            }
            if (tmp->left)
                Enqueue(queue, tmp->left);
            if (tmp->right)
                Enqueue(queue, tmp->right);
        }
    }
```

