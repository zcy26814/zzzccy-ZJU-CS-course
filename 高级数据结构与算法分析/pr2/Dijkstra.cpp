typedef struct Node* Node
struct  Node{
    int Node_id;
    int dis;
    Node next;
};

typedef struct Table* Table
struct  Table{
    int dis;
    int path;
};


int dij(int beg, int end){
    int judge;
    int min_dis;
    min_dis = beg;
    Node a,b;
    Table[beg]->dis = 0;

    #ifdef 

    #elif

    #elif

    #elif

    #endif

    while(!judge){
    #ifdef 

    #elif

    #elif

    #elif

    #endif

    if(to == min_way) break;
    for(b = a->next; b; b = b->next){
        if(Table[b->Node_id]->dis > Table[a>Node_id]->dis + b->dist){
            Table[b->Node_id]->dis = Table[a>Node_id]->dis + b->dist;
            Table[b->node_id]->path = min_dis;
                #ifdef 

                #elif

                #elif

                #elif

                #endif
        }
        #ifdef 

        #elif

        #elif

        #elif

        #endif
    }
    if(min_dix == end) return 1;
    return 0;
    }
}