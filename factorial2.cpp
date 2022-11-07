#include<iostream>
#include<vector>
#include<chrono>

using namespace std;

int length = 0;
int digits[10];

vector<int> factorial;
int factor;
int lo;
int n2_factors = 0, n5_factors = 0;

int main() {
	auto start = chrono::high_resolution_clock::now();
	for (int i=0; i<10; i++) {
		int l;
		cin >> l;
		digits[i] = l;
		length += l;
	}

	factorial.push_back(2);
	factor = 2;
	lo = 1;

	while(true) {
		factor++;

		if (lo >= length) {
			int count[10] = {};
			count[0] = n5_factors;
			//cout << "factor " << factor << ": ";
			
			int carry = 0;
			int two_surplus = n2_factors - n5_factors;
			//cout << two_surplus << endl;
			for(int i=0; i<factorial.size(); i++) {
				int val = factorial[i];
				for (int j=0; j<two_surplus; j++) {
					val *= 2;
				}
				int d = (val+carry) % 10;
				count[d]++;
				//cout << d << " "; 
				carry = (val+carry) / 10;
			}


			while(carry > 0) {
				int d = carry % 10;
				count[d]++;
				//cout << d << " ";
				carry /= 10;
			}

			//cout << endl;

			bool match = true;
			for(int i=0; i<10; i++) {
				if (count[i] != digits[i]) match = false;
			}

			if(match) {
				cout << factor - 1<< endl;
				auto end = chrono::high_resolution_clock::now();
				auto duration = chrono::duration_cast<chrono::microseconds>(end-start); 
				cout << duration.count() << endl;
				break;
			}
			
		}
		

		//counting length
		int factor_length = factor;
		while (factor_length > 0) {
			lo++;
			factor_length/=10;
		}


		//excluding 5 * 2 factors
		
		int simplified = factor; 
		if(n2_factors > n5_factors + 30) {
			while(simplified % 5 == 0) {
				simplified /= 5;
				n5_factors++;
			}

			while(simplified % 2 == 0) {
				simplified /= 2;
				n2_factors++;
			}
		}

		if(simplified == 1) continue;

		//multiplying
		int carry = 0;
		for(int i=0; i<factorial.size();i++) {
			int val = factorial[i] * simplified;
			factorial[i] = (val+carry) % 10;
			carry = (val+carry) / 10;
		}

		while(carry > 0) {
			factorial.push_back(carry % 10);
			carry /= 10;
		}
	}
}
