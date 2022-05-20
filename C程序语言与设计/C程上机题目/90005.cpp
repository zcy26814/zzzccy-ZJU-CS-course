#include <stdio.h>
int main (void)
{  
    int i, max_index, min_index, n;
    double x;
    struct book{
        char name[50];
        double price;
    }book[10];

    scanf("%d", &n);
    getchar();
    for(i = 0; i < n; i++){
        gets(book[i].name);
        scanf("%lf", &x);
        getchar();
        book[i].price = x;
    }
    min_index=max_index=0;
    for(i=1;i<n;i++)
    {
    	if(book[i].price>book[max_index].price)
    	max_index=i;
    	if(book[i].price<book[min_index].price)
    	min_index=i;
    }
    printf("highest price: %.1f, %s\n", book[max_index].price, book[max_index].name);
    printf("lowest price: %.1f, %s\n", book[min_index].price, book[min_index].name);
}
