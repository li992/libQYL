template <typename T>
class stack {
private:
	struct item {
		T value;
		struct item* next;
	};
	const int maxSize = 10;
	int length;
	item* head;
	item* tail;

public:
	stack();
	~stack();
	bool isEmpty()const;
	bool isFull()const;
	int countNum()const;
	bool push(const T&);
	bool pop(T&);
	char getTop()const;
}; 

