#pragma once
#include <iostream>
#include <xkeycheck.h>
using namespace std;

template<class Key, class Value> 
class Table
{
protected:
	struct Row {
		Key key;
		Value value;

		Row() noexcept {
			key = Key();
			value = Value();
		}
		Row(Key k, Value v) noexcept {
			key = k;
			value = v;
		}
		Row(const Row& row) noexcept {
			key = row.key;
			value = row.value;
		}
		bool operator==(const Row& r) noexcept{
			return (key == r.key && value == r.value);
		}
		bool operator!=(const Row& r) noexcept{
			return (key != r.key || value != r.value);
		}
	};
	int size = 0;
	int maxsize = 100000;
public:
	int GetSize() const ;
	bool IsEmpty() const ;
	bool IsFull() const ;
	
	
	virtual Value* Find(Key _key)  = 0;
	virtual int Insert(Key _key, Value _val)  = 0;
	virtual int Delete(Key _key)  = 0;

	virtual void Reset(void)  = 0;
	virtual bool IsTabEnded(void) const  = 0;
	virtual int GoNext(void)  = 0;

	virtual Key GetKey(void) const  = 0;
	virtual Value* GetValuePtr(void)  = 0;	//	(=1 first el, if called on last cell of table)				

	friend ostream& operator<<(ostream& os, Table& tab) 
	{
		cout << "Table printing" << endl;
		if (!tab.IsEmpty()) {
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			os << "Key: " << tab.GetKey() << " Val: " << *(tab.GetValuePtr()) << endl;
		}
		return os;
		}
		else {
			os << "Key: " << "NONE" << " Val: " << "NONE" << endl;
			return os;
		}
	}
};

template<class Key, class Value>
bool Table<Key, Value>::IsFull() const 
{
	return size == maxsize;
}

template<class Key, class Value>
bool Table<Key, Value>::IsEmpty() const 
{
	return size == 0; 
}
template<class Key, class Value>
int Table<Key, Value>::GetSize() const 
{
	return size;
}

