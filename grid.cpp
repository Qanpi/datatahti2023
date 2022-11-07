#include<iostream>
#include<chrono>
#include<algorithm>

using namespace std;
const int MOD = 1000000007;

int board[1001][1001];
int memo[1001][1001];
bool ready[1001][1001];
int sorted_x[1001][1001];
int sorted_y[1001][1001];
int n;

int recurse(int x, int y); 
int total_sum = 0;
//int recursive_calls = 0;

int main() {
	cin.tie(0);
	//freopen("grid1000.txt", "r", stdin);
	auto start = chrono::high_resolution_clock::now();
	cin >> n;

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
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

	cout << total_sum << endl;
	//cout << recursive_calls << endl;
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	//cout << duration.count() << endl;

}

int recurse(int x, int y) {
	if (ready[x][y]) {
		return memo[x][y];
	}

	int current = board[x][y];
	auto max_x_calls = lower_bound(sorted_x[x], sorted_x[x]+n, current) - sorted_x[x];
	auto max_y_calls = lower_bound(sorted_y[y], sorted_y[y]+n, current) - sorted_y[y];

	int x_calls = 0, y_calls = 0;
	int sum = 1;
	for (int i=0; i<n; i++) {
		if (y_calls > max_y_calls) break;
		if (current > board[i][y]) {
			sum += recurse(i, y);	
		}
		y_calls++;
	}

	for (int i=0; i<n; i++) {	
		if (x_calls > max_x_calls) break;
		if (current > board[x][i]) {
			sum += recurse(x, i);	
		}
		x_calls++;
	}

	sum %= MOD;
	memo[x][y] = sum;
	ready[x][y] = true;
	return sum;
}
