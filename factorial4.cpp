#include<iostream>
#include<bits/stdc++.h>
#include<cmath>

using namespace std;

int length;
int digits[10];

int main() {
	for(int i=0; i<10; i++) {
		int l;
		cin >> l;
		digits[i] = l;
		length += l;
	}

	if (length < 7) { //up to 8!
		int fact = 2;
		for (int factor=3; factor<=8; factor++) {
			int counting = fact;
			int count[10] = {};
			while (counting > 0) {
				int d = counting % 10;
				count[d]++;
				counting /= 10;
			}

			bool match = true;
			for (int i=0; i<10; i++) {
				if (count[i] != digits[i]) match = false;
			}

			if (match) {
				cout << factor - 1;
				return 0;
			}

			fact *= factor;
		}
	}

	long double log_sum = 0;
	int i = 2;
	while (true) {
		if (floor(log_sum) + 1 == length) break;

		log_sum += log10(i);
		i++;
	}
	cout << i - 1;
}
