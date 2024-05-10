#include "SkipListNode.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int max_height = 10;
template<class Value>
class SkipList {
private:
	SkipListNode<Value>* root;
	int height;
	int size;

protected:
	int flipCoin() {

		int streak = 0;
		while (rand() % 2 == 0 && streak < max_height) {
			streak++;
		}
		return streak;
	}
public:

	/// <summary>
	/// Default constructor
	/// </summary>
	SkipList();

	/// <summary>
	/// Init constructor
	/// </summary>
	SkipList(Value val);

	/// <summary>
	/// Copy constructor
	/// </summary>
	/// <param name="list">: List to be copied</param>
	SkipList(const SkipList<Value>& list);

	/// <summary>
	/// Bool function tells if this list is empty
	/// </summary>
	/// <returns>Returns true if size of list equals zero</returns>
	bool isEmpty();

	/// <param name="level">: The level which length you want to find out</param>
	/// <returns>Returns lenghth of chain from left to right on level</returns>
	int getLength(int level) const;

	/// <returns>Returns thenumber of items in list</returns>
	int getSize() const;

	/// <summary>
	/// Insert function
	/// </summary>
	/// <param name="data">: The data which you want to insert</param>
	/// <returns>Returns true if given data is succesfully inserted in list</returns>
	bool insert(const Value& data);
	
	/// <summary>
	/// Find function
	/// </summary>
	/// <param name="data">: The data which you want to find out</param>
	/// <returns>Returns true if given data is already present in the list</returns>
	bool find(const Value& data);

	/// <summary>
	/// Remove function
	/// </summary>
	/// <param name="data">: The data which you want to remove</param>
	/// <returns>Returns true if given data is successfullyremoved from the list</returns>
	bool remove(const Value& data);
	
	/// <summary>
	/// Output operator
	/// </summary>
	friend ostream& operator<<(ostream& os, const SkipList<Value>& n) {
		for (int i = n.height; i >= 0 ; i--) {
			auto curs = n.root->getNextAt(i);
			os << "Level: " << i + 1 << " | |-> ";
			while (curs != nullptr) {
				os << *(curs->getDataPtr()) << " -> ";
				curs = curs->getNextAt(i);
			}
			os << "| |" << endl;
		}
		
		
		return os;
	}

	///<summary>
	/// Equality operator
	///</summary>
	bool operator==(const SkipList<Value>& n);

	///<summary>
	/// Inequality operator
	///</summary>
	bool operator!=(const SkipList<Value>& n);

	///<summary>
	/// Assignment operator
	///</summary>
	SkipList& operator=(const SkipList<Value>& n);
};

template<class Value>
SkipList<Value>::SkipList() :
	root(new SkipListNode<Value>(Value(), max_height)),
	height(-1),
	size(0)
{
	srand(time(NULL));
}

template<class Value>
SkipList<Value>::SkipList(Value val) :
	root(new SkipListNode<Value>(val, max_height)),
	height(1),
	size(1)
{
	srand(time(NULL));
}

template<class Value>
SkipList<Value>::SkipList(const SkipList<Value>& list) :
	root(new SkipListNode<Value>(Value(), max_height)),
	height(list.height),
	size(list.size)
{
	srand(time(NULL));
	this->root->getNext().resize(list.height-1, nullptr);
	this->root->setData(*(list.root->getDataPtr()));
	for (int i = height; i >= 0; i--) {
		SkipListNode<Value>* this_curs = this->root;
		SkipListNode<Value>* cp_curs = list.root;
		while (cp_curs->getNextAt(i) != nullptr) {
			this_curs->setNextAt(i, new SkipListNode<Value>(*(cp_curs->getNextAt(i))));
			this_curs = this_curs->getNextAt(i);
			cp_curs = cp_curs->getNextAt(i);
		}
	}
}

template<class Value>
bool SkipList<Value>::isEmpty() {
	return size == 0;
}

template<class Value>
int SkipList<Value>::getLength(int level) const{
	int c = 0;
	auto curs = root;
	while (!curs->isEnd()) {
		c++;
		curs = curs->next[level];
	}
	return c;
}

template<class Value>
int SkipList<Value>::getSize() const {
	return this->size;
}

template<class Value>
bool SkipList<Value>::insert(const Value& data) {
	
	int newLevel = flipCoin();
	// Resizing the size of the levels to make place for the inserting value

	if (height < newLevel)
	{
		root->getNext().resize(newLevel + 1, nullptr);

		height = newLevel;
	}


	SkipListNode<Value>* current = root; // pointer to the head to traverse through the skip list


	vector<SkipListNode<Value>*> Update(height + 1, nullptr); // To store the update node at eah level

	// Loop over the levels upto which we want the value to be inserted

	for (int i = height; i >= 0; i--)
	{
		// Finding the place for the inserting value

		while (current->getNextAt(i) && *(current->getNextAt(i)->getDataPtr())< data)
		{
			current = current->getNextAt(i);
		}
		// Updating the level accordingly

		Update[i] = current;

	}

	current = current->getNextAt(0);   // Moves the current to the next node at level 0 

	if (current == nullptr || *(current->getDataPtr()) != data) // if the current is null then it does not exit we need to insert the value
	{
		auto newNode = new SkipListNode<Value>(data, height);

		for (int i = 0; i <= newLevel; i++)
		{
			newNode->setNextAt(i, Update[i]->getNextAt(i));

			Update[i]->setNextAt(i, newNode);  // To insert the value at each level

		}
		size++;
		return true;
	}
	else
	{
		return false;
	}
}

template<class Value> 
bool SkipList<Value>::find(const Value& data) {
	SkipListNode<Value>* current = root;           // start by setting a current pointer to the head node to traverse through the skip list

	for (int i = height; i >= 0; i--) // Begin traversing from the top level and iteratively approaching the bottom of the skip list
	{
		while (current->getNextAt(i) && *(current->getNextAt(i)->getDataPtr()) < data) // keep on moving forward if the value of the next node is less than the searching node otherwise  move downward (handled by outer for loop)
		{
			current = current->getNextAt(i); // moving forward

		}
	}

	current = current->getNextAt(0); // Move to the next of the node at level 0

	if (current != nullptr && *(current->getDataPtr()) == data) // if value is found
		return true;
	else  // Incase value does not exist
		return false;
}

template<class Value>
bool SkipList<Value>::remove(const Value& data) {
	// Function to remove value
	SkipListNode<Value>* current = root; // start by setting a current pointer to the head node 

	vector<SkipListNode<Value>*> Update(height + 1, nullptr); // Create an update vector to store the updated node at each level, Remember only those nodes will be updated where the value to be deleted is present.



	for (int i = height; i >= 0; i--)
	{
		while (current->getNextAt(i) && *(current->getNextAt(i)->getDataPtr()) < data)
		{
			current = current->getNextAt(i);
		}

		Update[i] = current;         // Update array is keeping the track, where the changes should be made, after deleting the node.
	}

	current = current->getNextAt(0);     // Set the current pointer to the next node at level 0.

	if (current != nullptr && *(current->getDataPtr()) == data) // If the value is present then delete the value
	{
		for (int i = 0; i <= height; i++)      // Deleting the value from each level
		{
			// Setting the pointers
			if (Update[i]->getNextAt(i) != current)
			{
				break;
			}
			else
			{
				Update[i]->setNextAt(i, current->getNextAt(i));
			}
		}

		delete current; // deleting the node

		while (height > 0 && root->getNextAt(height) == nullptr)  // decrement the level variable incase there is not any value at that level
		{
			height--;
			
		}
		size--;
		return true;
	}
	else // Incase the value does not exist
	{
		return false;
	}
}

template<class Value>
bool SkipList<Value>::operator==(const SkipList<Value>& n) {
	if (this->size != n.size || this->height != n.height || *(this->root) != *(n.root)) {
		return false;
	}
	for (int i = height; i >= 0; i--) {
		SkipListNode<Value>* this_curs = this->root;
		SkipListNode<Value>* cp_curs = n.root;
		while (cp_curs->getNextAt(i) != nullptr) {
			if (*(this_curs->getNextAt(i)) != *(cp_curs->getNextAt(i))) {
				return false;
			}
			this_curs = this_curs->getNextAt(i);
			cp_curs = cp_curs->getNextAt(i);
		}
	}
	return true;
}

template<class Value>
bool SkipList<Value>::operator!=(const SkipList<Value>& n) {
	if (this->size != n.size || this->height != n.height || this->root != n.root) {
		return true;
	}
	for (int i = height; i >= 0; i--) {
		SkipListNode<Value>* this_curs = this->root;
		SkipListNode<Value>* cp_curs = n.root;
		while (cp_curs->getNextAt(i) != nullptr) {
			if (this_curs->getNextAt(i) != cp_curs->getNextAt(i)) {
				return true;
			}
			this_curs = this_curs->getNextAt(i);
			cp_curs = cp_curs->getNextAt(i);
		}
	}
	return false;
}

template<class Value>
SkipList<Value>& SkipList<Value>::operator=(const SkipList<Value>& n) {
	if (&n == this)
		return *this;
	this->height = n.height;
	this->size = n.size;
	this->root->getNext().resize(n.height, nullptr);
	this->root->setData(*(n.root->getDataPtr()));
	for (int i = height; i >= 0; i--) {
		SkipListNode<Value>* this_curs = this->root;
		SkipListNode<Value>* cp_curs = n.root;
		while (cp_curs->getNextAt(i) != nullptr) {
			this_curs->setNextAt(i, new SkipListNode<Value>(*(cp_curs->getNextAt(i))) );
			this_curs = this_curs->getNextAt(i);
			cp_curs = cp_curs->getNextAt(i);
		}
	}
	return *this;
}