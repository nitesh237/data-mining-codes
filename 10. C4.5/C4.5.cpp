#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
//#define first first
//#define second second
//#define pair<int,int> pair<int, int>
using namespace std;
// ipair, ff, ss, gString, gMap, head, rSString, rMap, node2, 

map<string, int> attributeValues[10];
string rAttrValues[10][10];
map<string, int> attr;
string rAttr[10];
vector< vector<int> >inputArray;
struct node {
	vector<pair<int,int> > ch;		//index of child, partiular attribute
	int id;	// division on the basis of which attribute clasecond
	int fin;
} decTree[10000];
int ctr;

void mapData();
void printData(vector< vector<int> > &ad, vector<int> &colName);
void getData();
double getInfo(double p);
double getEntropy(vector< vector<int> > &inputArray);
int getAttrIndex(vector<int> &colName, vector< vector<int> > &inputArray,double tot);
void printDecTree() ;
void id3Algo(vector<int> &colName, vector< vector< int> > &inputArray, int node);


int main() {
	mapData();
	getData();
	ctr = 1;
	vector<int> colName;
	int i;
	for(i = 1; i <= attr.size(); i++) {
		colName.pb(i);
	}
	id3Algo(colName, inputArray, 1);
	//cout << ctr << endl;
	printDecTree();
	return 0;
}

void printData(vector< vector<int> > &ad, vector<int> &colName) {
	int i, j;
	for(i = 0; i < ad.size(); i++) {
		for(j = 0; j < ad[i].size(); j++) {
			cout << rAttrValues[colName[j]][ad[i][j]] << " ";
		}
		cout << endl;
	}
}
double getInfo(double p) {
	if(p == 0) {
		return 0;
	}
	double info = -p * log2(p);
	return info;
}

void getData() {
	int i;
	ifstream in("tempData.txt");
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
				v.pb(attributeValues[id][temp]);
				temp = "";
			}
			else {
				temp+=str[i];
			}
		}
		inputArray.pb(v);
	}
}

void mapData() {
	attr["Outlook"] = 1; attr["Temp"] = 2; attr["Humidity"] = 3; attr["Windy"] = 4; attr["Decision"] = 5;
	attributeValues[1]["Rain"] = 1; attributeValues[1]["Overcast"] = 2; attributeValues[1]["Sunny"] = 3;

	attributeValues[2]["Hot"] = 1; attributeValues[2]["Mild"] = 2; attributeValues[2]["Cool"] = 3;

	attributeValues[3]["Normal"] = 1; attributeValues[3]["High"] = 2;

	attributeValues[4]["Weak"] = 1; attributeValues[4]["Strong"] = 2;

	attributeValues[5]["No"] = 1; attributeValues[5]["Yes"] = 2;
	
	map<string, int> :: iterator it;
	for(it = attr.begin(); it != attr.end(); it++) {
		rAttr[it->second] = it->first;
	}
	for(int i = 1; i <= 7; i++) {
		for(it = attributeValues[i].begin(); it != attributeValues[i].end(); it++) {
			rAttrValues[i][it->second] = it->first;
		}
	}
}

double getEntropy(vector< vector<int> > &inputArray) {
	int i, j;
	map<int, int> m;
	map<int, int> :: iterator it;
	int c = 0;
	for(i = 0; i < inputArray.size(); i++) {
		int k = inputArray[i].size() - 1;
		m[inputArray[i][k]]++;
		c++;
	}
	if(c == 0) {
		return 0;
	}
	double val = 0;
	for(it = m.begin(); it != m.end(); it++) {
		double p = it->second;
		p/=c;
		val = val + getInfo(p);
	}
	return val;
}
int getAttrIndex(vector<int> &colName, vector< vector<int> > &inputArray,double tot) {
	int id = 0;
	double val = 1e7;
	int i, j;
	int k = colName.size() - 1;
	for(i = 0; i < k; i++) {
		int m = attributeValues[colName[i]].size();
		int n = attributeValues[colName[k]].size();
		int freq[m + 1][n + 1];
		memset(freq, 0, sizeof(freq));
		for(j = 0; j < inputArray.size(); j++) {
			freq[inputArray[j][i]][inputArray[j][k]]++;
		}
		double s = 0;
		double diff = 0;;
		double totSum = 0;
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
			//cout << colName[i] << " " << j << " " << prob  << " " << sum << endl;
			s = s + sum * (prob/inputArray.size());
			totSum+=prob;
		}
		diff = tot - s;
		int r;
		double splitInfo;
		for(j = 1; j <= m; j++) {
			int r;
			double pop = 0;
			for(r = 1; r <= n; r++) {
				pop+= freq[j][r];
			}
			splitInfo += getInfo(pop/totSum);
		}

		s = diff/splitInfo;

		cout << colName[i] << " " << s << endl;
		if(s < val) {
			id = i;
			val = s;
		}
	}
	return id;
}
void id3Algo(vector<int> &colName, vector< vector< int> > &inputArray, int node) {		// colNameing, data, node number
	
	if(inputArray.size() == 0) {
		return;
	}
	
	double tot = getEntropy(inputArray);
	cout << tot << endl;
	
	if(tot == 0) {
		decTree[node].fin = inputArray[0][inputArray[0].size() - 1];
		return;
	}
	
	//cout << "enter" << endl;
	printData(inputArray, colName);
	int id = getAttrIndex(colName, inputArray,tot);
	cout << id << endl;
	decTree[node].id = colName[id];
	vector<int> ncolName;
	int i, j;
	for(i = 0; i < colName.size(); i++) {
		if(i == id) {
			continue;
		}
		ncolName.pb(colName[i]);
	}
	/*for(i = 0; i < ncolName.size(); i++) {
		cout << ncolName[i] << " " ;
	}
	cout << endl;*/
	int num = attributeValues[colName[id]].size();
	//cout << num << endl;
	vector<vector<int> > v[num + 1];
	for(i = 0; i < inputArray.size(); i++) {
		vector<int> temp;
		for(j = 0; j < inputArray[i].size(); j++) {
			if(j == id) {
				continue;
			}
			temp.pb(inputArray[i][j]);
		}
		v[inputArray[i][id]].pb(temp);
	}
	// for(i = 1; i <= num; i++) {
	// 	//cout << "yahan " << i << endl;
	// 	for(j = 0; j < v[i].size(); j++) {
	// 		for(int k = 0; k < v[i][j].size(); k++) {
	// 			cout << rAttrValues[ncolName[k]][v[i][j][k]] << " ";
	// 		}
	// 		cout << endl;
	// 	}
	// 	cout << endl;
	// }
	for(i = 1; i <= num; i++) {
		if(v[i].size() == 0) {
			continue;
		}
		decTree[node].ch.pb(mp(++ctr, i));
		id3Algo(ncolName, v[i], ctr); 
	}
}
void printDecTree() {
	int i, j;
	for(i = 1; i <= ctr; i++) {
		if(decTree[i].fin) {
			cout <<"Leaf Node" << endl;
			cout << rAttrValues[attr.size()][decTree[i].fin] << endl;
		}
		cout << "Node index: " << i << " " << rAttr[decTree[i].id] << endl;
		for(j = 0; j < decTree[i].ch.size(); j++) {
			cout << decTree[i].ch[j].first << " Attribute Value " << rAttrValues[decTree[i].id][decTree[i].ch[j].second] << endl;
		}
		cout << endl;
	}
}