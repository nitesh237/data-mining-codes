#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define LN 20
#define MAX 100005
#define ipair pair<int, int> 
vector<int> adj[4000];
vector<string> naming;
int sup;
struct node2 {
	vector<ipair> ch;	//number, tree index
	int val;
	int cnt;
	vector<int> par;
} tree[MAX];
int n, mxid;
int ctr;
vector<ipair> vec;
vector<int> fp[MAX];
int occ[MAX];
void printVector(vector<int> v) {
	int i;
	for(i = 0; i < v.size(); i++) {
		cout << v[i] << "  ";
	}
}
void getData() {
	ifstream in("FILE3.txt");
	string str;
	int i;
	int c = 0;
	while(getline(in, str)) {
		c++;
		if(c == 1) {
			continue;
		}
		else if(c == 2) {
			string temp  = "";
			str+=',';
			for(i = 0; i < str.size(); i++) {
				if(str[i] == ',') {
					naming.pb(temp);
					temp = "";
				}
				else {
					temp = temp + str[i];
				}
			}
			continue;
		}
		++n;
		int num = 0;
		int cnt = 0;
		for(i = 0; i < str.size(); i++) {
			if(str[i] == ',') {
				cnt++;
				mxid = max(mxid, cnt);
				if(num) {
					adj[n].pb(cnt);
					num = 0;
				}
			}
			else {
				num = num * 10 + str[i] - '0';
			}
		}
		if(num) {
			cnt++;
			mxid = max(mxid, cnt);
			adj[n].pb(cnt);
		}
		//printVector(adj[n]);
	}
	in.close();
}
void getOrigdata() {
	int cnt[mxid + 1];
	int i, j, k;
	for(i = 1; i <= mxid; i++) {
		cnt[i] = 0;
	}

	for(i = 1; i <= n; i++) {
		for(j = 0; j < adj[i].size(); j++) {
			cnt[adj[i][j]]++;
		}
	}
	vector<pair<int, int> > v;
	for(i = 1; i <= mxid; i++) {
		if(cnt[i] >= sup) {
			v.pb(mp(cnt[i], i));
		}
	}
	sort(v.rbegin(), v.rend());
	for(i = 1; i <= n; i++) {
		vector<int> temp;
		for(j = 0; j < v.size(); j++) {
			for(k = 0; k < adj[i].size(); k++) {
				if(adj[i][k] == v[j].ss) {
					temp.pb(v[j].ss);
					break;
				}
			}
		}
		adj[i].clear();
		adj[i] = temp;
	}
}
void fillTree(vector<int> &v) {
	int cur = 1;
	int i, j;
	for(i = 0; i < v.size(); i++) {
		for(j = 0; j < tree[cur].ch.size(); j++) {
			if(tree[cur].ch[j].ff == v[i]) {
				break;
			}
		}
		if(j == tree[cur].ch.size()) {
			tree[cur].ch.pb(mp(v[i], ++ctr));
		}
		cur = tree[cur].ch[j].ss;
		tree[cur].cnt++;
		tree[cur].val = v[i];
	}
}
void insertTree() {
	int i;
	ctr = 1;
	for(i = 1; i <= n; i++) {
		fillTree(adj[i]);
	}
}
void dfs(int node, vector<int> &path) {
	if(!node) {
		return;
	}
	int id = tree[node].val;
	vector<int> comm;
	int i, j;
	if(occ[id]) {
		for(i = 0; i < path.size(); i++) {
			for(j = 0; j < fp[id].size(); j++) {
				if(fp[id][j] == path[i]) {
					break;
				}
			}
			if(j != fp[id].size()) {
				comm.pb(path[i]);
			}
		}
		fp[id].clear();
	}
	else {
		comm = path;
	}
	fp[id] = comm;
	occ[id]+=tree[node].cnt;
	if(id) {
		path.pb(id);
	}
	for(i = 0; i < tree[node].ch.size(); i++) {
		dfs(tree[node].ch[i].ss, path);
	}
	if(id) {
		path.pop_back();
	}

}
void getFrequentItemSet() {
	vector<int> path;
	dfs(1, path);
	int i, j, k;
	cout << "frequenetItemSet" << endl;
	for(i = 1; i <= mxid; i++) {
		int r = fp[i].size();
		int ln = (1 << r);
		for(j = 1; j < ln; j++) {
			cout << i << "---> " << naming[i - 1] << " ";
			for(k = 0; k < r; k++) {
				if(j&(1 << k)) {
					cout << fp[i][k] << "---> " << naming[fp[i][k] - 1] << " ";
				}
			}
			cout << endl;
		}
	}
}
int main() {
	getData();
	double plim;
	cin >> plim;
	sup = plim*n;
	getOrigdata();
	for(int i = 1; i <= n; i++) {
		printVector(adj[i]);
		cout << endl;
	}
	insertTree();
	getFrequentItemSet();
	return 0;
}
