#include<iostream>
#include<vector>

using namespace std;

int digits[10]; 
vector<int> factorial;

bool check(int n5, int n2);
void multiply(int i);

int main() {
	cin.tie(0);
	int length = 0;

	for (int i=0; i<10; i++) {
		int l; 
		cin >> l;

		digits[i] = l;
		length += l;
	}	

	factorial.push_back(2);

	int i = 3;
	int n2 = 0, n5 = 0;
	int lo = 1, hi = 2;
	while(true) {
		if(length >= lo && check(n5, n2)) break;

		int length_counter = i;
		while (length_counter > 0) {
			lo++;
			hi++;
			length_counter /= 10;
		}
		lo--;

		if (i % 5 == 0) {
			for (int j=1; j<=i; j*=5) {
				if (i/j % 5 != 0) break;
				n5++;
			}
			i++;
			continue;
		} 

		if (i % 2 == 0) {
			for (int j=1; j<=i; j*=2) {
				if (i/j % 2 != 0) break;
				n2++;
			}
			i++;
			continue;
		}

		multiply(i);

		cout << i << " " << lo << " " << hi << endl;
		i++; 
	}
	
	cout << i-1 << endl;
}

void multiply(int i) {
	int carry = 0; 
	int l = factorial.size();

	for(int j=0; j<l; j++) {
		int val = factorial[j] * i;
		factorial[j] = (val+carry) % 10;
		carry = (val+carry) / 10;
	}


	while (carry > 0) {
		factorial.push_back(carry % 10);
		carry /= 10;
	}
}

bool check(int n5, int n2) {
	cout << "check: " << n5 << " " << n2 << " ";
	int two_surplus = n2 - n5;

	int count[10] = {0};
	int l = factorial.size();

	count[0] = n5;
	for(int i=0; i<l; i++) {
		cout << factorial[i] << " ";
		int val = factorial[i] * 2 * two_surplus;
		count[val]++;
	}
	cout << endl;

	for(int i=0; i<10; i++) {
		if (digits[i] != count[i]) {
			return false;
		}
	}

	return true;
}


