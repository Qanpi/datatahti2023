#include<iostream>
#include<vector>

using namespace std;

int digits[10]; 
int factorial[100000]; 
int scale = 100000;
int l = 1;

bool check();

int main() {
	cin.tie(0);
	int length = 0;

	for (int i=0; i<10; i++) {
		int l; 
		cin >> l;

		digits[i] = l;
		length += l;
	}	

	factorial[0] = 1;

	int i = 2;
	int carry = 0;
	while(true) {
		for(int j=0; j<l; j++) {
			int val = factorial[j] * i;
			factorial[j] = (val+carry) % scale;
			carry = (val+carry) / scale;
		}

		while (carry > 0) {
			l++;
			factorial[l-1] = (carry % scale);
			carry /= scale;
		}

		if(l >= length/5 && check()) break;
		i++; 
	}
	
	cout << i << endl;
}

bool check() {
	int count[10] = {};

	for(int i=0; i<l; i++) {
		int factor = factorial[i];

		int added = 5;
		while (factor > 0) {
			count[factor%10]++;
			factor /= 10;
			added--;
		}
		if(i != l-1) count[0]+=added;
	}

	for(int i=0; i<10; i++) {
		if(digits[i] != count[i]) return false;
	}

	return true;
}


