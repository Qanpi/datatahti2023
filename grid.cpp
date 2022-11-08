#include<iostream>
#include<chrono>
#include<algorithm>

using namespace std;
const int MOD = 1000000007;

int board[1001][1001];
int memo[1001][1001];
bool ready[1001][1001];
int n;

int recurse(int x, int y); 
int total_sum = 0;
int recursive_calls = 0;
int useless_calls = 0;

int main() {
	cin.tie(0);
	freopen("grid1000.txt", "r", stdin);
	auto start = chrono::high_resolution_clock::now();
	cin >> n;

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int val;
			cin >> val;
			board[i][j] = val;
		}
	}

	//for future, maybe somehow sort the rows and cols and go from there
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (ready[i][j]) {
				total_sum += memo[i][j];
			} else {
				total_sum += recurse(i, j);
			}
			total_sum %= MOD;
		}
	}

			auto end = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

	cout << total_sum << endl;
	cout << recursive_calls << endl;
	cout << useless_calls << endl;
	cout << duration.count() << endl;

}

int recurse(int x, int y) {
	if (ready[x][y]) {
		return memo[x][y];
	}

	int current = board[x][y];

	recursive_calls++;
	int sum = 1;
	for (int i=0; i<n; i++) {
		if (current > board[i][y]) {
			sum += recurse(i, y);	
		}
		if (current > board[x][i]) {
			sum += recurse(x, i);	
		}
		if (current <= board[i][y] && current <= board[x][i]) useless_calls++;
	}

	sum %= MOD;
	memo[x][y] = sum;
	ready[x][y] = true;
	return sum;
}
