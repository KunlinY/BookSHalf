#pragma once
#include <vector>
using namespace std;
vector<int> tQuery_ISBNforUids(int ISBN) {
	int ary[] = { 001,002,003,004,005,006 };
	for (int i = 0; i < 6; ++i) ary[i] *= ISBN;
	return vector<int>({ ary[0],ary[1],ary[2],ary[3],ary[4],ary[5] });
}
vector<int> tQuery_UidforISBNs(int uid) {
	int ary[] = { 001,002,003,004,005,006 };
	for (int i = 0; i < 6; ++i) ary[i] *= uid;
	return vector<int>({ ary[0],ary[1],ary[2],ary[3],ary[4],ary[5] });
}