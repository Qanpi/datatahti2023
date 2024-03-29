#include<iostream>
#include<vector>
#include<queue>
//#include<chrono>

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
	//auto start = chrono::high_resolution_clock::now();

	long long int sum = 0;
	for(int i=1; i<=n; i++) {
		if(field[i]) sum += djikstra(i);
	}
	cout << sum << endl;
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	//cout << duration.count() << endl;
}

int memo[2*100000+1];
int ready[2*100000+1];

int djikstra(int x) {
	priority_queue<pair<int, int>> q;
	bool visited[2*100000+1] = {false};

	q.push({0, x});

	int shortest = INF;
	while (!q.empty()) {
		int a = q.top().second, w = -q.top().first; q.pop();
		//cout << a;
		//cout << " " << shortest << " " << w << endl;
		visited[a] = true;

		if (w >= shortest) break;
		if(!field[a]) shortest = w;
		if (ready[a]) {
			shortest = min(shortest, w + memo[a]);
			continue;
		}

		for (auto u : adj[a]) {
			int b = u.first, c = u.second;
			
			if(!visited[b])	q.push({-(w+c), b});
		}
	}
	//cout << endl;

	memo[x] = shortest;
	ready[x] = true;
	return shortest;
}
