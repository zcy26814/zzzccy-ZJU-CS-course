#include<stdio.h>

void push(int s[], int *top, int elem);
int pop(int s[], int *top);
int check(int sequence[], int length, int maxCapacity);

int main() {
    int M, N, K, i, j;
    int s[1000], r[1000];

    scanf("%d", &M);
    scanf("%d", &N);
    scanf("%d", &K);

    for(i=0; i<K; i++) {
        for(j=0; j<N; j++) {
            scanf("%d", s+j);
        }
        r[i] = check(s, N, M);
    }
    for(i=0; i<K; i++) {
        if(i != 0) putchar('\n');
        printf("%s", r[i] == 0? "NO": "YES");
    }
}

int check(int sequence[], int length, int maxCapacity){
    int stack[1000], i, j=0, p=0;

    for(i=0; i<length; i++){
        for(; j<sequence[i]; j++){
            push(stack, &p, j+1);
        }
        if((p > maxCapacity) || (sequence[i] != pop(stack, &p))) return 0;
    }
    return 1;
}
void push(int s[], int *top, int elem){
    s[*top] = elem;
    (*top)++;
}
int pop(int s[], int *top){
    return s[--(*top)];
}