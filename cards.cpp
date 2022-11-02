#include <iostream>

using namespace std;

int main (){
	int n;
	cin >> n;

	if (n>26) cout << "YES";
	else if (n>1) cout << "MAYBE";
	else cout << "NO"; 	

	cout << endl; 
}
