#include<iostream>
#include<string>

using namespace std;

int sums[100];
int list[2023];

int main() {
	freopen("list.txt", "r", stdin);

	for (int i=0; i<100; i++) {
		cin >> sums[i];
	}

	for(int i=0; i<2023; i++) {
		list[i] = i+1;
	}


}

void recurse() {
	
}
