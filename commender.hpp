#pragma once
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
#include <set>
//#define DEBUG

#ifndef _DEBUG
using namespace std;
vector<int> Query_ISBNforUids(int ISBN) {
	vector<int> v;
	return v;
}

vector<int> Query_UidforISBNs(int uid) {
	vector<int> v;
	return v;
}

#else
#include "Querytest.hpp"
using namespace std;
vector<int> Query_ISBNforUids(int ISBN) {
	return tQuery_ISBNforUids(ISBN);
}

vector<int> Query_UidforISBNs(int uid) {
	return tQuery_UidforISBNs(uid);
}
#endif

bool CmpByValue(const pair<int, int>& lhs, const pair<int, int>& rhs) {
	return lhs.second > rhs.second;
}


/*static class Weights {
public: 
	enum{ length3 = 5, length5 = 3};
};*/

class UsrDump {
public:
	UsrDump() {}
	UsrDump(const vector<int> & bks) { for (int i : bks)uids.insert(i); }
	UsrDump(const set<int> & bks) { uids = bks; }
	void AddUsr(int uid) { uids.insert(uid); }
	void Concat(set<int> colle) { for (int i : colle)uids.insert(i); }
	void Clr() { uids.clear(); }
	//int GetuidByID(int id) { return uids[id]; }
	void Sort() { 
		vpii = vector<pair<int,int>>(isbnsAndSum.begin(),isbnsAndSum.end());
		sort(vpii.begin(), vpii.end(), CmpByValue); 
	}
	void setbook() {
		for (int u : uids) {
			for (int i : Query_UidforISBNs(u)) {
				if (isbnsAndSum.find(i) == isbnsAndSum.end())isbnsAndSum[i] = 0;
				++isbnsAndSum[i];
			}
		}
	}

	vector<int> getBookCopy(int num);
private:

	set<int> uids;
	map<int,int> isbnsAndSum;
	vector<pair<int, int>> vpii;
};


class BookDump {
public:
	BookDump() {}
	BookDump(const vector<int> & bks) { for (int i : bks)ISBNs.insert(i); }
	BookDump(const set<int> & bks) { ISBNs = bks; }
	void AddBook(int ISBN) { ISBNs.insert(ISBN); }
	void Concat(set<int> colle) { for(int i : colle)ISBNs.insert(i); }
	void Clr() { ISBNs.clear(); }
	void setUser() {
		for (int i : ISBNs) {
			for (int u : Query_ISBNforUids(i)) {
				uidsRelated.insert(u);
			}
		}
	}
	const set<int>& getSetCopy() { return ISBNs; }
	const set<int>& getUidSetCopy() { return uidsRelated; }
private:

	set<int> ISBNs;
	set<int> uidsRelated;
};


class ItemSpreadMap {

public:


	ItemSpreadMap(int _uid) {
		SetSeedUser(_uid);
		BooksBought = Query_UidforISBNs(uid);
		BooksBought.setUser();
		UsersRelated = BooksBought.getUidSetCopy();
		UsersRelated.setbook();
		UsersRelated.Sort();
	}

	inline vector<int> getReco(int num);


private:
	void SetSeedUser(int _uid) {
		uid = _uid;
	}
	map<int, vector<int>> CostomertoISBNsMap;

	int uid;

	BookDump BooksBought;

	UsrDump UsersRelated;

protected:

};

/*
vector<int> RecommandedBooks(ItemSpreadMap _m, int num = 0) {
	vector<int> topN;
	for (int i = 0; i < num; ++i) {
		topN.push_back(_m.getReco(num)[i]);
	}
	return topN;
}
*/
inline vector<int> ItemSpreadMap::getReco(int num)
{
	return UsersRelated.getBookCopy(num);
}

vector<int> UsrDump::getBookCopy(int num)
{
	// TODO: 在此处插入 return 语句 // done
	vector<int> v;
	for (int i = 0; i < num && i < vpii.size(); ++i)
		v.push_back(vpii[i].first);
	return v;
}
