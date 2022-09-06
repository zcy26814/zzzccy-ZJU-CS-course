char name[5001];

char lim[1000001];

int s[101];

int r[101];

char tmp[1001];

int x;

int tj;

int tk;

int check(int j, int k) {
    x = 0;
    tj = j;
    tk = k;
    while(tk > 0) {
        if(tmp[x] != name[tj]) {
            return 0;
        }
        x += 1;
        tj += 1;
        tk -= 1;
    }
    return 1;
}

int main() {

    int gpa = 0;
    int trys = 0;
    int lrns = 0;
    int ress = 0;
    int n = 0;
    int end = 0;

    int i = 0;
    int j = 0;
    char ch = 0;
    int p = 0;
    int q = 0;
    int k = 0;
    int ok = 0;
    int tok = 0;
    int t = 0;
    char ling = 0; 
    char la = 0;
    char lb = 0;
    char lc = 0;
    while(end != 1) {
        la = tmp[1];
        lb = tmp[2];
        lc = tmp[3];
        scan(tmp);
        if(tmp[1] == la && tmp[2] == lb && tmp[3] == lc)
            end = 1;
        else {
            i = 0;
            j = 0;
            while(tmp[i] != '|') {
                name[n * 10 + j] = tmp[i];
                i += 1;
                j += 1;
            }
            i += 1;
            s[n] = tmp[i] - '0';
            i += 2;
            j = 0;
            while(tmp[i] != '|') {
                lim[n * 500 + j] = tmp[i];
                i += 1;
                j += 1;
            }
            lim[n * 500 + j] = ';';
            i += 1;
            ch = tmp[i];
            if(ch == 0) {
                r[n] = -1;
            }
            else {
                if(ch == 'F')
                    r[n] = 0;
                else
                    r[n] = 'E' - ch;
            }
            n += 1;
        }
    }
    i = 0;
    while(i < n) {
        if(r[i] == 0) {
            trys += s[i];
            ress += s[i];
        }
        if(r[i] == -1) {
            ress += s[i];
        }
        if(r[i] > 0) {
            trys += s[i];
            lrns += s[i];
            gpa += r[i] * s[i];
        }
        i += 1;
    }
    gpa *= 10;
    if(trys != 0)
        gpa /= trys;
    else
        gpa = 0;
    printf("GPA: %d", gpa / 10);
    printf(".%d", gpa % 10);
    println("");
    printf("Hours Attempted: %d", trys);
    println("");
    printf("Hours Completed: %d", lrns);
    println("");
    printf("Credits Remaining: %d", ress);
    println("");
    println("");
    printf("Possible Courses to Take Next:");
    println("");
    if(ress == 0) {
        println("  None - Congratulations!");
        return 0;
    }
    i = 0;
    while(i < n) {
        j = 0;
        ok = 0;
        tok = 1;
        k = 0;
        while(lim[i * 500 + j] != ling) {
            ch = lim[i * 500 + j];
            if(ch == ';') {
                if(k != 0) {
                    tmp[k] = 0;
                    tmp[k + 1] = 0;
                    tmp[k + 2] = 0;
                    p = 0;
                    q = -1;
                    while(p < n) {
                        int cnt = 0;
                        if(check(p * 10, k + 2) == 1) {
                            q = p;
                        }
                        p += 1;
                    }
                    if(q == -1)
                        tok = 0;
                    else {
                        if(r[q] <= 0) {
                            tok = 0;
                        }
                    }
                    k = 0;
                }
                if(tok == 1)
                    ok = 1;
                tok = 1;
                k = 0;
            } else {
                if(ch == ',') {
                    tmp[k] = 0;
                    tmp[k + 1] = 0;
                    tmp[k + 2] = 0;
                    p = 0;
                    q = -1;
                    while(p < n) {
                        if(check(p * 10, k + 2) == 1) {
                            q = p;
                        }
                        p += 1;
                    }
                    if(q == -1)
                        tok = 0;
                    else {
                        if(r[q] <= 0) {
                            tok = 0;
                        }
                    }
                    k = 0;
                }
                else {
                    tmp[k] = ch;
                    k += 1;
                }
            }
            j += 1;
        }
        if(ok == 1 && r[i] <= 0) {
            printf("  ");
            t = 0;
            while(name[i * 10 + t] != ling) {
                printf("%c", name[i * 10 + t]);
                t += 1;
            }
            println("");
        }
        i += 1;
    }
    return 0;
}