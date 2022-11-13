#include<iostream>
#include<chrono>
 
using namespace std;
const int MOD = 1000000007;
 
int board[1000][1000];
long long int memo[1001][1001];
int n;
 
int recurse(int x, int y); 
 
int main() {
	freopen("grid100.txt", "r", stdin);
	cin >> n;
 
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cin >> board[i][j];
		}
	}

	auto start = chrono::high_resolution_clock::now();
 
	long long int sum = 0;
	//for future, maybe somehow sort the rows and cols and go from there
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (memo[i][j] != 0) {
				sum += memo[i][j];
			} else {
				sum += recurse(i, j);
			}
			sum %= MOD;
		}
	}
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end-start);

 
	cout << sum << endl;
	cout << duration.count() << endl;
 
}
 
int recurse(int x, int y) {
	if (memo[x][y] != 0) {
		return memo[x][y];
	}
 
	int current = board[x][y];
	long long int sum = 1;
	for (int i=0; i<n; i++) {
		if (current > board[i][y]) {
			sum += recurse(i, y);	
		}
	}
 
	for (int i=0; i<n; i++) {	
		if (current > board[x][i]) {
			sum += recurse(x, i);	
		}
	}

	//cout << current << " (" << x << "," << y << "): " << sum << endl;
 
	sum %= MOD;
	memo[x][y] = sum;
	return sum;
}
