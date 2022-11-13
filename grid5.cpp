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

int tree_rows[1000][1001];
int tree_cols[1000][1001];

void recurse(int i, int j); 
int recursive_calls = 0;

int main() {
	cin.tie(0);
	//freopen("grid1000.txt", "r", stdin);
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
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			recurse(i, j);
		}
	}

	cout << recursive_calls << endl;
	cout << total_sum << endl;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	cout << duration.count() << endl;

}

int sum(int tree[], int k) {
	int s = 0;
	while (k >= 1) {
		s += tree[k];
		s %= MOD;
		k -= k&-k;
	}
	return s;
}


void add(int tree[], int k, int x) {
	while(k <= n) {
		tree[k] += x;
		tree[k] %= MOD;
		k += k&-k;
	}
}

void recurse(int i, int j) {
	if (visited[i][j]) return;
	visited[i][j] = true;

	int current = board[i][j];

	auto x_hi = lower_bound(sorted_cols[j], sorted_cols[j]+n, pair<int, int>{current, 0}) - sorted_cols[j];
	auto y_hi = lower_bound(sorted_rows[i], sorted_rows[i]+n, pair<int, int>{current, 0}) - sorted_rows[i];

	auto x_lo = lower_bound(sorted_cols[j], sorted_cols[j]+n, pair<int, int>{sorted_cols[j][x_hi-1].first, 0}) - sorted_cols[j];
	auto y_lo = lower_bound(sorted_rows[i], sorted_rows[i]+n, pair<int, int>{sorted_cols[i][y_hi-1].first, 0}) - sorted_rows[i];

	cout << "bounds hi: " << current << " " << x_hi << " " << y_hi << endl;
	cout << "bounds lo: " << current << " " << x_lo << " " << y_lo << endl;
	int y;
	for (y = y_hi; y > y_lo; y--) {
		recursive_calls++;
		int next_y = sorted_rows[i][y-1].second;
		recurse(i, next_y);
	}

	int x;
	for (x=x_hi; x > x_lo; x--) {
		int next_x = sorted_cols[j][x-1].second;
		recurse(next_x, j);
	}

	cout << x_lo << " " << y_lo <<endl;
	long int val = 0;
	val += sum(tree_cols[j], x_hi + 1); 
	//if (current == 3) cout << val << endl;
	val += sum(tree_rows[i], y_hi + 1); 
	val %= MOD;
	//if (current == 3) cout << val << endl;
	val++;

	cout << current << " (" << i << "," << j << "): " << val << endl;
	total_sum += val;
	total_sum %= MOD;

	add(tree_cols[j], x_hi + 1, val);
	add(tree_rows[i], y_hi + 1, val);
}
