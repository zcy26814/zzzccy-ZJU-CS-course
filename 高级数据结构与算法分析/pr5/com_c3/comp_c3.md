The comparison of the time performance
The overhead of recursive calls is mainly in stack maintenance. The number of parameters less than or equal to 6 in a 64-bit program is passed through the register. It is usually necessary to reserve the original value through the stack before changing the value of the register. Thus, only one additional register is required to reserve through the stack (rbp). ![1](C:\Users\clearlove-champion7\Desktop\5.高级数据结构与算法分析\pr\pr5\com_c3\1.png)

In addition, the stack is maintained only function return address, stack frame pointer and local variable definition. Meanwhile the recursive algorithm does not involve repeated calculation and the overhead is not large in the case of small tree depth. In this case,  the largest N is 63, so the recursive algorithm is not very expensive.

However, the iterative algorithm uses queues, and the maintenance of queues is more expensive than the maintenance of the recursive stack when N is small, so its performance is worse than that of the recursive algorithm.

While, because the number N is not big enough, the difference in speed of two methods is not very obvious.

## Chapter 3: Testing Results

- Case 1: The standard sample

  - Input:7

    A 1 B 1 C 1 D 3 E 3 F 6 G 6 

    4

    A 00000

    B 00001

    C 0001

    D 001

    E 01

    F 10

    G 11

    A 01010

    B 01011

    C 0100

    D 011

    E 10

    F 11

    G 00

    A 000

    B 001

    C 010

    D 011

    E 100

    F 101

    G 110

    A 00000

    B 00001

    C 0001

    D 001

    E 00

    F 10

    G 11

  - Expected Result:

    Yes

    Yes

    No

    No

  - Actual Result:

    Iterative version: ![2](C:\Users\clearlove-champion7\Desktop\5.高级数据结构与算法分析\pr\pr5\com_c3\2.png)
    Average time：4.5638（Each test was performed five times and averaged, same as below）

    Recursive version:![3](C:\Users\clearlove-champion7\Desktop\5.高级数据结构与算法分析\pr\pr5\com_c3\3.png)
    Average time：2.3996

  - Status: Pass

- Case 2: case that each character is not a prefix encoding for any other character
  - Input:

    5

    A 3 B 5 C 3 D 1 E 1 

    1

    A 00

    B 01

    C 10

    D 110

    E 111

  - Expected Result:

    Yes

  - Actual Result:

    Iterative version:

     ![4](C:\Users\clearlove-champion7\Desktop\5.高级数据结构与算法分析\pr\pr5\com_c3\4.png)
    Average time：3.6543

    Recursive version:

    ![5](C:\Users\clearlove-champion7\Desktop\5.高级数据结构与算法分析\pr\pr5\com_c3\5.png)

    Average time：2.6954

  - Status: Pass

- Case 3: case that unsatisfied the requirement of prefix

  - Input:

    5

    A 3 B 5 C 3 D 1 E 1

    1

    A 00

    B 01

    C 11

    D 011

    E 100

  - Expected Result:

    No

  - Actual Result:

    Iterative version:

     ![6](C:\Users\clearlove-champion7\Desktop\5.高级数据结构与算法分析\pr\pr5\com_c3\6.png)
    Average time：2.608

    Recursive version:

    ![7](C:\Users\clearlove-champion7\Desktop\5.高级数据结构与算法分析\pr\pr5\com_c3\7.png)
    Average time：2.677

  - Status: Pass

