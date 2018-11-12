#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define ipair pair<int, int>
using namespace std;

vector< vector<string> > adj;

void printData(vector< vector<string> > &ad) {
	int i, j;
	for(i = 0; i < ad.size(); i++) {
		for(j = 0; j < ad[i].size(); j++) {
			cout << ad[i][j] << " ";
		}
		cout << endl;
	}
}
vector<string> getSplit(string str) {
	str = str + ',';
	int l = str.size();
	string temp = "";
	vector<string> v;
	int i;
	for(i = 0; i < l; i++) {
		if(str[i] == ',') {
			v.pb(temp);
			temp = "";
		}
		else {
			temp+=str[i];
		}
	}
	return v;
}
void getData() {
	ifstream in("Dataset2.txt");
	string str;
	while(getline(in, str)) {
		vector<string> v = getSplit(str);
		adj.pb(v);
	}
}
int main() {
	getData();
	set<string> s;
	set<string> :: iterator it;
	int i, j;
	for(i = 1; i < adj.size(); i++) {
		s.insert(adj[i][adj[i].size() - 1]);
	}
	int k = s.size();
	printData(adj);
	int q;
	cin >> q;
	string str;
	getline(cin,str);
	while(q--) {
		map<string, double> fin;
		map<string, double> :: iterator it2;
		for(it = s.begin(); it != s.end(); it++) {
			fin[*it] = 1;
		}
		getline(cin, str);
		vector<string> v = getSplit(str);
		for(i = 1; i < adj[0].size() - 1; i++) {
			map<string, int> m;
			double num = 0;
			for(j = 1; j < adj.size(); j++) {
				if(adj[j][i] == v[i - 1]) {
					m[adj[j][adj[j].size() - 1]]++;
					num++;
				}
			}
			if(num == 0) {
				continue;
			}
			for(it = s.begin(); it != s.end(); it++) {
				fin[*it]*=(m[*it]/num);
			}
		}
		string res = "";
		double mx = -1;
		for(it2 = fin.begin(); it2 != fin.end(); it2++) {
			cout << it2->ff << " " << it2->ss << endl;
			if(it2->ss > mx) {
				mx = it2->ss;
				res = it2->ff;
			}
		}
		cout << res << endl;
	}
	return 0;
}