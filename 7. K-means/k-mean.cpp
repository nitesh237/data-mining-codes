#include<bits/stdc++.h>
#define pb push_back
using namespace std;
struct cluster
{
	vector< vector<double> > points;
	vector<double> mean;
};
vector< vector<double> > adj;
int size, n;
void getdata()
{
	ifstream in("Kmeans.txt");
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
double eucl(vector<double> v, vector<double> mean) 
{
	double ans = 0;
	for(int i = 0; i < v.size(); i++) {
		ans += (v[i] - mean[i])*(v[i] - mean[i]);
	}
	ans = sqrt(ans);
	return ans;
}
void kmeans(cluster c[], int k, int num_iter)
{
	for(int p = 0; p < num_iter; p++) {
		for(int i = 0; i < k; i++) {
			c[i].points.clear();
		}
		for(int i = 0; i < size; i++) {
			double min = 1e7;
			int id = 0;
			for(int j = 0; j < k; j++) {
				double dis = eucl(adj[i], c[j].mean);
				if(dis < min) {
					min = dis;
					id = j;
				}
			}
			c[id].points.pb(adj[i]);
		}
		for(int i = 0; i < k; i++) {
			vector<double> sum;
			for(int j = 0; j < n; j++) {
				sum.pb(0);
			}
			for(int j = 0; j < c[i].points.size(); j++) {

				for(int q = 0; q < n; q++) {
					sum[q] += c[i].points[j][q];
				}
			}
			for(int j = 0 ; j < n; j++) {
				if(c[i].points.size() == 0) {
					continue;
				}
				sum[j] = sum[j]/c[i].points.size();
			}
			c[i].mean = sum;
		}
	}
}
int main()
{
	int k, num_iter;
	cout<<"Enter K: ";
	cin>>k;
	cout<<"Enter Number of Iterations:";
	cin>>num_iter;
	getdata();
	cluster c[k];
	srand (time(NULL));
	for(int i = 0; i < k; i++) {
		int id = rand() % size;
		c[i].mean = adj[id];
	}
	kmeans(c, k, num_iter);
	for(int i = 0; i < k; i++) {
		cout<<"cluster "<<(i+1)<<"---------------------------------------------------------------------------"<<endl;
		for(int j = 0; j < c[i].points.size(); j++) {
			for(int p = 0; p < n; p++) {
				cout<<c[i].points[j][p]<<" ";
			}
			cout<<endl;
		}
	}
}