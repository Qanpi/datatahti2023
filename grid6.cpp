#include<iostream>
//#include<chrono>
#include<algorithm>

using namespace std;
const int MOD = 1000000007;

int n;
int board[1000][1000];
bool visited[1000][1000];
int total_sum;

pair<int, int> sorted_rows[1000][1000];
pair<int, int> sorted_cols[1000][1000];

int tree_rows[1000][1000];
int tree_cols[1000][1000];

void recurse(int i, int j); 
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

	//auto start = chrono::high_resolution_clock::now();
	for(int i=0; i<n; i++) {
		sort(sorted_rows[i], sorted_rows[i]+n);
		sort(sorted_cols[i], sorted_cols[i]+n);
	}


	//for future, maybe somehow sort the rows and cols and go from there
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			recurse(i, j);
		}
	}

	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

	cout << total_sum << endl;
	//cout << "calls: " << recursive_calls << endl;
	//cout << "dur: " << duration.count() << endl;
}

int sum_rows(int i, int k) {
	int s = 0;
	while (k >= 1) {
		s += tree_rows[i][k];
		s %= MOD;
		k -= k&-k;
	}
	return s;
}

int sum_cols(int j, int k) {
	int s = 0;
	while (k >= 1) {
		s += tree_cols[j][k];
		s %= MOD;
		k -= k&-k;
	}
	return s;
}

void add_rows(int i, int k, int x) {
	while(k <= n) {
		tree_rows[i][k] += x;
		tree_rows[i][k] %= MOD;
		k += k&-k;
	}
}

void add_cols(int j, int k, int x) {
	while(k <= n) {
		tree_cols[j][k] += x;
		tree_cols[j][k] %= MOD;
		k += k&-k;
	}
}
void recurse(int i, int j) {
	if (visited[i][j]) return;
	visited[i][j] = true;

	int current = board[i][j];
	pair<int, int> key = {current, 0};
	auto x_hi = lower_bound(sorted_rows[i], sorted_rows[i]+n, key) - sorted_rows[i];
	auto y_hi = lower_bound(sorted_cols[j], sorted_cols[j]+n, key) - sorted_cols[j];

	//if (x_hi == 0 && y_hi == 0) {
	//	add(tree_rows[i], 1, 1);
	//	add(tree_cols[j], 1, 1);
	//	return;
	//}
	//cout << current << " " << x_hi << " " << y_hi << endl;
	//cout << sorted_rows[i][x_hi-1].first << endl; 
	//cout << sorted_cols[j][y_hi-1].first << endl;

	pair<int, int> x_key = {sorted_rows[i][x_hi-1].first, 0};
	pair<int, int> y_key = {sorted_cols[j][y_hi-1].first, 0};
	auto x_low = lower_bound(sorted_rows[i], sorted_rows[i]+n, x_key) - sorted_rows[i]; 
	auto y_low = lower_bound(sorted_cols[j], sorted_cols[j]+n, y_key) - sorted_cols[j]; 


	for(int x = x_low; x<x_hi; x++) {
		recursive_calls++;
		int next = sorted_rows[i][x].second;
		//cout << current << " next x: " << next << endl;
		recurse(i, next);
	}

	for(int y = y_low; y<y_hi; y++) {
		recursive_calls++;
		int next = sorted_cols[j][y].second;
		//cout << current << " next y: " << next << endl;
		recurse(next, j);
	}

	int x_sum = sum_rows(i, x_hi);
	int y_sum = sum_cols(j, y_hi);
	int sum = (x_sum + y_sum) % MOD + 1;

	add_rows(i, x_hi + 1, sum);
	add_cols(j, y_hi + 1, sum);
	
	total_sum += sum;
	total_sum %= MOD;
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
