int array[10000];

int quick_sort(int left, int right) {
    if (left < right) {
        int i = left;
        int j = right;
        int pivot = array[i];
        while (i < j) {
            while(i < j && array[j] > pivot) 
                j -= 1;
            if(i < j) {
			    array[i] = array[j];
                i += 1;
            }

            while(i < j && array[i] < pivot) 
				i += 1;
            if(i < j) {
                array[j] = array[i];
                j -= 1;
            }
        }
        array[i] = pivot;
        quick_sort(left, i-1);
        quick_sort(i+1, right);
    }
    return 0;
}
  
int main() {
   	int N;scan(N);
	
    int i = 0;
   	
    while( i < N ) {
      	scan(array[i]);
      	i += 1;
   	}

	quick_sort(0, N-1);

    println("after sorted:");
    i = 0;
   	while (i < N ) {
		printf("%d ",array[i]);
      	i += 1;
   	}

	return 0;
}