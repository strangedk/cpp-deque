#include <iostream>
#include <map>
#include <stdexcept>
#include <array>

using namespace std;

template <typename T>
struct Node {
	Node(T value) {
		this->value = make_shared<T>(value);
	}

	shared_ptr<Node<T>> prev;
	shared_ptr<Node<T>> next;
	shared_ptr<T> value;

	T GetValue() {
		return *value;
	}
};

template <typename T>
class Deque {
public:
	void PushBack(T value) {
		auto node = make_shared<Node<T>>(value);

		if (!m_tail) {
			m_tail = node;
			m_head = node;
		}
		else {
			m_tail->next = node;
			node->prev = m_tail;
			m_tail = node;
		}

		UpdateMap();
	}

	void PushFront(T value) {
		auto node = make_shared<Node<T>>(value);

		if (!m_head) {
			m_head = node;
			m_tail = node;
		}
		else {
			m_head->prev = node;
			node->next = m_head;
			m_head = node;
		}

		UpdateMap();
	}

	T At(int index) {
		int i = 0;
		shared_ptr<Node<T>> node = m_head;

		try {
			while (i++ < index) {
				node = node->next;
			}
		} catch (...) {
			throw out_of_range("Wrong index. Out of bounds.");
		}

		return node->GetValue();
	}

	T operator[] (int index) {
		return m_map.at(index)->GetValue();
	}

private:
	void UpdateMap() {
		int i = 0;
		m_map.clear();
		for (auto node = m_head; node; node = node->next) {
			pair<int, shared_ptr<Node<T>>> pair(i++, node);
			m_map.insert(pair);
		}
	}

	shared_ptr<Node<T>> m_head;
	shared_ptr<Node<T>> m_tail;

	map <int, shared_ptr<Node<T>>> m_map;
};

int main() {
	Deque<int> intDeque;
	intDeque.PushBack(30);
	intDeque.PushBack(40);
	intDeque.PushFront(20);
	intDeque.PushFront(10);

	cout << intDeque.At(3) << endl;
	cout << intDeque[0] << endl;

	const int size = 4;
	Deque<array<int, size>> arrDeque;
	arrDeque.PushBack({ 0, 1, 2, 3 });
	arrDeque.PushBack({ 4, 5, 6, 7 });
	arrDeque.PushFront({ 8, 9, 10, 11 });
	arrDeque.PushFront({ 12, 13, 14, 15 });

	for (auto i : arrDeque[0]) {
		cout << i << " ";
	}

	for (auto i : arrDeque.At(2)) {
		cout << i << " ";
	}
};