#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define fi first
#define se second
vector<string>tree[107];
vector<vector<string>>table;
vector<vector<int>>ntable;
map<int,string>heading_mp;
map<string,int>mp[17];
map<int,string>rev_mp[17];
int attrcnt;
void read()
{
	string entry,attr;
	int cnt=0;
	while(getline(cin,entry))
	{
		stringstream ss;
		ss<<entry;
		vector<string>row;
		vector<int>v;
		while(getline(ss,attr,' ')) row.pb(attr),v.pb(0);
		if(cnt) {table.pb(row),ntable.pb(v);}
		else {for(int i=0;i<row.size();i++) heading_mp[i]=row[i];}
		cnt++;
	}
	attrcnt=table[0].size();
	for(int i=0;i<attrcnt;i++) for(int j=0;j<table.size();j++) {if(!mp[i][table[j][i]]) mp[i][table[j][i]]=j+1,rev_mp[i][j+1]=table[j][i];ntable[j][i]=mp[i][table[j][i]];}
	return ;
}
bool check_same(vector<vector<int>>&ntable)
{
	for(int i=1;i<ntable.size();i++) if(ntable[i][attrcnt-1]!=ntable[i-1][attrcnt-1]) return 0;
	return 1;
}
double eval_entropy(vector<vector<int>>&ntable)
{
	map<int,int>mp;
	for(int i=0;i<ntable.size();i++) mp[ntable[i][attrcnt-1]]++;
	double entropy=0;
	for(auto x:mp) if(x.se) entropy-=(x.se*1.0/ntable.size())*log2(x.se*1.0/ntable.size());
	return entropy;
}
void build(vector<vector<int>>&ntable,int lev)
{
	if(check_same(ntable))
	{
		//cout<<lev<<" "<<ntable.size()<<"\n";
		//for(int i=0;i<ntable.size();i++) for(int j=0;j<attrcnt;j++) cout<<rev_mp[j][ntable[i][j]]<<" \n"[j==attrcnt-1];
		tree[lev].pb(rev_mp[attrcnt-1][ntable[0][attrcnt-1]]);
		return ;
	}
	double cur_entropy=eval_entropy(ntable);
	double gain=0;
	int selected_attr=-1;
	for(int i=0;i<attrcnt-1;i++)
	{
		double tem_entropy=0;
		double norm=0;
		vector<vector<int>>nntable[mp[i].size()+5];
		for(int j=0;j<ntable.size();j++) nntable[ntable[j][i]].pb(ntable[j]);
		for(int j=0;j<mp[i].size()+5;j++) if(nntable[j].size()) tem_entropy+=(nntable[j].size()*1.0/ntable.size())*eval_entropy(nntable[j]),norm-=(nntable[j].size()*1.0/ntable.size())*log2((nntable[j].size()*1.0/ntable.size()));
		if((cur_entropy-tem_entropy)/norm>gain) gain=(cur_entropy-tem_entropy)/norm,selected_attr=i;
	}
	if(selected_attr==-1) { cout<<"here\n"; return ;}
	map<int,int>mpp;
	for(int i=0;i<ntable.size();i++) mpp[ntable[i][selected_attr]]++;
	for(auto x:mpp) tree[lev].pb(rev_mp[selected_attr][x.fi]);
	vector<vector<int>>nntable[mp[selected_attr].size()+5];
	for(int i=0;i<ntable.size();i++) nntable[ntable[i][selected_attr]].pb(ntable[i]);
	for(int i=0;i<mp[selected_attr].size()+5;i++) if(nntable[i].size()) build(nntable[i],lev+1);
	return ;
}
void print()
{
	for(int i=0;i<107;i++) if(tree[i].size()) for(int j=0;j<tree[i].size();j++) cout<<tree[i][j]<<" \n"[j==tree[i].size()-1];
}
int main()
{
	freopen("data.txt","r",stdin);
	read();
	cout<<ntable.size()<<" "<<attrcnt<<"\n";
	build(ntable,0);
	print();
	return 0;
}