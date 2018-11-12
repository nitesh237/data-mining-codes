#include <bits/stdc++.h>
#define ipair pair<int, int>
using namespace std;

int main() {
	ipair p = mp(2, 3);
	ipair k = mp(3, 4);
	ipair ans = p + k;
	cout << ans.ff << " " << ans.ss << endl;
	return 0;
}