#include <bits/stdc++.h>
using namespace std;

typedef struct article{
	int i = 0;
	int v = 0;
	int w = 0;
	vector<article*> children;
} article;

const int maxx = 1000;
const article data0;
int V, N;
int father[maxx] = {0};
vector<article> datas(maxx, data0);

void readData(){
	freopen("depending_bagging_data.txt", "r", stdin);
	scanf("%d %d", &V, &N);
	for(int i = 1; i <= N; i++){
		int father;
		datas[i].i = i;
		scanf("%d %d %d", &datas[i].v, &datas[i].w, &father);
		datas[father].children.push_back(&datas[i]);
	} 
}

void printData(article* atl){
	cout << (*atl).i << setw(4);
	for(int i = 0; i < (*atl).children.size(); i++){		
		printData((*atl).children[i]);
	}
}


int dfs(article* atl, int vol){
	//cout << "running..." << endl;
	int v_remain = vol - (*atl).v;
	int n_son = ((*atl).children).size();
	int f[v_remain + 1] = {0};
	for(int i = 0; i < n_son; i++){
		for(int v_for = v_remain; v_for >= (*(*atl).children[i]).v; v_for--){
			for(int v_share = (*(*atl).children[i]).v; v_share <= v_for; v_share++){
				f[v_for] = max(f[v_for], f[v_for - v_share] + dfs((*atl).children[i], v_share));
			}
		}
	}
	return (*atl).w + f[v_remain];
}


int main(){
	readData();
	printData(&datas[0]);
	cout << "datas[0].children.num:" << (datas[0]).children.size() << endl;
	int result = dfs(&datas[0], V);
	cout << result << endl;
	return 1;
}
