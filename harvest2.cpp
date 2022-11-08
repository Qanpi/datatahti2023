#include<iostream>
#include<vector>
#include<queue>
#include<chrono>

using namespace std;

int n;
bool field[2*100000+1];
vector<pair<int, int>> adj[2*100000+1];
const int INF = 10e7;

int traverse(int s);

int main() {
	//freopen("harvest100000.txt", "r", stdin);
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

	traverse(4);
}

int traverse(int s) {
	priority_queue<pair<int, int>> q;

	bool visited[2*100000+1] = {};
	int shortest[2*100000+1];
	shortest[s] = 0;

	int prev = 0;
	q.push({0, s});
	while(!q.empty()) {
		int a = q.top().second, w = -q.top().first; q.pop();
		if (visited[a]) continue;
		visited[a] = true;
		cout << a << ": ";

		for (auto u : adj[a]) {
			int b = u.first, c = u.second;
			if (b == prev) continue;
			//cout << b << " ";

			if(c >= w) cout << w << endl;
			
			shortest[b] = shortest[a] + c;
			q.push({-shortest[b], b});

		}
		//cout << endl;
		prev = a;
	}
	return 0;
}
