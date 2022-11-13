#include<iostream>
#include<chrono>
#include<algorithm>

using namespace std;
const int MOD = 1000000007;

int n;
int board[1000][1000];
bool visited[1000][1000];
int total_sum;

pair<int, int> sorted_rows[1000][1000];
pair<int, int> sorted_cols[1000][1000];

int memo[1000][1000];
bool ready[1000][1000];

int recurse(int i, int j); 
int recursive_calls = 0;

int main() {
	cin.tie(0);
	freopen("grid1000.txt", "r", stdin);
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

	auto start = chrono::high_resolution_clock::now();
	for(int i=0; i<n; i++) {
		sort(sorted_rows[i], sorted_rows[i]+n);
		sort(sorted_cols[i], sorted_cols[i]+n);
	}


	//for future, maybe somehow sort the rows and cols and go from there
	long long int total_sum = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			total_sum += recurse(i, j);
		}
	}

	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

	cout << total_sum << endl;
	cout << "calls: " << recursive_calls << endl;
	cout << "dur: " << duration.count() << endl;
}

int recurse(int i, int j) {
	if (ready[i][j]) return memo[i][j];
	ready[i][j] = true;

	int current = board[i][j];
	pair<int, int> key = {current, 0};
	auto x_hi = lower_bound(sorted_rows[i], sorted_rows[i]+n, key) - sorted_rows[i];
	auto y_hi = lower_bound(sorted_cols[j], sorted_cols[j]+n, key) - sorted_cols[j];

	//cout << current << " " << x_hi << " " << y_hi << endl;
	//cout << sorted_rows[i][x_hi-1].first << endl; 
	//cout << sorted_cols[j][y_hi-1].first << endl;

	pair<int, int> x_key = {sorted_rows[i][x_hi-1].first, 0};
	pair<int, int> y_key = {sorted_cols[j][y_hi-1].first, 0};
	auto x_low = lower_bound(sorted_rows[i], sorted_rows[i]+n, x_key) - sorted_rows[i]; 
	auto y_low = lower_bound(sorted_cols[j], sorted_cols[j]+n, y_key) - sorted_cols[j]; 

	int sum = 1;
	for(int x = 0; x<x_hi; x++) {
		recursive_calls++;
		int next = sorted_rows[i][x].second;
		//cout << current << " next x: " << next << endl;
		sum += recurse(i, next);
	}

	for(int y = 0; y<y_hi; y++) {
		recursive_calls++;
		int next = sorted_cols[j][y].second;
		//cout << current << " next y: " << next << endl;
		sum += recurse(next, j);
	}
	
	//cout << current << ": " << sum << endl;
	memo[i][j] = sum;
	return sum;
//	cout << x_hi << " " << y_hi << endl;
//
//	int x_sum = memo_rows[i][x_hi-1];
//	cout << "res x: " << x_sum << endl;
//	int y_sum = memo_cols[j][y_hi-1];
//	cout << "res y: " << y_sum << endl;
//	int sum = x_sum + y_sum + 1;
//
//	memo_rows[i][x_hi] += x_sum + sum;
//	memo_cols[j][y_hi] += y_sum + sum;
//	cout << "res : " << x_sum + y_sum + 1 << endl;
	

}
