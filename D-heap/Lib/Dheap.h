#include <iostream>
#include <vector>

template<class Value>
class Dheap {
private:
	int max_size;
	std::vector<Value> heap;
	int size;
	int d;
	int level;

	int findInChilds(int id, const Value& val);
	void updateLevel();
	void normalizeUp();
	void normalizeDown(int i = 0);
	std::vector<int>* getLevelSizeRatio(int maxSize = 1000) const;
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	Dheap(int d);

	/// <summary>
	/// Value init constructor.
	/// </summary>
	Dheap(const Value& val, int d);
	
	/// <summary>
	/// Vector init constructor. Attention! Vector is a heap representation!
	/// </summary>
	Dheap(const std::vector<Value>& v, int d);

	/// <summary>
	/// Copy constructor.
	/// </summary>
	Dheap(const Dheap& h);

	/// <summary>
	/// Find method.
	/// </summary>
	/// <returns>Returns id of found element. If not, returns -1.</returns>
	int find(const Value& val);

	/// <summary>
	/// Insert method.
	/// </summary>
	/// <param name="val">: (const) Value to insert.</param>
	void insert(const Value& val);

	/// <summary>
	/// Pop method.
	/// </summary>
	/// <returns>Returns the value on top of the heap. Raises an error if empty.</returns>
	Value pop();

	/// <summary>
	/// Bool function. Tells is heap is full.
	/// </summary>
	/// <returns>Returns true if size equals max_size.</returns>
	bool isFull();

	/// <summary>
	/// Bool function. Tells is heap is empty.
	/// </summary>
	/// <returns>Returns true if size equals zero.</returns>
	bool isEmpty();

	/// <summary>
	/// Change max_size function. Changes max_size. Be carefull
	/// </summary>
	/// <param name="val">: new max_size.</param>
	void maxSize(int size);

	/// <summary>
	/// Equality operator
	/// </summary>
	bool operator==(const Dheap<Value>& h);

	///<summary>
	/// Inequality operator
	///</summary>
	bool operator!=(const Dheap<Value>& h);

	///<summary>
	/// Assignment operator
	///</summary>
	Dheap<Value>& operator=(const Dheap<Value>& h);

	/// <summary>
	/// Output operator
	/// </summary>
	friend std::ostream& operator<<(std::ostream& os, const Dheap<Value>& h) {
		std::vector<int>* LSRatio = new std::vector<int>(*h.getLevelSizeRatio());
		os << "level 0: " << h.heap[0] << std::endl;
		if (h.level > 0) {
			for (int i = 1; i < h.level; i++) {
				os << "level " << i << ": ";
				for (int j = LSRatio->at(i); j < h.size && j < LSRatio->at(i+1); j++) {
					if (j % h.d == 0)
						os << h.heap[j] << "| ";
					else
						os << h.heap[j] << " ";
				}
				os << std::endl;
			}
		}
		return os;
	}
};

template<class Value>
Dheap<Value>::Dheap(int d) :
	max_size(1000),
	heap(std::vector<Value>()),
	size(0), 
	d(d),
	level(0)
{}

template<class Value>
Dheap<Value>::Dheap(const Value& val, int d) :
	max_size(1000),
	heap(std::vector<Value>(1, val)),
	size(1),
	d(d),
	level(0)
{}

template<class Value>
Dheap<Value>::Dheap(const std::vector<Value>& v, int d) :
	max_size(1000),
	heap(v),
	size(v.size()),
	d(d),
	level((int)std::ceil((double)v.size()/double(d)))
{
	updateLevel();
}

template<class Value>
Dheap<Value>::Dheap(const Dheap& h) :
	max_size(h.max_size),
	heap(h.heap),
	size(h.size),
	d(h.d),
	level(h.level)
{}

template<class Value>
int Dheap<Value>::find(const Value& val) {	
	if (size < 1) return -1;
	int found_id = -1;
	for (int i = 0; i < size && found_id == -1; i++) {
		found_id = findInChilds(i, val);
	}
	return found_id;
}

template<class Value>
int Dheap<Value>::findInChilds(int id, const Value& val) {
	if (level < 0)
		throw std::runtime_error("level can't be less than zero.");
	if(heap[id] == val) return id;
	else {
		int left = (d - 1) * (level - 1) - 1;
		int right = d * level;
		if (id > level)
			return -1;
		for (int i = left; i <= right && i < size; i++) {
			if (heap[i] == val)
				return i;
		}
	}
	return -1;
}

template<class Value>
void Dheap<Value>::insert(const Value& val) {
	if (isFull()) 
		throw std::range_error("heap reached max_size, increase max_size");
	heap.push_back(val);
	size++;
	updateLevel();
	normalizeUp();
}

template<class Value>
void Dheap<Value>::updateLevel() {
	std::vector<int>* levelSizeRatio = new std::vector<int>(*(this->getLevelSizeRatio()));
	int i = 0;
	bool flag = false;
	while (!flag || i == levelSizeRatio->size() - 1) {
		if (size <= levelSizeRatio->at(i)) {
			this->level = i;
			flag = true;
		}
		i++;
	}
	if (!flag)
		throw std::range_error("level out of range for this size, increase max_size");
}

template<class Value>
void Dheap<Value>::normalizeUp() {
	int id = heap.size() - 1;
	while (id != 0 && heap[id] > heap[(id - 1) / d]) {
		std::swap(heap[id], heap[(id - 1) / d]);
		id = (id - 1) / d;
	}
}

template<class Value>
std::vector<int>* Dheap<Value>::getLevelSizeRatio(int maxSize = 1000) const{
	std::vector<int>* levelSizeRatio = new std::vector<int>();
	int count = 0;
	int floor = 0;
	while (count < maxSize) {
		levelSizeRatio->push_back(count);
		count += std::pow(d, floor);
		floor++;
	}
	return levelSizeRatio;
}

template<class Value>
Value Dheap<Value>::pop() {
	if (!isEmpty()) {
		Value top = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		size--;
		normalizeDown();
		updateLevel();
		return top;
	}
	else throw std::range_error("Heap is empty");
}

template<class Value>
void Dheap<Value>::normalizeDown(int i = 0) {
	int ind = i;
	for (int k = 0; k < d; k++) {
		int child = d * i + k + 1;
		if (child < heap.size() && heap[child] > heap[ind]) {
			ind = child;
		}
	}
	if (ind != i) {
		std::swap(heap[i], heap[ind]);
		normalizeDown(ind);
	}
}

template<class Value>
bool Dheap<Value>::isFull() {
	return size == max_size;
}

template<class Value>
bool Dheap<Value>::isEmpty() {
	return size == 0;
}

template<class Value>
void Dheap<Value>::maxSize(int size) {
	max_size = size;
}

template<class Value>
bool Dheap<Value>::operator==(const Dheap<Value>& h) {
	if (size != h.size || level != h.level || max_size != h.max_size || d != h.d || heap != h.heap)
		return false;
	return true;
}

template<class Value>
bool Dheap<Value>::operator!=(const Dheap<Value>& h){
	if (size != h.size || level != h.level || max_size != h.max_size || d != h.d || heap != h.heap)
		return true;
	return false;
}

template<class Value>
Dheap<Value>& Dheap<Value>::operator=(const Dheap<Value>& h){
	if (this == &h)
		return *this;
	this->max_size = h.max_size;
	this->size = h.size;
	this->heap = h.heap;
	this->d = h.d;
	this->level = h.level;
}