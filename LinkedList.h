#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"
using namespace std;
template<class T>
class LinkedList {
public: 
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    void insertAtTheHead(const T &data);
    void insertAtTheTail(const T &data);
    void insertSorted(const T &data);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();

    void print() const;

    T *toArray() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private:
	void remove_first();
private: 
    Node<T> *head;
    Node<T> *tail;
};

//default constructor
template<class T>
LinkedList<T>::LinkedList() { 
    head = nullptr;
	tail = nullptr;
}
 //A constructor takes an array of T objects (arr) and the size of the arr array (arrSize) as parameters.
template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize) {
    int i;
	Node<T> *curr;
	for(i=0;i<arrSize;i++){
		if(i == 0){
			head = new Node<T>(arr[i],nullptr,nullptr);
			curr = head;
		}
		else{
			curr->next = new Node<T>(arr[i],curr,nullptr);
			curr = curr->next;
		}
	}
	tail = curr;
}

// the copy constructor
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    Node<T> *curr;
	Node<T> *obj_curr;
	if(obj.getFirstNode() == nullptr){
		head = nullptr;
		tail = nullptr;
	}
	else{
		obj_curr = obj.head->next;
		head = new Node<T>(obj.head->data,nullptr,nullptr);
		curr = head;
		while(obj_curr != nullptr){
			curr->next = new Node<T>(obj_curr->data,curr,nullptr);
			curr = curr->next;
			obj_curr = obj_curr->next;
		}
		tail = curr;
	}
}

// destructor, deallocate all the memory allocated before
template<class T>
LinkedList<T>::~LinkedList() {
	removeAllNodes();
	head = nullptr;
	tail = nullptr;
}
	
// A function returns a pointer to the first node in the linked list.
template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    if(isEmpty()){
		return nullptr;
	}
	return head;
}

// A function returns a pointer to the last node in the linked list.
template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    if(isEmpty()){
		return nullptr;
	}
	return tail;
}

// A function returns a pointer the node which includes the data given as parameter
template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    Node<T> *curr;
	if(isEmpty()){
		return nullptr;
	}
	curr = head;
	while(curr != nullptr){
		if(curr->data == data){
			return curr;
		}
		curr = curr->next;
	}
	return nullptr;
}

//  A function returns the number of nodes in the linked list.
template<class T>
int LinkedList<T>::getNumberOfNodes() const {
    int k=0;
	Node<T> *curr;
	curr = head;
	while(curr != nullptr){
		k++;
		curr = curr->next;
	}
	return k;
}

// A function checks whether the linked list is empty or not.
template<class T>
bool LinkedList<T>::isEmpty() const {
    if(head==nullptr){
		return true;
	}
	return false;
}

// A function checks whether the given node is in the linked list or not.
template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
	Node<T> *curr;
	curr = head;
	while(curr != nullptr){
		if(curr == node){
			return true;
		}
		curr = curr->next;
	}
	return false;
}

// A function creates and inserts a node at the beginning of the linked list with given data.
template<class T>
void LinkedList<T>::insertAtTheHead(const T &data) {
	if(head == nullptr){
		head = new Node<T>(data,nullptr,nullptr);
		tail = head;
	}
	else{
		Node<T> *node = new Node<T>(data,nullptr,head);
		
		head->prev = node;
		head = node;
	}
}

// A function creates and inserts a node at the end of the linked list with given data.
template<class T>
void LinkedList<T>::insertAtTheTail(const T &data) {
    
	if(head == nullptr){
		head = new Node<T>(data,nullptr,nullptr);
		tail = head;
	}
	else{
		Node<T> *node = new Node<T>(data,tail,nullptr);
		tail->next = node;
		tail = node;
	}
}

// A function creates a node with given data and inserts it to the right place, assuming linked list is ordered ascending.
template<class T>
void LinkedList<T>::insertSorted(const T &data) {
	if(head == nullptr){
		head = new Node<T>(data,nullptr,nullptr);
		tail = head;
	}
	else{
		Node<T> *curr;
		curr = head;
		while(curr->next != nullptr && curr->data < data) curr = curr->next;
		if(curr == head){
			if(data > curr->data){
				if(curr == tail){
					insertAtTheTail(data);
				}
				else{
					Node<T> *newNode = new Node<T>(data,curr,curr->next);
					curr->next->prev = newNode;
					curr->next = newNode;
				}
			}
			else{
				insertAtTheHead(data);
			}
		}
		else if(curr == tail){
			if(data > curr->data){
				insertAtTheTail(data);
			}
			else{
				Node<T> *newNode = new Node<T>(data,curr->prev,curr);
				curr->prev->next = newNode;
				curr->prev = newNode;
			}
		}
		else{
			Node<T> *newNode = new Node<T>(data,curr->prev,curr);
			curr->prev->next = newNode;
			curr->prev = newNode;
		}
	}
}

// A function deletes given node from the linked list.
template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
	if(isEmpty() || !contains(node)) return;
	Node<T> *curr;
	curr = head;
	while(curr != node) curr = curr->next;
	if(curr == head){
		remove_first();
	}
	else if(curr == tail){
		tail = curr->prev;
		tail->next = nullptr;
		delete curr;
	}
	else{
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
		delete curr;
	}
}

// A function deletes the node with given data from the linked list.
template<class T>
void LinkedList<T>::removeNode(const T &data) {
    if(isEmpty()) return;
	Node<T> *curr = head;
	while(curr != nullptr && curr->data != data){
		curr = curr->next;
	}
	removeNode(curr);
}

// A function deletes all nodes from the linked list.
template<class T>
void LinkedList<T>::removeAllNodes() {
    if(isEmpty()) return;
	while(head != tail) remove_first();
	delete head;
	head = nullptr;
	tail = nullptr;
	
}

// A function deletes the first node from the linked list.
template<class T>
void LinkedList<T>::remove_first() {
    if (head == nullptr) {
        return;
    }
	Node<T> *curr = head;
	head = head->next;
	delete curr;
	
}

// A function prints the all linked list content.
template<class T>
void LinkedList<T>::print() const {
    std::cout << "Printing the linked list ..." << std::endl;

    if (this->isEmpty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    Node<T> *node = this->head;

    while (node) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

// A function returns an array which includes the data of all nodes in the linked list.
template<class T>
T *LinkedList<T>::toArray() const {
    if(isEmpty()) return nullptr;
	int i=0;
	T *Arr = new T[getNumberOfNodes()];
	Node<T> *curr = head;
	while(curr != nullptr){
		Arr[i] = curr->data;
		curr = curr->next;
		i++;
	}
	return Arr;
}

// Overloading assignment operator, recreate the linked list with given linked list as parameter
template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
	if(rhs.isEmpty()) this->removeAllNodes();
	
	if(rhs.head == nullptr){
		this->head = nullptr;
		this->tail = nullptr;
	}
	else{
		if(this->head != rhs.head){
			if(!isEmpty()) this->removeAllNodes();
			Node<T> *curr,*currthis;
			curr = rhs.head;
			this->head = new Node<T>(curr->data,nullptr,nullptr);
			currthis = this->head;
			curr = curr->next;
			while(curr != nullptr){
				currthis->next = new Node<T>(curr->data,currthis,nullptr);
				currthis = currthis->next;
				curr = curr->next;
			}
			this->tail = currthis;
		}
	}
	return *this;
}

#endif //LINKEDLIST_H
