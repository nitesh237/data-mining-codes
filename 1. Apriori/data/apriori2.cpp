#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
typedef pair<vector<int>, vector<int> > tpair;
vector<int> adj[4000];
set<tpair> res;
map < vector<int>, int > fin;
int n;
int mxid;
float conf;
int arr[30];
float thresh;
vector<string> naming;
void printVector(vector<int> v) {
	int i;
	for(i = 0; i < v.size(); i++) {
		cout << v[i] << "  ";
	}
}
void getData() {
	ifstream in("FILE1.txt");
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

int getCount(vector<int> &v) {
	int c = 0;
	int i, j;
	for(i = 1; i <= n; i++) {
		int id = 0;
		for(j = 0; j < adj[i].size(); j++) {
			if(adj[i][j] == v[id]) {
				id++;
			}
			if(id == v.size()) {
				c++;
				break;
			}
		}
	}
	return c;
}
void getFirstLevel(vector< vector<int> > &data, vector<int> &occur) {
	int i;
	for(i = 1; i <= mxid; i++) {
		vector<int> temp;
		temp.pb(i);
		int val = getCount(temp);
		if(val > thresh) {
			data.pb(temp);
			occur.pb(val);
		}
	}
}
int getCommon(vector <int> &v1, vector <int> &v2, vector <int> &res) {
	int i = 0, j = 0;
	int c = 0;
	while(i < v1.size() && j < v2.size()) {
		if(v1[i] == v2[j]) {
			res.pb(v1[i]);
			i++;
			j++;
			c++;
		}
		else if(v1[i] < v2[j]) {
			res.pb(v1[i]);
			i++;
		}
		else {
			res.pb(v2[j]);
			j++;
		}
	}
	while(i < v1.size()) {
		res.pb(v1[i]);
		i++;
	}
	while(j < v2.size()) {
		res.pb(v2[j]);
		j++;
	}
	return c;
}

void printData2(vector <vector<int> > &data, vector<int> &occur) {
	int i, j;
	for(i = 0; i < data.size(); i++) {
		for(j = 0; j < data[i].size(); j++) {
			cout << data[i][j] << " ";
		}
		cout << occur[i] << endl;
	}
}
void calcVal(int id, vector<int> v, int cur) {
	if(id == v.size()) {
		int i, j;
		for(i = 0; i < id - 1; i++) {
			vector<int> v1, v2;
			for(j = 0; j <= i; j++) {
				v1.pb(arr[j]);
			}
			for(j = i + 1; j < id; j++) {
				v2.pb(arr[j]);
			}
			sort(v1.begin(), v1.end());
			sort(v2.begin(), v2.end());
			//printVector(v1);
			//printVector(v2);
			float val1 = cur;
			val1/=getCount(v1);
			//cout << getCount(v1) << " " << val1 << endl;
			//cout << endl;
			if(val1 > conf) {
				res.insert(mp(v1, v2));
			}
		}
		return;
	}
	int i, j;
	for(i = 0; i < v.size(); i++) {
		int f = 1;
		for(j = 0; j < id; j++) {
			if(arr[j] == v[i]) {
				f = 0;
			}
		}
		if(f) {
			arr[id] = v[i];
			calcVal(id + 1, v, cur);
		}
	}
}
void apriori() {
	vector< vector <int> > data; vector<int> occur;
	getFirstLevel(data, occur);
	//printData2(data, occur);
	int i, j;
	int c = 0;
	while(data.size() > 1) {
		occur.clear();
		vector< vector<int> > nData;
		set< vector<int> > spl;
		for(i = 0; i < data.size(); i++) {
			for(j = i + 1; j < data.size(); j++) {
				vector<int> k;
				int p = getCommon(data[i], data[j], k);
				//cout << i << " " << j << " " << p << endl;
				if(p >= c && spl.find(k) == spl.end()) {
					int r = getCount(k);
					if(r > thresh) {
						nData.pb(k);
						occur.pb(r);
						spl.insert(k);
						fin[k] = r;
					}
				}
			}
		}
		if(nData.size() == 0) {
			break;
		}
		data.clear();
		for(i = 0; i < nData.size(); i++) {
			data.pb(nData[i]);
		}
		c++;
	}
	cout << "Most Frequent itemset" << endl;
	for(i = 0; i < data.size(); i++) {
		for(j = 0; j < data[i].size(); j++) {
			cout << data[i][j] << " -> " << naming[data[i][j] - 1] << " ";
		}
		cout << endl;
	}
}
void printData() {
	int i;
	for(i = 1; i <= n; i++) {
		int j;
		for(j = 0; j < adj[i].size(); j++) {
			cout << adj[i][j] << " " ;
		}
		cout << endl;
		cout << endl;
	}
}
int main() {
	getData();
	double pip;
	cin >> pip;
	thresh  = pip * n;
	conf = 0.58;
	//printData();
	apriori();
	return 0;
}