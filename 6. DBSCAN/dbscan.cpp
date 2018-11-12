#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define ipair pair<int, int>
#define dpair pair<double, double>
using namespace std;

int minPts;
double eps;
struct node2 {
	dpair val;
	int label;	//0->unassigned, -1->noise
	node2() {
		val = mp(0, 0);
		label = 0;
	}
} arr[10005];
int n = 0;
dpair getSplit(string s) {
	s = s;
	dpair res;
	int i;
	double sum = 0;
	int f = 0;
	double val = 0.1;
	for(i = 0; i < s.size(); i++) {
		if(s[i] == '.') {
			f = 1;
			val = 0.1;
			continue;
		}
		else if(s[i] == ' ') {
			res.ff = sum;
			sum = 0;
			f = 0;
			continue;
		}
		if(f) {
			sum = sum + (s[i] - '0') * val;
			val/=10;
		}
		else {
			sum = sum * 10 + s[i] - '0';
		}
	}
	res.ss = sum;
	return res;
}
void getData() {
	ifstream in("DBSCAN.txt");
	string str;
	getline(in, str);
	dpair p  = getSplit(str);
	minPts = p.ss;
	while(getline(in, str)) {
		n++;
		arr[n].val = getSplit(str);
	}
	cin >> eps;
}

double dist(dpair p, dpair q) {
	double val = (p.ff - q.ff) * (p.ff - q.ff) + (p.ss - q.ss) * (p.ss - q.ss);
	return sqrt(val);
}
set <int> QueryN(dpair p) {
	int i;
	set<int> v;
	for(i = 1; i <= n; i++) {
		if(dist(p, arr[i].val) <= eps) {
			v.insert(i);
		}
	}
	return v;
}
void mergeSet(set <int> &s1, set<int> &s2) {
	set<int> :: iterator it;
	for(it = s2.begin(); it != s2.end(); it++) {
		s1.insert(*it);
	}
}
void copy(set <int> &s1, set<int> &s2) {
	s1.clear();
	mergeSet(s1, s2);
}
void assignLabel() {
	int c = 0;
	int i;
	for(i = 1; i <= n; i++) {
		if(arr[i].label) {
			continue;
		}
		set<int> s1 = QueryN(arr[i].val);
		if(s1.size() < minPts) {
			arr[i].label = -1;
			continue;
		}
		c++;
		arr[i].label = c;
		s1.erase(i);
		set<int> s2;
		set<int> :: iterator it;
		while(s1.size()) {
			for(it = s1.begin(); it != s1.end(); it++) {
				int id = *it;
				if(arr[id].label == -1) {
					arr[id].label = c;
				}
				else if(arr[id].label) {
					continue;
				}
				arr[id].label = c;
				set<int> s3 = QueryN(arr[id].val);
				if(s3.size() >= minPts) {
					mergeSet(s2, s3);
				}
			}
			copy(s1, s2);
			s2.clear();
		}
	}
	cout << "Number of class Labels " << c << endl;
}
void printLabel() {
	int i;
	for(i = 1; i <= n; i++) {
		cout << arr[i].val.ff << " " << arr[i].val.ss << " " << arr[i].label << endl;
	}
}
int main() {
	getData();
	assignLabel();
	//printLabel();
	return 0;
}