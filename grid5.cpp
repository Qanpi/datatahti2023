#include<iostream>
//#include<chrono>
#include<algorithm>

using namespace std;
const int MOD = 1000000007;

int n;
int board[1001][1001];

pair<int, int> sorted_rows[1000][1000];
pair<int, int> sorted_cols[1000][1000];

int memo[1001][1001];
bool ready[1001][1001];

int recurse(int i, int y); 
int recursive_calls = 0;

int main() {
	cin.tie(0);
	freopen("grid100.txt", "r", stdin);
	//auto start = chrono::high_resolution_clock::now();
	cin >> n;

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int val;
			cin >> val;
			board[i][j] = val;
			sorted_rows[i][j] = {val, j};
			sorted_cols[j][i] = {val, i};
		}
	}

	for(int i=0; i<n; i++) {
		sort(sorted_rows[i], sorted_rows[i]+n);
		sort(sorted_cols[i], sorted_cols[i]+n);
	}


	//for future, maybe somehow sort the rows and cols and go from there
	int total_sum = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			total_sum += recurse(i, j);
			total_sum %= MOD;
		}
	}

	cout << total_sum << endl;
	cout << recursive_calls << endl;
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	//cout << duration.count() << endl;

}

int recurse(int i, int j) {
	if (ready[i][j]) return memo[i][j];

	int current = board[i][j];
	int sum = 1;

	pair<int, int> key = {current, 0};
	//for (int k=0; k<n; k++) cout << sorted_cols[j][k].first << " ";
	auto x_bound = lower_bound(sorted_cols[j], sorted_cols[j]+n, key) - sorted_cols[j];
	auto y_bound = lower_bound(sorted_rows[i], sorted_rows[i]+n, key) - sorted_rows[i];

	//cout << "bounds: " << current << " " << x_bound << " " << y_bound << endl;
	recursive_calls++;
	for(int y=y_bound-1; y>=0; y--) {
		int next_y = sorted_rows[i][y].second; 
		//cout << "next x move: " << current << " " << next_y << " " << j << endl;
		sum += recurse(i, next_y); 
		sum %= MOD;
	}

	for(int x=x_bound-1; x>=0; x--) {
		int next_x = sorted_cols[j][x].second; 
		//cout << current << " " << i << " " << next_y << endl;
		sum += recurse(next_x, j); 
		sum %= MOD;
	}

	//cout << endl;

	memo[i][j] = sum;
	ready[i][j] = true;
	return sum;
}
