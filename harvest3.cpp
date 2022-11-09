#include<iostream>
#include<vector>
#include<queue>
#include<chrono>
 
using namespace std;
 
int n;
bool field[2*100000+1];
vector<pair<int, int>> adj[2*100000+1];
const int INF = 10e7;
 
int djikstra(int x);
 
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
	auto start = chrono::high_resolution_clock::now();
 
	long long int sum = 0;
	for(int i=1; i<=n; i++) {
		if(field[i]) {
			int res = djikstra(i);
			cout << i << " " << res << endl;
			sum += res;
		}

	}
	cout << sum << endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	cout << duration.count() << endl;
}
 
int memo[2*100000+1];
 
int djikstra(int x) {
	priority_queue<pair<int, int>> q;
	int distance[2*100000+1] = {0};
 
	for (int i=1; i<=n; i++) {
		distance[i] = INF;
	}
 
	distance[x] = 0;
	q.push({0, x});
 
	int shortest = INF;
	while (!q.empty()) {
		int a = q.top().second, w = -q.top().first; q.pop();
 
		if (w >= shortest) {
			memo[x] = shortest;
			return shortest;
		};
		if (memo[a] != 0) {
			shortest = min(w + memo[a], shortest); 
			continue;
		}
		if(!field[a]) {
			memo[x] = w;
			return w;
		}
 
		for (auto u : adj[a]) {
			int b = u.first, c = u.second;
			
			//famous last words...
			if (distance[a]+c < distance[b]) {
				distance[b] = distance[a]+c;
				q.push({-distance[b], b});
			}
		}
	}
 
	memo[x] = shortest;
	return shortest;
}
