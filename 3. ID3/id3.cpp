#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define ipair pair<int, int>
using namespace std;


map<string, int> gMap[10];
string rMap[10][10];
map<string, int> gString;
string rString[10];
vector< vector<int> >adj;
struct node2 {
	vector<ipair> ch;		//index of child, partiular attribute
	int id;	// division on the basis of which attribute class
	int fin;
} tree[10000];
int ctr;
void makeData() {
	gString["buying"] = 1; gString["maint"] = 2; gString["doors"] = 3; gString["person"] = 4; gString["lugBoot"] = 5; gString["safety"] = 6; gString["cl"] = 7;
	gMap[1]["low"] = 1; gMap[1]["med"] = 2; gMap[1]["high"] = 3; gMap[1]["vhigh"] = 4;

	gMap[2]["low"] = 1; gMap[2]["med"] = 2; gMap[2]["high"] = 3; gMap[2]["vhigh"] = 4;

	gMap[3]["2"] = 1; gMap[3]["3"] = 2; gMap[3]["4"] = 3; gMap[3]["5more"] = 4;

	gMap[4]["2"] = 1; gMap[4]["4"] = 2; gMap[4]["more"] = 3;

	gMap[5]["small"] = 1; gMap[5]["med"] = 2; gMap[5]["big"] = 3;

	gMap[6]["low"] = 1; gMap[6]["med"] = 2; gMap[6]["high"] = 3;

	gMap[7]["unacc"] = 1; gMap[7]["acc"] = 2; gMap[7]["good"] = 3; gMap[7]["vgood"] = 4;
	map<string, int> :: iterator it;
	for(it = gString.begin(); it != gString.end(); it++) {
		rString[it->ss] = it->ff;
	}
	for(int i = 1; i <= 7; i++) {
		for(it = gMap[i].begin(); it != gMap[i].end(); it++) {
			rMap[i][it->ss] = it->ff;
		}
	}
}

void printData(vector< vector<int> > &ad, vector<int> &head) {
	int i, j;
	for(i = 0; i < ad.size(); i++) {
		for(j = 0; j < ad[i].size(); j++) {
			cout << rMap[head[j]][ad[i][j]] << " ";
		}
		cout << endl;
	}
}
void getData() {
	int i;
	ifstream in("carData.txt");
	string str;
	while(getline(in, str)) {
		str = str + ',';
		int l = str.size();
		string temp = "";
		int id = 0;
		vector<int> v;
		for(i = 0; i < l; i++) {
			if(str[i] == ',') {
				++id;
				v.pb(gMap[id][temp]);
				temp = "";
			}
			else {
				temp+=str[i];
			}
		}
		adj.pb(v);
	}
}
double getInfo(double p) {
	if(p == 0) {
		return 0;
	}
	return -p * log2(p);
}
double getEntropy(vector< vector<int> > &adj) {
	int i, j;
	map<int, int> m;
	map<int, int> :: iterator it;
	int c = 0;
	for(i = 0; i < adj.size(); i++) {
		int k = adj[i].size() - 1;
		m[adj[i][k]]++;
		c++;
	}
	if(c == 0) {
		return 0;
	}
	double val = 0;
	for(it = m.begin(); it != m.end(); it++) {
		double p = it->ss;
		p/=c;
		val = val + getInfo(p);
	}
	return val;
}
int getIndex(vector<int> &head, vector< vector<int> > &adj) {
	int id = 0;
	double val = 1e7;
	int i, j;
	int k = head.size() - 1;
	for(i = 0; i < k; i++) {
		int m = gMap[head[i]].size();
		int n = gMap[head[k]].size();
		int freq[m + 1][n + 1];
		memset(freq, 0, sizeof(freq));
		for(j = 0; j < adj.size(); j++) {
			freq[adj[j][i]][adj[j][k]]++;
		}
		double s = 0;
		for(j = 1; j <= m; j++) {
			double sum = 0;
			double prob = 0;
			int r;
			double pop = 0;
			for(r = 1; r <= n; r++) {
				pop+=freq[j][r];
			}
			if(pop == 0) {
				continue;
			}
			for(r = 1; r <= n; r++) {
				sum = sum + getInfo(freq[j][r]/pop);
				prob+=freq[j][r];
			}
			s = s + sum * (prob/adj.size());
		}
		if(s < val) {
			id = i;
			val = s;
		}
	}
	return id;
}
void buildSub(vector<int> &head, vector< vector< int> > &adj, int node) {		// heading, data, node number
	if(adj.size() == 0) {
		return;
	}
	double tot = getEntropy(adj);
	if(tot == 0) {
		tree[node].fin = adj[0][adj[0].size() - 1];
		return;
	}
	int id = getIndex(head, adj);
	tree[node].id = head[id];
	vector<int> nhead;
	int i, j;
	for(i = 0; i < head.size(); i++) {
		if(i == id) {
			continue;
		}
		nhead.pb(head[i]);
	}
	int num = gMap[head[id]].size();
	vector<vector<int> > v[num + 1];
	for(i = 0; i < adj.size(); i++) {
		vector<int> temp;
		for(j = 0; j < adj[i].size(); j++) {
			if(j == id) {
				continue;
			}
			temp.pb(adj[i][j]);
		}
		v[adj[i][id]].pb(temp);
	}
	for(i = 1; i <= num; i++) {
		if(v[i].size() == 0) {
			continue;
		}
		tree[node].ch.pb(mp(++ctr, i));
		buildSub(nhead, v[i], ctr); 
	}
}
void printTree() {
	int i, j;
	for(i = 1; i <= ctr; i++) {

		cout << "NODE "<< " " << rString[tree[i].id] << endl;
		cout<<endl;
		if(tree[i].fin) {
			cout<<"CLASS LABEL-"<<endl;
			cout << rMap[gString.size()][tree[i].fin] <<endl;
			continue;
		} else {
			cout<<"NOT A LEAF"<<endl;
		}
		cout<<"CHILDs-"<<endl;
		for(j = 0; j < tree[i].ch.size(); j++) {
			cout << tree[i].ch[j].ff << " " << rMap[tree[i].id][tree[i].ch[j].ss] << endl;
		}
		cout << endl<<endl;
	}
}
int main() {
	makeData();
	getData();
	ctr = 1;
	vector<int> head;
	int i;
	for(i = 1; i <= gString.size(); i++) {
		head.pb(i);
	}
	buildSub(head, adj, 1);
	printTree();
	return 0;
}
