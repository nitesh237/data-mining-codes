#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std;
vector< pair<vector<double>, string> > adj;
int size, n;
void getdata()
{
	ifstream in("dataset.txt");
	string str;
	int f = 0;
	while(getline(in, str)) {
		string temp = "";
		str += " ";
		if(!f) {
			for(int i = 0; i < str.size(); i++) {
				if(str[i] == ' ') {
					if(!f) {
						stringstream cinn(temp);
						cinn>>size;
						f = 1;
						temp = "";
					} else {
						stringstream cinn(temp);
						cinn>>n;
						temp = "";
					}
				}
				temp += str[i];
			}
		} else {
			vector<double> v;
			string cl;
			double x = 0;
			for(int i =0 ; i < str.size(); i++) {
				if(str[i] == ' ') {
					if(v.size() == n-1) {
						cl = temp;
						temp = "";
						continue;
					}
					stringstream cinn(temp);
					cinn>>x;
					temp = "";
					v.pb(x);
					continue;
				} 
				temp += str[i];
			}
			adj.pb(mp(v, cl));
		}
	}
}
double eucl(vector<double> v, vector<double> mean) 
{
	double ans = 0;
	for(int i = 0; i < v.size(); i++) {
		ans += (v[i] - mean[i])*(v[i] - mean[i]);
	}
	ans = sqrt(ans);
	return ans;
}
string KNN(vector<double> qr, int k)
{
	vector<pair<double, int> > dist;
	for(int i = 0; i < adj.size(); i++) {
		dist.pb(mp(eucl(qr, adj[i].first), i));
	}
	sort(dist.begin(), dist.end());
	map<string, int> mp;
	map<string, int> :: iterator it;
	for(int i = 0 ; i < k; i++) {
		int id = dist[i].second;
		string classs = adj[id].second;
		mp[classs]++;
	}
	string ans;
	int maxx = -1;
	for(it = mp.begin(); it != mp.end(); it++) {
		if(it->second > maxx) {
			maxx = it->second;
			ans = it->first;
		}
	}
	return ans;
}
int main()
{
	int q, k;
	cout<<"Enter K: ";
	cin>>k;
	cout<<"Enter Number of queries:";
	cin>>q;
	getdata();
	while(q--) {
		vector<double> qr;
		double x;
		for(int i = 0; i < n-1; i++) {
			cin>>x;
			qr.pb(x);
		}
		string ans = KNN(qr, k);
		cout<<ans<<endl;
	}
}