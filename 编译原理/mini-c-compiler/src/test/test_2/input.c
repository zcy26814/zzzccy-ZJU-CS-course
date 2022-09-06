int A[1001];

int B[1001];

int C[1001];

int main()
{
    int p = 0;
    int q = 0;
    int r = 0;
    int a = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    scan(p, q);
    while(i < p) {
        j = 0;
        while(j < q) {
            scan(A[i * q + j]);
            j += 1;
        }
        i += 1;
    }
    i = 0;
    scan(a, r);
    while(i < a) {
        j = 0;
        while(j < r) {
            scan(B[i * r + j]);
            j += 1;
        }
        i += 1;
    }

    if(a != q) {
        println("Incompatible Dimensions");
        return 0;
    }
    
    i = 0;
    while(i < p) {
        j = 0;
        while(j < r) {
            k = 0;
            while(k < q) {
                C[i * r + j] += A[i * q + k] * B[k * r + j];
                k += 1;
            }
            j += 1;
        }
        i += 1;
    }

    i = 0;
    j = 0;
    while(i < p) {
        j = 0;
        while(j < r) {
            printf("%10d", C[i * r + j]);
            j += 1;
        }
        i += 1;
        println("");
    }

    return 0;
}
