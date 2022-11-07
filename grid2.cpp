#include<iostream>
#include<algorithm>

using namespace std;

int board[1000][1000];
int tab[1000][1000];
int tab_temp[1000][1000];

int main() {
	freopen("grid1000.txt", "r", stdin);
	int n;
	cin >> n;


	for (int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			int d;
			cin >> d;
			board[i][j] = d;
		}
	}

	int sum = 0;

//	int rows[100][1000] = {0};
//	int cols[100][1000] = {0};

	for (int x=1; x<=n*n; x++) {
		if (x % 1000 == 0) cout << x << endl;
		for(int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				if (board[i][j] != x) continue;
				int val = 0;
				for(int k=0; k<n; k++) {
					val += tab[i][k];
					val += tab[k][j];
				}
				val++;

				tab_temp[i][j] = val;

				sum += val;
//				int prev_sum = 0;
//
//				for (int y=1; y<x; y++) {
//					prev_sum += rows[i][y];
//					prev_sum += cols[j][y];
//				}
//
//				int new_sum = prev_sum + 1;
//				rows[i][x] += new_sum;
//				cols[j][x] += new_sum;
//
//				sum += new_sum;

			}
		}
		for(int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				tab[i][j] = tab_temp[i][j];
			}
		}
	}

	cout << sum << endl;
	//combinations
	//3
	//3 -> 1
	//3 -> 2
	//3 -> 2 -> 1
}
