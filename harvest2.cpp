#include<iostream>
#include<vector>
//#include<chrono>

using namespace std;

int n;
vector<pair<int, int>> adj[2*100000+1];
const int INF = 10e7;

int traverse(int s, int e);

int memo[2*100000+1];
int pred[2*100000+1];
bool ready[2*100000+1];
bool field[2*100000+1];

int main() {
	freopen("harvest15.txt", "r", stdin);
	cin.tie(0);
	cin >> n;

	for(int i=1; i<=n; i++) {
		cin >> field[i];
	}

	for(int i=0; i<n-1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	//auto start = chrono::high_resolution_clock::now();
	
	long long int total_sum = 0;

	for(int i=1; i<=n; i++) {
		if (field[i]) {
			int res = traverse(i, 0);
			cout << i << " " << res << " " << pred[i] << endl;
			total_sum += res;
		}
	}
	
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

	cout << total_sum << endl;
	//cout << duration.count() << endl;
}


int traverse(int s, int e) {
	if(!field[s]) return 0;
	if(ready[s]) {
		cout << "memo" << endl;
		return memo[s];
	}

	int shortest = INF;

	for (auto u : adj[s]) {
		int a = u.first, c = u.second;
		if (a == e) continue;
		pred[a] = s;
		shortest = min(shortest, traverse(a, s) + c);
	}
	//cout << s << " " << shortest << endl;

	if (shortest != INF) {
		memo[s] = shortest;
		ready[s] = true;
	}
	return shortest;
}
