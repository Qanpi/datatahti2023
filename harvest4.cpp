#include<iostream>
#include<vector>

using namespace std;

bool field[2*100000+1];
vector<pair<int, int>> adj[2*100000+1];

int memo1[2*100000+1];
int memo2[2*100000+1];
int blacklist[2*100000+1];

const int INF = 10e7;

int dfs(int s, int e);
int dfs2(int s, int e);
int calls = 0;

int main() {
	cin.tie(0);
	//freopen("harvest15.txt", "r", stdin);

	int n;
	cin >> n;
	for (int i=1; i<=n; i++) {
		cin >> field[i];
	}

	for(int i=0; i<n-1; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back({b, c});
		adj[b].push_back({a, c});
	}

	long long int total_sum = 0;
	for (int i=1; i<=n; i++) {
		if (field[i]) {
			cout << i << " " << dfs(i, 0) << endl;
			break;
			//dfs(i, 0);
			dfs2(i, 0);
			total_sum += min(memo1[i], memo2[i]); 
		}
	}


	cout << total_sum << endl;
}

int dfs(int s, int e) {
	if(!field[s]) return 0;
	if(memo1[s] != 0) return memo1[s];

	int shortest = INF;
	for (auto u : adj[s]) {
		int a = u.first, c = u.second;
		if (a == e) continue;

		int path = dfs(a, s) + c;
		if (path < shortest) {
			shortest = path;
			blacklist[s] = a;
		}
	}

	if (shortest != INF) memo1[s] = shortest;
	return shortest;
}

int dfs2(int s, int e) {
	if(!field[s]) return 0;
	if(memo2[s] != 0) return memo2[s];

	int shortest = INF;
	for (auto u : adj[s]) {
		int a = u.first, c = u.second;
		if (a == e) continue;
		if (a == blacklist[s]) continue;

		shortest = min(shortest, dfs2(a, s) + c);
	}

	memo2[s] = shortest;
	return shortest;
}
