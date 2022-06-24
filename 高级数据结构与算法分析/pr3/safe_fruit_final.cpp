#include <iostream>
#include <vector>
#include <algorithm>//for sorting
#include <iomanip>//for printing
#include <time.h>//check pruning and program speed
//#include <map>//an alternative to input conversion
#define MAX 100

using namespace std;

//Born_Kerbosch  The maximum independent set of the original graph is transformed into the maximum clique of the complementary graph
//R set records the points that have been added to the current maximum clique
//P set is a record of points that can be added (that is, points that have edges with all the points in the R set so that they can be added to form a clique)
//X set is a record of the points that have been added to a maximum clique
vector<int> P;
vector<int> R;
vector<int> X;

//price stores the price of each fruit
vector<int> price(MAX, 0);
vector<int> answer(MAX, 0);//final answer

//map<string, int> ID;//if the IDChange function is not used to transform the input data, map can also be used to directly establish a one-to-one correspondence

int BestNum = 0;//largest number
int BestPrice;//best price

//graph stores the complementary graph of the original graph, so the initial edges are true
vector<vector<bool>> graph(MAX, vector<bool>(MAX, true));
//Born_Kerbosch
void Born_Kerbosch(vector<int> R, vector<int> P, vector<int> X,int ISFirst);
//ascending output, using the sort function, need to write the comparison function
bool cmp(int a, int b) {
	return a < b;
}
//convert the input
int IDChange(string s) {
	return (s[2] - '0') + (s[1] - '0') * 10 + (s[0] - '0') * 100;
}
//print the answer
void printAnswer();

//number of edges and vertexes
int EdgeNum, VexNum;
int main() {

//	clock_t start = clock();//check the clock cycle

	string V1, V2;
	int v1, v2;

	cin >> EdgeNum >> VexNum;
	//The problem of maximum independent set of general graphs is transformed into the maximal clique problem of finding the maximum of their complementary graphs by constructing complementary graphs 
	for (int i = 0; i < EdgeNum; i++) {
		cin >> V1 >> V2;
		v1 = IDChange(V1);
		v2 = IDChange(V2);
		//all edges of the complement should be erased to false
		graph[v1][v2] = false;
		graph[v2][v1] = false;
		graph[v1][v1] = false;
		graph[v2][v2] = false;
	}
	// prevent the subscript of the algorithm vector function from running out of bounds, some special edges need to be erased
	{
		graph[i][i] = false;
		graph[0][i] = false;
		graph[i][0] = false;
	}
	//store the prices
	for (int i = 0; i < VexNum; i++) {
		cin >> V1;
		v1 = IDChange(V1);
		cin >> price[v1];
		P.push_back(v1);
	}
	//call algorithm function
	Born_Kerbosch(R, P, X,1);
	//打print the answer
	printAnswer();

	//clock_t end = clock();//check the clock cycle for quantitative viewing of pruning advantages
	//cout << "Running time is " << end - start << endl;

	system("pause");

	return 0;
}

void Born_Kerbosch(vector<int> R, vector<int> P, vector<int> X,int ISFirst) {
	//a clique stored by R is a maximal clique if and only if both P and X are empty
	if (P.empty() && X.empty()) {
		//select the Max Max group with the lowest price
		if (R.size() > BestNum) {
			BestNum = R.size();
			BestPrice = 0;
			for (int i = 0; i < BestNum; i++) {
				answer[i] = R[i];
				BestPrice += price[answer[i]];
			}
		}
		else if (R.size() > 0 && R.size() == BestNum) {
			int nowPrice = 0;
			for (int i = 0; i < R.size() ; i++) {
				nowPrice += price[R[i]];
			}
			if (nowPrice < BestPrice) {
				BestPrice = nowPrice;
				for (int i = 0; i < BestNum; i++) {
					answer[i] = R[i];
				}
			}
		}
	}
	//traversal the point in P, is the point connected with R, may be a point of the maximal clique, so traversal is required 
	for (int i = P.size() - 1; i >= 0; i--) {
		//renew R、P、X
		vector<int> temR;
		vector<int> temP;
		vector<int> temX;

		//pruning
		if (P.size() + R.size() < BestNum)continue;

		//更新新的R、P、X,参照伪代码：
		/*
		Bron-Kerbosch Algorithm:

			R={}   //已确定的极大团顶点的集合
			P={v}  //未处理顶点集，初始状态是所有结点
			X={}   //已搜过的并且属于某个极大团的顶点集合

			BronKerbosch(R, P, X):
			   if P and X are both empty:
				   report R as a maximal clique
			   for each vertex v in P:
				   BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
				   P := P \ {v}
				   X := X ⋃ {v}
		
		*/
		//new R is the old R plus the point I'm traversing now, P[I]
		for (size_t k = 0; k < R.size(); k++) {
			temR.push_back(R[k]);
		}
		//ensure P[I] is not repeatedly added to the new R
		if (find(temR.begin(), temR.end(), P[i]) == temR.end()) temR.push_back(P[i]);

		//renew P、X
		for (int j = 1; j <= VexNum; j++) {
			if (graph[P[i]][j] == true) {
				if (find(P.begin(), P.end(), j) != P.end()) temP.push_back(j);
				if (find(X.begin(), X.end(), j) != X.end()) temX.push_back(j);
			}
		}
		//继续回溯递归
		Born_Kerbosch(temR, temP, temX,0);
		//free memory
		temP.clear();
		temR.clear();
		temX.clear();

		//renew X、P
		X.push_back(P[i]);
		P.pop_back();
	}


}
//print the answer
void printAnswer() {
	cout << BestNum << endl;
	sort(&answer[0], &answer[BestNum], cmp);
	for (int i = 0; i < BestNum; i++) {
		cout << setw(3) << setfill('0') << answer[i] << ' ';//three digit output; if not enough, fill in the front with 0s
	}
	cout << endl;
	cout << BestPrice << endl;
}