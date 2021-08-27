#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_

template<class T>
struct QueueNode
{
	T data;
	QueueNode<T>* next;
};

enum QueueErrorCode
{
	EMPTY,
	OUT_OF_MEMORY,
	NONE_ERROR
};

template<class T>
class MyQueue
{
public:
	MyQueue();
	~MyQueue();
	bool isEmpty();

	QueueErrorCode append(T t);
	QueueErrorCode serve();
	QueueErrorCode getFront(T& t);
	int getCount() { return count; }

private:
	QueueNode<T> * front;
	QueueNode<T> * rear;
	int count;
};

template<class T>
MyQueue<T>::MyQueue() :count(0)
{
	QueueNode<T>* node = new QueueNode<T>;
	node->next = nullptr;
	front = node;
	rear = node;
}

template<class T>
bool MyQueue<T>::isEmpty()
{
	if (count == 0)
		return true;
	return false;
}

template<class T>
QueueErrorCode MyQueue<T>::append(T t)
{
	QueueNode<T>* node = new QueueNode<T>;
	if (node == nullptr) return QueueErrorCode::OUT_OF_MEMORY;
	node->data = t;
	node->next = nullptr;
	rear->next = node;
	rear = node;
	count++;
	return QueueErrorCode::NONE_ERROR;
}

template<class T>
QueueErrorCode MyQueue<T>::serve()
{
	if (isEmpty()) return QueueErrorCode::EMPTY;
	QueueNode<T>* node = front;
	front = front->next;
	delete node;
	count--;
	return QueueErrorCode::NONE_ERROR;
}

template<class T>
QueueErrorCode MyQueue<T>::getFront(T& t)
{
	if (isEmpty()) return QueueErrorCode::EMPTY;
	t = front->next->data;
	return QueueErrorCode::NONE_ERROR;
}

template<class T>
MyQueue<T>::~MyQueue()
{
	while (!isEmpty()) serve();
	delete front;
}

#endif // !MY_QUEUE_H_
