#pragma once
#include <iostream>
using namespace std;

template<class T>
class TList
{
protected:
	template <class T>
	struct TNode // cell
	{
		T value;
		TNode<T>* pNext;

		TNode<T>* get_next(void) 
		{
			return pNext;
		}
		bool operator==(const TNode<T>& n) {
			return (this->value == n.value && this->pNext == n.pNext);
		}
		
		bool operator!=(const TNode<T>& n) {
			return (this->value != n.value || this->pNext != n.pNext);
		}
	};

	TNode<T>* pFirst;			// First cell
	TNode<T>* pLast;			// Last cell
	TNode<T>* pCurrent;			// Current cell
	TNode<T>* pPrevious;		// Previous cell
	TNode<T>* pStop;			// Value saying abt end of the list
	int length;					// Size

public:
	TList();
	~TList();
	int GetLength() const;		// +
	bool IsEmpty();				// +

	// вставка звеньев
	void InsertFirst(T item); // перед первым
	void InsertCurrent(T item); // перед текущим 
	void InsertNextCurrent(T item); // после текущего                           //TODO
	void InsertLast(T item);  // вставить последним 


	// удаление звеньев
	int DeleteFirst(); // удалить первое звено 
	int DeleteCurrent(); // удалить текущее звено



	void GoNext(); // сдвиг вправо текущего звена
	//(=1 после применения GoNext для последнего звена списка)

	void Reset(); // установить на начало списка
	bool IsEnd() const;  // список завершен ?
	bool IsNextEnd() const;  // список завершен ?

	T GetCurrentItem();
	T* GetCurrentItemPtr() const;
	int SetCurrentItem(T item);

	bool operator==(const TList<T>& other) const;
	//bool operator!=(const TList<T>& other) const;
};



template<class T>
TList<T>::TList() {
	pFirst = nullptr;
	pCurrent = nullptr;
	pPrevious = nullptr;
	pLast = nullptr;
	pStop = nullptr;
	length = 0;
}

template<class T>
TList<T>::~TList()
{
	while (!IsEmpty()) {
		DeleteFirst();
	}
}

template<class T>
int TList<T>::GetLength() const
{
	return this->length;
}

template<class T>
bool TList<T>::IsEmpty()
{
	return pFirst == nullptr;
}

template<class T>
void TList<T>::InsertFirst(T item)
{
	TNode<T>* n = new TNode<T>{ item, pFirst };
	pFirst = n;
	if (IsEmpty()) 
		pLast = pFirst;
	length++;
}

template<class T>
void TList<T>::InsertCurrent(T item)
{
	if (pCurrent == pFirst || pCurrent == nullptr) {
		this->InsertFirst(item);
		return;
	}
	TNode<T>* n = new TNode<T>{ item, pCurrent };
	pPrevious->pNext = n;
	length++;
}

template<class T>
void TList<T>::InsertNextCurrent(T item) //
{
	return;
}

template<class T>
void TList<T>::InsertLast(T item)
{
	TNode<T>* n = new TNode<T>{ item, nullptr };
	if (pFirst == NULL && length == 0) {
		pLast = n;
		pFirst = pCurrent = pLast;
	}
	else {
		pLast->pNext = n;
		pLast = n;
	}
	length++;
}

template<class T>
int TList<T>::DeleteFirst()
{
	if (IsEmpty()) return -1;
	TNode<T>* n = pFirst;
	pFirst = pFirst->pNext;
	if (pFirst == nullptr)
		pLast = nullptr;
	delete n;
	length--;
	return 0;
}

template<class T>
int TList<T>::DeleteCurrent()
{
	if (pCurrent == nullptr) 
		return -1;
	if (pCurrent == pFirst) {
		this->DeleteFirst();
		return 0;
	}
	if (pCurrent == pLast) {
		delete pCurrent;
		pPrevious->pNext = nullptr;
		pLast = pPrevious;
		pCurrent = nullptr;
	}
	else {
		pPrevious->pNext = pCurrent->pNext;
		delete pCurrent;
		pCurrent = pPrevious->pNext;
	}
	length--;
}

template<class T>
void TList<T>::GoNext()
{
	pPrevious = pCurrent;
	pCurrent = pCurrent->pNext;
	if (pCurrent == pStop || pCurrent == nullptr)
		pLast = pPrevious;
}

template<class T>
void TList<T>::Reset()
{
	pCurrent = pFirst;
	pPrevious = nullptr;
}

template<class T>
bool TList<T>::IsEnd() const
{
	return pCurrent == pStop;
}
template<class T>
bool TList<T>::IsNextEnd() const  // next el is empty???
{
	return pCurrent->get_next() == nullptr;
}


template<class T>
T TList<T>::GetCurrentItem()
{
	return (pCurrent != nullptr) ? pCurrent->value : throw runtime_error("List is empty");
}

template<class T>
T* TList<T>::GetCurrentItemPtr() const
{
	return (pCurrent != nullptr) ? &pCurrent->value : throw runtime_error("List is empty");
}

template<class T>
int TList<T>::SetCurrentItem(T item)
{
	if (pCurrent == nullptr)
		return -1;
	else {
		pCurrent->value = item;
	}
	return 0;
}
template<class T>
bool TList<T>::operator==(const TList<T>& other) const {
	// Check if the lists are of the same length
	if (length != other.length) {
		return false;
	}

	// Compare each element in the lists
	TNode<T>* node1 = pFirst;
	TNode<T>* node2 = other.pFirst;

	while (node1 != nullptr && node2 != nullptr) {
		if (node1->value != node2->value) {
			return false;
		}
		node1 = node1->pNext;
		node2 = node2->pNext;
	}

	// If all elements are equal, return true
	return true;
}
