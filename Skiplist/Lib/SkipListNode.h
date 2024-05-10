#include <iostream>
#include <vector>
using namespace std;

template<class Value>
class SkipListNode {
private:
	vector<SkipListNode<Value>*> next;
	Value data;
	int level;
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	SkipListNode();

	/// <summary>
	/// Initialize constructor
	/// </summary>
	/// <param name="data">: (const) Value to be stored</param>
	/// <param name="level">: Level of node in ListNode</param>
	SkipListNode(const Value& data, int level);

	/// <summary>
	/// Full-Initialize constructor
	/// </summary>
	/// <param name="data">: (const) Value to be stored</param>
	/// <param name="level">: Level of node in ListNode</param>
	/// <param name="next">: (const) Vector of pointers to SkipListNodes</param>
	//SkipListNode(const Value& data, int level,const vector<SkipListNode<Value>*>& next);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="node">: (const) Node to be copied</param>
	SkipListNode(const SkipListNode& node);

	/// <summary>
	/// The bool function that tells if this node is the last one
	/// </summary>
	/// <returns>Returns true if this node has only null-pointers in next-vector or the node itself is a nullptr</returns>
	bool isEnd();

	/// <summary>
	/// Changes data & level of node
	/// </summary>
	/// <param name="new_data">: (const) new data</param>
	/// <param name="new_level">: new level</param>
	void set(const Value& new_data, int new_level);

	/// <summary>
	/// Changes data
	/// </summary>
	/// <param name="data">: (const) new data</param>
	void setData(const Value& new_data);

	/// <summary>
	/// Changes next-vector to new one
	/// </summary>
	/// <param name="vector">:(const) Vector of pointers on SkipListNodes</param>
	void setPtr(const vector<SkipListNode<Value>*>& vector);

	/// <summary>
	/// Changes level of node
	/// </summary>
	void setLevel(int new_level);

	/// <returns>Returns pointer to the data stored in node</returns>
	Value* getDataPtr();
	
	/// <param name="id">: Index in next-ptr array</param>
	/// <returns>Returns pointer to SkipListNode at id position in next-vector</returns>
	SkipListNode<Value>* getNextAt(int id);
	
	/// <summary>
	/// Changes pointer in array at id pos to new one
	/// </summary>
	/// <param name="id">Index in next-ptr array</param>
	void setNextAt(int id, SkipListNode<Value>* n);

	/// <returns>Returns next-vector</returns>
	vector<SkipListNode<Value>*> getNext();

	/// <summary>
	/// Output operator
	/// </summary>
	friend ostream& operator<<(ostream& os, SkipListNode<Value>& n);
	
	///<summary>
	/// Equality operator
	///</summary>
	bool operator==(SkipListNode<Value>& n);

	///<summary>
	/// Inequality operator
	///</summary>
	bool operator!=(SkipListNode<Value>& n);

	///<summary>
	/// Assignment operator
	///</summary>
	SkipListNode& operator=(const SkipListNode<Value>& n);
};

template<class Value>
SkipListNode<Value>::SkipListNode() :
	data(Value()),
	level(0),
	next()
{}

template<class Value>
SkipListNode<Value>::SkipListNode(const Value& data, int level) :
	data(data),
	level(level),
	next(level + 1, nullptr)
{}

//template<class Value>
//SkipListNode<Value>::SkipListNode(const Value& data, int level, const vector<SkipListNode<Value>*>& next) :
//	data(data),
//	level(level),
//	next(next)
//{}

template<class Value>
SkipListNode<Value>::SkipListNode(const SkipListNode& node) :
	data(node.data),
	level(node.level),
	next(node.next)
{}

template<class Value>
bool SkipListNode<Value>::isEnd() {
	if (this != nullptr) {
		for (int i = 0; i < next.size(); i++) {
			if (next[i] != nullptr) {
				return false;
			}
		}
		return true;
	}
	else return true;
}

template<class Value>
void SkipListNode<Value>::set(const Value & new_data, int new_level) {
	this->data = new_data;
	this->level = new_level;
}

template<class Value>
void SkipListNode<Value>::setData(const Value& new_data) {
	this->data = new_data;
}

template<class Value>
void SkipListNode<Value>::setPtr(const vector<SkipListNode<Value>*>& vector) {
	this->next = vector;
}

template<class Value>
void SkipListNode<Value>::setLevel(int new_level) {
	this->level = new_level;
}

template<class Value>
Value* SkipListNode<Value>::getDataPtr() {
	return &data;
}

template<class Value>
SkipListNode<Value>* SkipListNode<Value>::getNextAt(int id) {
	if (id >= 0 && id < this->next.size()) {
		return this->next[id];
	}
	else throw std::range_error("invalid index!");
}

template<class Value>
void SkipListNode<Value>::setNextAt(int id, SkipListNode<Value>* n) {
	if (id >= 0 && id < this->next.size()) {
		this->next[id] = n;
	}
	else throw std::range_error("invalid index!");
}

template<class Value>
vector<SkipListNode<Value>*> SkipListNode<Value>::getNext() {
	return this->next;
}

template<class Value>
ostream& operator<<(ostream& os, SkipListNode<Value>& n) {
	os << " {" << n.getData() << "} ";
	return os;
}

template<class Value>
bool SkipListNode<Value>::operator==(SkipListNode& n) {
	if (this->level != n.level  || this->data != n.data)
		return false;
	for (int i = 0; i < n.next.size(); i++) {
		if (this->next[i] != n.next[i]) {
			if (this->next[i] == nullptr || n.next[i] == nullptr) {
				return false;
			}
			if (*(this->next[i]) != *(n.next[i]))
				return false;
		}
		
	}
	return true;
}

template<class Value>
bool SkipListNode<Value>::operator!=(SkipListNode& n) {
	if (this->level != n.level || this->data != n.data)
		return true;
	for (int i = 0; i < n.next.size(); i++) {
		if (this->next[i] != n.next[i]) {
			if (this->next[i] == nullptr || n.next[i] == nullptr) {
				return true;
			}
			if (*(this->next[i]) != *(n.next[i]))
				return true;
		}

	}
	return false;
}

template<class Value>
SkipListNode<Value>& SkipListNode<Value>::operator=(const SkipListNode& n) {
	if (&n == this)
		return *this;
	this->next = n.next;
	this->data = n.data;
	this->level = n.level;
}
