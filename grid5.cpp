#include<iostream>
//#include<chrono>
#include<algorithm>

using namespace std;
const int MOD = 1000000007;

int n;
int board[1000][1000];
bool visited[1000][1000];

pair<int, int> sorted_rows[1000][1000];
pair<int, int> sorted_cols[1000][1000];

int tree_rows[1000][1000];
int tree_cols[1000][1000];

void recurse(int i, int y); 
int sum(int tree[], int k);
int recursive_calls = 0;

int main() {
	cin.tie(0);
	//freopen("grid100.txt", "r", stdin);
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
			recurse(i, j);
		}
	}

	for (int i=0; i<n; i++) {
		cout << sum(tree_rows[i], 1)  << " ";
	}
	cout << endl;

	cout << total_sum << endl;
	cout << recursive_calls << endl;
	//auto end = chrono::high_resolution_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end-start);
	//cout << duration.count() << endl;

}

int sum(int tree[], int k) {
	int s = 0;
	while (k >= 1) {
		s += tree[k];
		k -= k&-k;
	}
	return s;
}


void add(int tree[], int k, int x) {
	while(k <= n) {
		tree[k] += x;
		k += k&-k;
	}
}

void recurse(int i, int j) {
	if (visited[i][j]) return;
	visited[i][j] = true;

	int current = board[i][j];

	pair<int, int> key = {current, 0};
	//for (int k=0; k<n; k++) cout << sorted_cols[j][k].first << " ";
	auto x = lower_bound(sorted_cols[j], sorted_cols[j]+n, key) - sorted_cols[j];
	auto y = lower_bound(sorted_rows[i], sorted_rows[i]+n, key) - sorted_rows[i];
	//cout << "bounds: " << current << " " << x << " " << y << endl;

	if (x == 0 && y == 0) {
		add(tree_cols[j], 1, 1);
		add(tree_rows[i], 1, 1);
		return;
	}

	recursive_calls++;
	if (y > 0) {
		int next_y = sorted_rows[i][y-1].second;
		//cout << next_y << endl;
		recurse(i, next_y);
	}

	if (x > 0) {
		int next_x = sorted_cols[j][x-1].second;
		recurse(next_x, j);
	}


	int val = 0;
	val += sum(tree_cols[j], x); 
	val += sum(tree_rows[i], y); 
	val++;

	cout << current << ": " << val << endl;
	add(tree_cols[j], x+1, val);
	add(tree_rows[i], y+1, val);

	return;



	//for(int y=y_bound-1; y>=0; y--) {
	//	int next_y = sorted_rows[i][y].second; 
	//	//cout << "next x move: " << current << " " << next_y << " " << j << endl;
	//	sum += recurse(i, next_y); 
	//	sum %= MOD;
	//}

	//for(int x=x_bound-1; x>=0; x--) {
	//	int next_x = sorted_cols[j][x].second; 
	//	//cout << current << " " << i << " " << next_y << endl;
	//	sum += recurse(next_x, j); 
	//	sum %= MOD;
	//}

	//cout << endl;
	//cout << current << ": " << sum << endl;

	//memo[i][j] = sum;
	//ready[i][j] = true;
	return;
}
