#include<iostream>

using namespace std;

int digits[10]; 
int factorial[5*100000] = {0};

bool check(int l);

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
	int l = 1;
	int scale = 100;
	int carry = 0;
	while(true) {
		for(int j=0; j<l; j++) {
			int val = factorial[j] * i;
			factorial[j] = (val+carry) % scale;
			carry = (val+carry) / scale;
		}

		while (carry > 0) {
			l++;
			factorial[l-1] = carry % scale;
			carry /= scale;
		}

		if(l > length/2 && check(l)) break;
		i++; 
	}
	
	cout << i << endl;
}

bool check(int l) {
	int count[10] = {};

	for(int i=0; i<l; i++) {
		int d = factorial[i];
		cout << d << " ";
		count[d]++;
	}
	cout << endl;

	for(int i=0; i<10; i++) {
		if(digits[i] != count[i]) return false;
	}

	return true;
}


