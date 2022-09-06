int main() {
    int a = 0;
    int b = 1;
    int c = 0;
    int n = 0;
    int t = 0;
    scan(n);
    while(c < n) {
        t = b;
        b = a + b;
        a = t;
        c += 1;
    }
    return 0;
}
