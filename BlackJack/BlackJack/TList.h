#pragma once
/*
template <class T>
struct Node{
	T* value;
	Node* next;
};
template <class T>
class TList{


private:
	Node<T>* first;
	Node<T>* end;

public:
	TList() :first(nullptr), end(nullptr){};
	~TList(){};
	void Insert(T node);
	
	T& operator[](int i){
		if (i == 0){
			return first;
		}
		Node* current = first;
		int count = 0;
		while (current->next != nullptr){
			if (count == i){
				return current->value;
			}
			current = current->next;
		}
		return nullptr;
		
	};
};
*/