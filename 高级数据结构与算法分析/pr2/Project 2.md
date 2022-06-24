# Project 2 - Shortest Path Algorithm with Heaps

2022/3/30

## Chapter 1 Introduction

Shortest path problems never fail to be an efficient way to solve and optimize other complex problems.

This project is using Dijkstra's algorithm to compute the shortest paths, basing on min-priority queues.

In this project, our team use Fibonacci heap, Leftist heap, Skewed heap and Binomial queue.

## Chapter 2 Data Structure & Algorithm Specification

### 2.1 Algorithm Specification

Dijkstra algorithm is greedy. 

First it saves the distance from the starting point to all points to find the shortest one. 

And then release one to find the shortest one. Such operation is to traverse the shortest point just found as a transit station to see if it will be closer. 

If it is closer, update the distance, so that all the points can be found and then save the starting point and its shortest distance to all other points.

### 2.2 Data Structure

#### 1) main data structure

```c

```

#### 2) Fibonaaci heap

```

```

#### 3) Leftist heap

```

```

#### 4) Skewed heap

```

```

#### 5) Binomial queue

```

```

#### 6) Dijkstra Algorithm

```

```

#### Other main functions:



### Chapter 3 Testing Result

#### **1) Fibonaaci heap**

#### 2) Leftist heap

#### 3) Skewed heap

#### 4) Binomial queue





### Chapter 4 Analysis and Comments

**Time Complexity**



**Space Complexity**



### **Appendix**

```c

```

