#include "SkipList.h"
#include <iostream>
using namespace std;

int main() {
	SkipList<int> list(-9999);
	list.insert(3);
	list.insert(8);
	list.insert(1);
	list.insert(11);
	list.insert(74);
	list.insert(9);
	cout << list << endl;
	bool isfound74 = list.find(74);
	bool isfound33 = list.find(33);
	bool isRemoved9 = list.remove(9);
	bool isRemoved124 = list.remove(124);

	cout << "element 74 is found - " << ((isfound74) ? "true" : "false") << endl;
	cout << "element 33 is found - " << ((isfound33) ? "true" : "false") << endl;
	cout << "element 9 is removed - " << ((isRemoved9) ? "true" : "false") << endl;
	cout << list << endl;
	cout << "element 124 is removed - " << ((isRemoved124) ? "true" : "false") << endl;
	return 0;
}
