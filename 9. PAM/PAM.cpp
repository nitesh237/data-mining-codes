#include<bits/stdc++.h>
#define pb push_back
using namespace std;
struct cluster
{
	vector< vector<double> > points;
	vector<double> medoid;
};
vector< vector<double> > adj;
int size, n;
double cost;
void getdata()
{
	ifstream in("Kmedoids.txt");
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
			double x = 0;
			for(int i =0 ; i < str.size(); i++) {
				if(str[i] == ' ') {
					stringstream cinn(temp);
					cinn>>x;
					temp = "";
					v.pb(x);
				} 
				temp += str[i];
			}
			adj.pb(v);
		}
	}
}
double manh(vector<double> v, vector<double> mean) 
{
	double ans = 0;
	for(int i = 0; i < v.size(); i++) {
		ans += abs(v[i] - mean[i]);
	}
	return ans;
}
bool check(vector<double> pt, vector< vector<double> > medoid, int k)
{
	for(int i = 0; i < k; i++) {
		int ct = 0;
		for(int j = 0; j < n; j++) {
			if(pt[j] == medoid[i][j]) {
				ct++;
			}
		}
		if(ct == n) {
			return true;
		}
	}
	return false;
}
double calc_cost(vector<vector<double> > medoid)
{
	int costt;
	for(int i = 0; i < adj.size(); i++) {
		double temp = 1000000;
		for(int j = 0 ; j < medoid.size(); j++) {
			temp = min(temp, manh(adj[i], medoid[j]));
		}
		costt += temp;
	}
	return costt;
}
void PAM(vector<vector<double> > medoid, int k, int num_iter)
{
	for(int itr = 0; itr < num_iter; itr++) {
		for(int i = 0; i < k; i++) {
			for(int j = 0; j < adj.size(); j++) {
				if(check(adj[j], medoid, k)) {
					continue;
				}
				vector< vector<double> > nmed = medoid;
				nmed[i] = adj[j];
				double costt = calc_cost(nmed);
				if(costt < cost) {
					medoid = nmed;
					break;
				}
			}
		}
	}
}
void form_cluster(cluster c[], int k, vector<vector <double> > medoid)
{
	for(int i = 0; i < k; i++) {
		c[i].medoid = medoid[i];
	}
	for(int i = 0; i < adj.size(); i++) {
		int id = 0;
		int minn = 10000000;
		for(int j = 0; j < k; j++) {
			if(manh(adj[i], medoid[j]) < minn) {
				minn = manh(adj[i], medoid[j]);
				id = j;
			}
		}
		c[id].points.pb(adj[i]);
	}
}
int main()
{
	int k, num_iter;
	cout<<"Enter K: ";
	cin>>k;
	cout<<"Number of iterations: ";
	cin>>num_iter;
	getdata();
	vector< vector<double> > medoid; 
	cluster c[k];
	srand (time(NULL));
	for(int i = 0; i < k; i++) {
		int id = rand() % size;
		medoid.pb(adj[id]);
	}
	cost = calc_cost(medoid);
	PAM(medoid, k, num_iter);
	// for(int i = 0; i < k; i++) {
	// 	cout<<"cluster "<<(i+1)<<"---------------------------------------------------------------------------"<<endl;
	// 	for(int j = 0; j < c[i].points.size(); j++) {
	// 		for(int p = 0; p < n; p++) {
	// 			cout<<c[i].points[j][p]<<" ";
	// 		}
	// 		cout<<endl;
	// 	}
	// }
	form_cluster(c, k, medoid);
	for(int i = 0; i < k; i++) {
		for(int j = 0 ; j < n; j++) {
			cout<<medoid[i][j]<<" ";
		}
		cout<<endl;
	}
}