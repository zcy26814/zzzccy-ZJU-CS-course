#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length )
{
    for(int i = 0; i < N; i += 2 * length){
        int L = i;
        int R = i + length;
        int num = i;
        int last;
        if((i + 2 * length) > N) last =N;
        else last = i + 2 * length;
        while(L < i + length && R < last && L < N && R < N){
            if(list[L]<list[R])
                sorted[num++]=list[L++];
            else
                sorted[num++]=list[R++];
        }
        while (L < i +length)
        {
            sorted[num++]=list[L++];
        }
        while (R < last)
        {
            sorted[num++]=list[R++];
        }
    }
}
