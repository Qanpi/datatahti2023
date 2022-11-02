#include <iostream>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	bool found_top_left = false;
	bool cows[101][101] = {}; //do not leave uninitialized!
	pair<int, int> top_left; 
	pair<int, int> bottom_right;

	for(int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			char ch;
			cin >> ch;
			if (ch == '*') {
				if (!found_top_left) {
					top_left = {j, i};
					found_top_left = true;
				} else {
					bottom_right = {j, i};
				} 
			} else if (ch == '@') {
				cows[i][j] = true;
			}

		}
	}

	int count = 0;

	int x1 = top_left.first, y1 = top_left.second;
	int x2 = bottom_right.first, y2 = bottom_right.second;
	for(int i=y1+1; i<y2; i++) {
		for (int j=x1+1; j<x2; j++) {
			if (cows[i][j]) count++;
		}
	}

	cout << count << endl;
}
