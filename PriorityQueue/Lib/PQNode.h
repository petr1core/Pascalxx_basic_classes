template<class T>
class Item {
private:
	T data;
	int priority;
public:
	Item(T data, int priority) :
		data(data),
		priority(priority)
	{}

	Item(const Item& item) :
		data(item.data),
		priority(item.priority)
	{}

	void set(T data, int priority) {
		this->data = data;
		this->priority = priority;
	}

	T getData() {
		return data;
	}

	int getPriority() const {
		return priority;
	}

	void setData(const T& data) {
		this->data = data;
	}

	void setPriority(int p) {
		this->priority = p;
	}

	bool operator==(const Item<T>& n) {
		if (this->data != n.data || this->priority != n.priority)
			return false;
		return true;
	}

	bool operator!=(const Item<T>& n) {
		if (this->data != n.data || this->priority != n.priority)
			return true;
		return false;
	}

	Item& operator=(const Item<T>& n) {
		if (*this == n)
			return *this;
		this->priority = n.priority;
		this->data = n.data;
		return *this;
	}
};

template <class T>
class PQNode {
private:
	Item<T> item;
	PQNode* next;
public:
	PQNode();
	PQNode(T data, int priority);
	PQNode(T data, int priority, PQNode<T>* next);
	PQNode(const PQNode<T>& node);
	PQNode<T>* getNextPtr();
	void setNextPtr(PQNode<T>* node);
	void set(T data, int priority, PQNode<T>* next);
	T getData();
	int getPriority() const;
	bool operator==(const PQNode<T>& n);
	bool operator!=(const PQNode<T>& n);
	PQNode& operator=(const PQNode<T>& n);
};

template<class T>
PQNode<T>::PQNode() :
	item(T(), 0),
	next(nullptr)
{}

template<class T>
PQNode<T>::PQNode(T data, int priority) :
	item(data, priority),
	next(nullptr)
{}

template<class T>
PQNode<T>::PQNode(T data, int priority, PQNode<T>* next) :
	item(data, priority),
	next(next)
{}

template<class T>
PQNode<T>::PQNode(const PQNode<T>& node) :
	item(node.item),
	next(node.next)
{}

template<class T>
PQNode<T>* PQNode<T>::getNextPtr() {
	return next;
}

template<class T>
void PQNode<T>::setNextPtr(PQNode<T>* node) {
	this->next = node;
}


template<class T>
void PQNode<T>::set(T data, int priority, PQNode<T>* next) {
	this->item.set(data, priority);
	this->next = next;
}

template<class T>
T PQNode<T>::getData() {
	return item.getData();
}

template<class T>
int PQNode<T>::getPriority() const {
	return item.getPriority();
}

template<class T>
bool PQNode<T>::operator==(const PQNode<T>& n) {
	if (this->item != n.item || this->next != n.next)
		return false;
	return true;
}

template<class T>
bool PQNode<T>::operator!=(const PQNode<T>& n) {
	if (this->item != n.item || this->next != n.next)
		return true;
	return false;
}

template<class T>
PQNode<T>& PQNode<T>::operator=(const PQNode<T>& n) {
	if (*this == n)
		return *this;
	this->item = n.item;
	this->next = n.next;
	return *this;
}
