#include <mutex>
#include <condition_variable>
#include <iostream>

struct Node {
	Node(size_t num) : next(nullptr), ticket_number(num) {}
	Node* next;
	size_t ticket_number;
};

class QueueSpinLock {
public:
private:
	Node* head_ = new Node(0);
	Node* tail_ = head_;
};