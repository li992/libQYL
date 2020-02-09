#include "InfixPostfixConvertor.h"
#include <iostream>
#include <stdlib.h>

template <typename T>
stack<T>::stack() {
	head = tail = nullptr;
	length = 0;
}

template <typename T>
stack<T>::~stack() {
	item* current;
	while (head != nullptr)
	{
		current = head;
		head = head->next;
		delete current;
	}
}

template <typename T>
bool stack<T>::isEmpty() const {
	if (length == 0)
		return true;
	else return false;
}

template <typename T>
bool stack<T>::isFull() const {
	if (length == maxSize)
		return true;
	else return false;
}

template <typename T>
int stack<T>::countNum() const {
	return length;
}

template <typename T>
bool stack<T>::push(const T& value) {
	if (isFull())
		return false;
	item ptr = new item;
	ptr.value = value;
	ptr.next = nullptr;
	length++;
	if (head == nullptr)
		head = ptr;
	else
		tail.next = ptr;
	tail = ptr;

	delete ptr;
	return true;
}

template <typename T>
bool stack<T>::pop(T& value) {
	if (isEmpty())
		return false;
	item* current = head;
	if (head != tail) {
		while (current.next != tail) {
			current = current.next;
		}
		value = tail.value;
		tail = current;
		current = current.next;
		delete current;
		tail.next = nullptr;
	}
	else {
		value = current.value;
		head = nullptr;
		tail = nullptr;
		delete current;
	}
	length--;

	return true;
}

template <typename T>
char stack<T> ::getTop() const {
	return tail.value;
}