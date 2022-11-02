#include<iostream>
#include<vector>
#include<unordered_map>

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

	//vector<int> factorial;
	//factorial.push_back(1);
	factorial[0] = 1;

	int i = 2;
	int l = 1;
	int carry = 0;
	while(true) {
//		if (i % 10 == 0) {
//			for (int j=0; j<i/10; j++) l++; 
//			check(l);
//			carry = 0;
//		}
//		else {
			for(int j=0; j<l; j++) {
				int val = factorial[j] * i;
				factorial[j] = (val+carry) % 10;
				carry = (val+carry) / 10;
			}

			while (carry > 0) {
				l++;
				factorial[l-1] = carry % 10;
				//factorial.push_back(carry % 10);
				carry /= 10;
			}
		//}

		if(l == length && check(l)) break;
		i++; 
	}
	
	cout << i << endl;
}

bool check(int l) {
	unordered_map<int, int> count; 

	for(int i=0; i<l; i++) {
		int d = factorial[i];
		count[d]++;
	}

	for(int i=0; i<10; i++) {
		if(digits[i] != count[i]) return false;
	}

	return true;
}


