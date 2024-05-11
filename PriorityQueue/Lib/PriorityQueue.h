#include "PQNode.h"
#include "iostream"
using namespace std;

const int max_size = 100000;

template<class Value>
class PriorityQueue {
private:
	PQNode<Value>* head;
	int size;
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	PriorityQueue();
	
	/// <summary>
	/// Init constructor.
	/// </summary>
	/// <param name="data">: Data to init. with.</param>
	/// <param name="priority">: Priority of this data.</param>
	PriorityQueue(Value data, int priority);

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="q">: (const) Queue to copy.</param>
	PriorityQueue(const PriorityQueue& q);

	/// <summary>
	/// Push method.
	/// </summary>
	/// <param name="data">: Data to push.</param>
	/// <param name="priority">: Priority of this data.</param>
	void push(Value data, int priority);
	
	/// <summary>
	/// Peek method.
	/// </summary>
	/// <returns>Returns the highest element with highest priority.</returns>
	Value peek();

	/// <summary>
	/// Pop method. Removes the top element.
	/// </summary>
	void pop();

	/// <summary>
	/// Bool function tells is this queue is empty.
	/// </summary>
	/// <returns>Returns true if size of queue equals zero.</returns>
	bool isEmpty();

	/// <summary>
	/// Bool function tells is this queue is full.
	/// </summary>
	/// <returns>Returns true if size of queue exceeds 100000 elements.</returns>
	bool isFull();

	/// <summary>
	/// Get size function.
	/// </summary>
	/// <returns>Returns size of the queue.</returns>
	int getSize() const;
	
	/// <summary>
	/// Output operator.
	/// </summary>
	friend ostream& operator<<(ostream& os, const PriorityQueue<Value>& n) {
		PriorityQueue<Value>* q = new PriorityQueue<Value>(n);
		os << "|->";
		while (!q->isEmpty()) {
			os << "{" << q->peek() << "}->";
			q->pop();
		}
		os << "| ";
		return os;
	}

	///<summary>
	/// Equality operator.
	///</summary>
	bool operator==(const PriorityQueue<Value>& n);

	///<summary>
	/// Inequality operator.
	///</summary>
	bool operator!=(const PriorityQueue<Value>& n);

	///<summary>
	/// Assignment operator.
	///</summary>
	PriorityQueue& operator=(const PriorityQueue<Value>& n);
};

template<class Value>
PriorityQueue<Value>::PriorityQueue() :
	head(new PQNode<Value>()),
	size(-1)
{}

template<class Value>
PriorityQueue<Value>::PriorityQueue(Value data, int priority) :
	head(new PQNode<Value>(data, priority)),
	size(1)
{}

template<class Value>
PriorityQueue<Value>::PriorityQueue(const PriorityQueue& q) :
	head(new PQNode<Value>(*q.head)),
	size(q.size)
{
	PQNode<Value>* curs = head;
	PQNode<Value>* q_curs = q.head;
	while (q_curs != nullptr) {
		curs->setNextPtr(q_curs->getNextPtr());
		q_curs = q_curs->getNextPtr();
		curs = curs->getNextPtr();
	}
}

template<class Value>
Value PriorityQueue<Value>::peek() {
	if (!isEmpty())
		return head->getData();
	else throw std::range_error("list is empty, nothing to peek");
	

}

template<class Value>
void PriorityQueue<Value>::push(Value data, int priority) {
	if (size == -1) 
		size = 0;
	PQNode<Value>* curs = head;

	PQNode<Value>* newNode = new PQNode<Value>(data, priority);

	if (head->getPriority() < priority) {
		newNode->setNextPtr(head);
		head = newNode;
	}
	else {
		while (curs->getNextPtr() != nullptr && curs->getNextPtr()->getPriority() > priority) {
			curs = curs->getNextPtr();
		}

		newNode->setNextPtr(curs->getNextPtr());
		curs->setNextPtr(newNode);
	}
	size++;
}

template<class Value>
void PriorityQueue<Value>::pop() {
	if (!isEmpty()) {
		head = head->getNextPtr();
		size--;
	}
	else throw std::range_error("list is empty, nothing to POP");
}

template<class Value>
bool PriorityQueue<Value>::isEmpty() {
	return size <= 0;
}

template<class Value>
bool PriorityQueue<Value>::isFull() {
	return size == max_size;
}

template<class Value>
int PriorityQueue<Value>::getSize() const {
	return this->size;
}
