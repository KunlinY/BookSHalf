#include "commender.hpp"
#include <iostream>
using namespace std;
int main(){
	int uidseed = 0,sum = 0;
	cin >> uidseed >> sum;
	ItemSpreadMap imp(uidseed);
	vector<int> reco = imp.getReco(sum);
	for (int i : reco) cout << i << endl;
	system("PAUSE");
	return 0;
}