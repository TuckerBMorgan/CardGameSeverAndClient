/*
#include "TList.h"

template<class T>
void TList<T>::Insert(T node){
	if (first == nullptr){
		Node fn;
		fn.value = node;
		fn.next = end;
		end = first;
		return;
	}
	if (first == end){
		Node en;
		en.value = node;
		en.next = nullptr;
		end = en;
		return;
	}
	Node n;
	n.value = node;
	end.next = n;
	n.next = nullptr;
}
*/