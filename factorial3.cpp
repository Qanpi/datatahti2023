#include<iostream>
#include<chrono>

using namespace std;

int digits[10]; 
int factorial[5*100000] = {0};

bool check(int l);

int main() {
	auto start = chrono::high_resolution_clock::now();
	cin.tie(0);
	int length = 0;

	for (int i=0; i<10; i++) {
		int l; 
		cin >> l;

		digits[i] = l;
		length += l;
	}	

	factorial[0] = 2;

	int i = 3;
	int l = 1;
	while(true) {
		if (l == length) {
			int count[10] = {};

			for(int i=0; i<l; i++) {
				int d = factorial[i];
				count[d]++;
			}

			bool match = true;
			for(int i=0; i<10; i++) {
				if(digits[i] != count[i]) match = false;
			}
			
			if(match) break;
		}

		int carry = 0;
		for(int j=0; j<l; j++) {
			int val = factorial[j] * i;
			factorial[j] = (val+carry) % 10;
			carry = (val+carry) / 10;
		}

		while (carry > 0) {
			l++;
			factorial[l-1] = carry % 10;
			carry /= 10;
		}

		i++; 
	}
	
	cout << i-1 << endl;
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
	cout << duration.count() << endl;
}

