#include<iostream>
#include<vector>
#include<stack>
#include<chrono>
#include<algorithm>

using namespace std;

int n;
const int MOD = 1000000007;

int board[1000][1000];

int sorted_x[1000][1000];
int sorted_y[1000][1000];

bool visited[1000][1000];
stack<pair<int, int>> topomemo;

vector<pair<int, int>> adj[1000][1000];
int paths[1000][1000];

void topo(int x, int y);

int main() {
	freopen("grid100.txt", "r", stdin);
	cin >> n;

	for (int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			int val;
			cin >> val;
			board[i][j] = val;
			sorted_x[i][j] = val;
			sorted_y[j][i] = val;
		}
	}

	for(int i=0; i<n; i++) {
		sort(sorted_x[i], sorted_x[i]+n);
		sort(sorted_y[i], sorted_y[i]+n);
	}

	auto start = chrono::high_resolution_clock::now();

	for (int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			topo(i, j);
			//cout << adj[i][j][0].first << " ";
			//cout << adj[i][j]<< endl;
		}
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	cout << duration.count() << endl;
	cout << endl;


	auto start2 = chrono::high_resolution_clock::now();
	long long int total_sum = 0;
	while(!topomemo.empty()) {
		int x = topomemo.top().first, y = topomemo.top().second;
		topomemo.pop();
		cout << board[x][y] << " ";
		//cout << x << " " << y << ": " ;
		
		long long int sum = 1;
		for(auto u : adj[x][y]) {
			int nx = u.first, ny = u.second;
			//cout << nx << " " << ny << ", "; 
			sum += paths[nx][ny];
			sum %= MOD;
		}	

		//cout << sum << endl;
		paths[x][y] = sum;

		total_sum += sum;
		total_sum %= MOD;
	}

	auto end2 = chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration_cast<chrono::microseconds>(end2-start2);
	cout << endl;
	cout << duration2.count() << endl;

	cout << total_sum << endl;
}

void topo(int x, int y) {
	if (visited[x][y]) return;
	visited[x][y] = true;

	int curr = board[x][y];

	for (int k=0; k<n; k++) {
		if (board[x][y] >= board[x][k]) continue;
		topo(x, k);
		adj[x][k].push_back({x, y});
	}

	for (int k=0; k<n; k++) {
		if (board[x][y] >= board[k][y]) continue;
		topo(k, y);
		adj[k][y].push_back({x, y});
	}

	topomemo.push({x, y});
}
