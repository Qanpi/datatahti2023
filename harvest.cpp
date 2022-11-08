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
long long int dur = 0;

int main() {
	freopen("harvest100000.txt", "r", stdin);
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

	long long int sum = 0;
	for(int i=1; i<=n; i++) {
		if(field[i]) sum += djikstra(i);
	}
	cout << dur << endl;
	cout << sum << endl;
}

int memo[2*100000+1];
int ready[2*100000+1];

int djikstra(int x) {
	priority_queue<pair<int, int>> q;
	auto start = chrono::high_resolution_clock::now();
	int distance[2*100000+1] = {0};

	for (int i=1; i<=n; i++) {
		distance[i] = INF;
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	dur += duration.count();

	distance[x] = 0;
	q.push({0, x});

	//int shortest = INF;
	while (!q.empty()) {

		int a = q.top().second, w = -q.top().first; q.pop();

		//cout << "total: " << a << " " << w << endl;
		if(!field[a]) {
			memo[x] = w;
			ready[x] = true;
			return w;
			//shortest = min(shortest, w);
			//continue;
		}
		//if (w >= shortest) continue;
		if (ready[a]) {
			memo[x] = w + memo[a];
			ready[x] = true;
			return w + memo[a];
			//shortest = min(w + memo[a], shortest); 
			//continue;
		}
		//cout << a << " " << w << endl;

		for (auto u : adj[a]) {
			//if (u == x) continue;
			int b = u.first, c = u.second;
			
			//famous last words...
			distance[b] = distance[a]+c;
			q.push({-distance[b], b});
		}
	}

	//memo[x] = shortest;
	//ready[x] = true;
	return 0;
}
