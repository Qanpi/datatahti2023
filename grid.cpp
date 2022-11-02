#include<iostream>

using namespace std;

int board[1000][1000];
int memo[1001][1001];
int n;

int recurse(int x, int y); 

int main() {
	cin >> n;

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			cin >> board[i][j];
		}
	}

	int sum = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			sum += recurse(i, j);
		}
	}

	cout << sum << endl;

}

int recurse(int x, int y) {
	if (memo[x][y] != 0) return memo[x][y];

	int current = board[x][y];
	int sum = 1;
	for (int i=0; i<n; i++) {
		if (current > board[i][y])
			sum += recurse(i, y);	
	}

	for (int i=0; i<n; i++) {	
		if (current > board[x][i])
			sum += recurse(x, i);	
	}

	memo[x][y] = sum;
	return sum;
}
