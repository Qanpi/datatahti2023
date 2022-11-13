#include<iostream>
#include<vector>
#include<string>

using namespace std;

int sums[100];
const int range = 2023;
int test;

long long int count[58668];
vector<int> firsts[58668];
vector<vector<int>> solutions[range];

void solve();
void solve2(int target);
int recurse(int sum, bool visited[]);

int main() {
	freopen("list.txt", "r", stdin);

	for (int i=0; i<100; i++) {
		cin >> sums[i];
	}
	test = 9;

	solve();
	//bool visited[range] = {};
	//cout << recurse(3, visited) << endl;
}

void solve() {
	count[0] = 1;

	vector<vector<int>> start = {{0}};
	//start.push_back({1});
	solutions[0] = start;

	int calls = 0;
	for(int k=1; k<=range; k++) {
		//cout << k << endl;
		for(int sum=test; sum>=0; sum--) {
			calls++;
			if (sum - k >= 0 && count[sum - k] > 0) {
				count[sum] += count[sum - k];	
				//cout << "sum: " << sum << " k: " << k << endl;

				for (vector<int> s : solutions[sum - k]) {
					if (s.size() > 43) continue;
					vector<int> new_s = s;
					new_s.push_back(k);

					//for (auto u : new_s) cout << u << " ";
					//cout << endl;
					solutions[sum].push_back(new_s);
				}
				//firsts[sum].push_back(k);
			}
		}	
	}
	cout << count[test] << endl;
	cout << calls << endl;
	cout << endl;

	//for (int c : count) cout << c << endl;
	//return;

	for (auto s : solutions[test]) {
		for (auto u : s) cout << u << " ";
		cout << endl;
	}
	//solve2(test);
}

//vector<vector<int>> 
void solve2(int target) {
	//if (target == 0) return vector<vector<int>> {{}};

	//vector<vector<int>> total;
	for(int i=0; i<firsts[target].size(); i++) {
		int n = firsts[target][i];
		//total.push_back(vector<int>{n});
		cout << n << " ";
		//vector<vector<int>> s = 
		solve2(target - n);
	}

	//solutions[target]
	cout << endl;
}


int recurse(int sum, bool visited[]) {
	if (sum < 0) return 0;
	if (sum == 0) return 1;

	int count = 0;
	for(int k=1; k<=range; k++) {
		if (visited[k]) continue;

		bool new_visited[range];
		copy(visited, visited + range, new_visited);
		new_visited[k] = true;

		count += recurse(sum - k, new_visited);
	}
	return count;
}

