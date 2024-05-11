#include "PriorityQueue.h"
#include <iostream>
using namespace std;

int main() {
	PriorityQueue<int> q;
	q.push(111, 1);
	q.push(12, 1);
	q.push(140, 1);
	q.push(21, 2);
	q.push(30, 3);
	q.push(770, 3);
	q.push(40, 4);
	cout << q << endl << "pop()" << endl;
	q.pop();
	cout << q << endl;
	cout << "peek() = " << q.peek() << endl;
}