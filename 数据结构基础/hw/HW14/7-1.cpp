#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include<iostream>
#include <iomanip>
#include<string>
#include<fstream>

using namespace std;

int n, flag;
int s[1000], l[1000];
vector<int> v[1000];
struct cmp {
	bool operator () (const int &a,const int &b) {
		return s[a] > s[b];
	}
};

int main() {  
	cin>>n;
    int i = 0;
    while(i < n) {
        cin>>s[i];
        i++;
    }

	priority_queue<int,vector<int>,cmp> q;
	int j = 0;
	while (j < n) {
		if(s[j] < 0) {
			j++;
			continue;
		}
		if(s[j] % n != j) {
			int d = s[j] % n > j ? j + n : j;
			for(int k = s[j] % n; k < d; ++k) {
				if(s[k % n] < 0) continue;
				v[k % n].push_back(j);
				l[j] ++;
			}
		} else q.push(j);
		j++;
	}
		
	while(q.empty() == 0) {
		int a = q.top();
		q.pop();
		if(flag) cout<<" ";
		else flag = 1;
		cout<<s[a];
		int m = 0;
		while(m < v[a].size()) {
			int d = v[a][m];
			l[d] --;
			if(!l[d]) q.push(d);
			m++;
		}
	}
	return 0;
}