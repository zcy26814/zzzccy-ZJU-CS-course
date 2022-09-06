int a[10001];

//quick sort [l, r]
int qsort(int l, int r) {
    if(l >= r)
        return 0;
    int i = l;
    int j = r;
    int p = a[i];
    while(i < j) {
        while(i < j && a[j] > p) 
            j -= 1;
        if(i < j) {
            a[i] = a[j];
            i += 1;
        }
        while(i < j && a[i] < p) 
            i += 1;
        if(i < j) {
            a[j] = a[i];
            j -= 1;
        }
    }
    a[i] = p;
    qsort(l, i - 1);
    qsort(i + 1, r);
    return 0;
}
  
int main() {
    int n = 0;
    int i = 0;
    scan(n);
    while(i < n) {
      	scan(a[i]);
      	i += 1;
   	}
	qsort(0, n - 1);
    i = 0;
   	while(i < n) {
		printf("%d",a[i]);
        println("");
      	i += 1;
   	}
	return 0;
}