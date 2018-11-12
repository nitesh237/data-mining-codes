#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define ipair pair<int, int>
#define dpair pair<double, double>
using namespace std;

int bFact;
double rad;
int nLeaf;
int ctr = 0;
int root = 0;
struct node2 {
	bool isLeaf;
	int n;
	dpair sum1;	//LS
	dpair sum2;	//SS
	vector <int> ch;	// index,
	vector<dpair> data;
	int par;
} adj[400005];

dpair getSplit(string str) {
	str = str;
	int l = str.size();
	int temp = 0;
	int i;
	dpair p;
	for(i = 0; i < l; i++) {
		if(str[i] == ' ') {
			if(temp) {
				p.ff = temp;
			}
			temp = 0;
			continue;
		}
		else {
			temp = temp * 10 + str[i] - '0';
		}
	}
	p.ss = temp;
	return p;
}
int getNodeRoot(dpair p) {
	++ctr;
	adj[ctr].n = 1;
	adj[ctr].sum1 = p;
	adj[ctr].sum2 = mp(p.ff * p.ff, p.ss * p.ss);
	adj[ctr].isLeaf = false;
	adj[ctr].ch.pb(ctr + 1);
	++ctr;
	adj[ctr].isLeaf = true;
	adj[ctr].sum1 = adj[ctr - 1].sum1;
	adj[ctr].sum2 = adj[ctr - 1].sum2;
	adj[ctr].n = 1;
	adj[ctr].data.pb(p);
	adj[ctr].par = ctr - 1;
	return ctr - 1;
}
int getNode(dpair p) {
	++ctr;
	adj[ctr].data.pb(p);
	adj[ctr].isLeaf = true;
	adj[ctr].sum1 = p;
	adj[ctr].sum2 = mp(p.ff * p.ff, p.ss * p.ss);
	adj[ctr].n = 1;
	return ctr;
}
dpair add(dpair p, dpair q) {
	return mp(p.ff + q.ff, p.ss + q.ss);
}
dpair add2(dpair p, dpair q) {
	return mp(p.ff + q.ff * q.ff, p.ss + q.ss * q.ss);
}
dpair div(dpair p, int n) {
	return mp(p.ff/n, p.ss/n);
}
double getDist(dpair p, dpair q) {
	double val = (p.ff - q.ff) * (p.ff - q.ff) + (p.ss - q.ss) * (p.ss - q.ss);
	return sqrt(val);
}
void relax(int id) {
	dpair ans1 = mp(0, 0);
	dpair ans2 = mp(0, 0);
	if(adj[id].isLeaf) {
		int i;
		for(i = 0; i < adj[id].data.size(); i++) {
			dpair p = adj[id].data[i];
			ans1 = add(ans1, p);
			ans2 = add2(ans2, p);
		}
		adj[id].sum1 = ans1;
		adj[id].sum2 = ans2;
		adj[id].n = i;
		return;
	}
	int i;
	int cnt = 0;
	for(i = 0; i < adj[id].ch.size(); i++) {
		int id2 = adj[id].ch[i];
		ans1 = add(ans1, adj[id2].sum1);
		ans2 = add(ans2, adj[id2].sum2);
		cnt+=adj[id2].n;
	}
	adj[id].sum1 = ans1;
	adj[id].sum2 = ans2;
	adj[id].n = cnt;
}
void branchOverload(int node, int pa, dpair p) {
	if(adj[pa].ch.size() == bFact) {
		int nroot = getNodeRoot(p);
		int id = ++ctr;
		adj[id].ch.pb(pa);
		adj[id].ch.pb(nroot);
		int pa2 = adj[pa].par;
		adj[pa].par = id;
		adj[nroot].par = id;
		adj[id].par = 0;
		if(root == pa) {
			root = id;
		}
		else {
			adj[id].par = pa2;
			adj[pa2].ch.pop_back();
			adj[pa2].ch.pb(id);
		}
		relax(id);
	}
	else {
		int nroot = getNode(p);
		adj[nroot].par = pa;
		adj[pa].ch.pb(nroot);
	}
}
void insertTree2(int node, int pa, dpair p) {
	if(adj[node].isLeaf) {
		if(adj[node].data.size() == nLeaf) {
			branchOverload(node, pa, p);
			return;
		}
		dpair s1 = add(adj[node].sum1, p);
		dpair s2 = add2(adj[node].sum2, p);
		double r = s2.ff + s2.ss;
		double r2 = s1.ff * s1.ff + s1.ss * s1.ss;
		r2/=(adj[node].n + 1);
		r-=r2;
		r/=(adj[node].n + 1);
		r = sqrt(r);
		if(r <= rad) {
			adj[node].data.pb(p);
			adj[node].n+=1;
			adj[node].sum1 = s1;
			adj[node].sum2 = s2;
		}
		else {
			branchOverload(node, pa, p);
		}
		return;
	}

	int id = 0;
	double mn = 1000000000;
	int i;
	for(i = 0; i < adj[node].ch.size(); i++) {
		int nc = adj[node].ch[i];
		dpair q = div(adj[nc].sum1, adj[nc].n);
		double dis = getDist(p, q);
		if(dis < mn) {
			mn = dis;
			id = i;
		}
	}
	insertTree2(adj[node].ch[id], node, p);
	relax(node);
}
void insertTree(dpair p) {
	if(root == 0) {
		root = getNodeRoot(p);
		return;
	}
	insertTree2(root, 0, p);
}

void printTree() {
	int i, j;
	cout << "Root " << root << endl;
	for(i = 1; i <= ctr; i++) {
		cout << "Node " << i << " " << adj[i].par  << " " << adj[i].n << " " << adj[i].isLeaf << endl;
		cout << "LS " << adj[i].sum1.ff << " " << adj[i].sum1.ss << endl;
		cout << "SS " << adj[i].sum2.ff << " " << adj[i].sum2.ss << endl;
		cout << "Child\n";
		for(j = 0; j < adj[i].ch.size(); j++) {
			cout << adj[i].ch[j] << " ";
		}
		cout << endl;
		cout << "Data\n";
		for(j = 0; j < adj[i].data.size(); j++) {
			cout << adj[i].data[j].ff << " " << adj[i].data[j].ss << endl;
		}
		cout << endl;
	}
}
void buildTree() {
	ctr = 0;
	bFact = 2;
	rad = 0.15;
	nLeaf = 2;
	ifstream in("Dataset.txt");
	string str;
	int c = 0;
	while(getline(in, str)) {
		c++;
		dpair p = getSplit(str);
		insertTree(p);
		cout << c << " " << ctr << endl;
		if(c > 1000) 
			break;
	}
	printTree();
}
int main() {
	buildTree();
	return 0;
}