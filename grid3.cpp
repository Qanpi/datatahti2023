#include<iostream>
#include<algorithm>

using namespace std;

int board[1001][1001];
int sorted_x[1001][1001];
int sorted_y[1001][1001];

int recurse(int x, int y);

int main() {
	//freopen("grid1000.txt", "r", stdin);
	int n;
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

	int sum = 0;
	for (int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			recurse(i, j);
		}
	}
	cout << sum << endl;
	cout << "test" << endl;
}

int recurse(int x, int y) {
	if (x == 0) return 1;

	int val = board[i][j];		

	auto x = lower_bound(sorted_x[i], sorted_x[i]+n, val) - sorted_x[i];
	auto y = lower_bound(sorted_y[j], sorted_y[j]+n, val) - sorted_y[j];

	for (int i=x-1; i>=0; i--){
		if (sorted_x[x] > sorted_x[i]) {
			sum += recurse(sorted, i);
		}	
	}

	int x_paths = recurse(sorted_x[i], x);
	int y_paths = recurse(sorted_y[j], y);

	cout << x_paths-1 << " " << y_paths << endl;
	sum += x_paths + y_paths - 1;

	int sum = 1;


	return sum;
}

  
