#include<iostream>
#include<vector>

using namespace std;

bool field[2*100000+1];
vector<pair<int, int>> adj[2*100000+1];

int down[2*100000+1];
int up[2*100000+1];
const int INF = 10e7;

void dfs(int s, int e);
void dfs2(int s, int e);

int calls = 0;

int main() {
	cin.tie(0);
	//freopen("harvest10.txt", "r", stdin);

	int n;
	cin >> n;
	for (int i=1; i<=n; i++) {
		cin >> field[i];
		up[i] = INF;
	}

	for(int i=0; i<n-1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	long long int total_sum = 0;

	dfs(1, 0);
	dfs2(1, 0);

	for (int i=1; i<=n; i++) {
		if (field[i]) {
			int res = min(down[i], up[i]);
			//cout << i << " " << res << endl;
			total_sum += res;
		}
	}

	cout << total_sum << endl;
}

void dfs(int s, int e) {
	if(field[s]) down[s] = INF;

	for (auto u : adj[s]) {
		int a = u.first, c = u.second;
		if (a == e) continue;

		dfs(a, s);
		if (down[a] + c < down[s]) {
			down[s] = down[a]+c;
		//	blacklist[s] = a;
		}
	}
	//cout << s << " " << down[s] << endl;
}

//void other(int s, int e) {
//	if(field[s]) down_2[s] = INF;
//
//	for (auto u : adj[s]) {
//		int a = u.first, c = u.second;
//		if (a == e) continue;
//		if (a == blacklist[s]) continue;
//
//		dfs(a, s);
//		down_2[s] = min(down_2[s], down[a] + c);
//	}
//	//cout << s << " " << down_2[s] << endl;
//}

void dfs2(int s, int e) {
	if (!field[s]) up[s] = 0;

	for (auto u : adj[s]) {
		int a = u.first, c = u.second;
		if (a == e) continue;
		
		if (field[a]) up[a] = min(up[s] + c, down[s] + c);
		dfs2(a, s);
	}	
	//cout << s << " " << up[s] << endl;
}

//int dfs2(int s, int e) {
//	if(!field[s]) return 0;
//	if(memo2[s] != 0) return memo2[s];
//
//	int shortest = INF;
//	for (auto u : adj[s]) {
//		int a = u.first, c = u.second;
//		if (a == e) continue;
//		if (a == blacklist[s]) continue;
//
//		shortest = min(shortest, dfs2(a, s) + c);
//	}
//
//	memo2[s] = shortest;
//	return shortest;
//}
