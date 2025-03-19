#pragma once
#include <memory>

template<typename ElementT>
class IteratorVector;

template <typename ElementT>
class DynamicArray {
private:
	int cap;
	ElementT* elems;
	int lungime;

public:
	DynamicArray();
	DynamicArray(const DynamicArray& ot);
	~DynamicArray();

	void push_back(const ElementT& el);
	ElementT& get(int poz) const;
	void set(int poz, const ElementT& el);
	int size() const noexcept;
	void erase(int poz);

	ElementT& operator[](int poz) noexcept;

	ElementT* getALL() const;

	DynamicArray& operator=(const DynamicArray& ot);

	friend class IteratorVector<ElementT>;
	IteratorVector<ElementT> begin();
	IteratorVector<ElementT> end();
};

template <typename ElementT>
DynamicArray<ElementT>::DynamicArray() {
	this->elems = new ElementT[10];
	this->cap = 10;
	this->lungime = 0;
}

template <typename ElementT>
DynamicArray<ElementT>::DynamicArray(const DynamicArray& ot) {
	this->cap = ot.cap;
	this->lungime = ot.lungime;
	this->elems = new ElementT[this->cap];
	for (int i = 0; i < this->cap && i < this->lungime; i++)
		this->elems[i] = ot.elems[i];
}

template <typename ElementT>
DynamicArray<ElementT>::~DynamicArray(){
	delete[] elems;
}

template <typename ElementT>
void DynamicArray<ElementT>::push_back(const ElementT& el) {

	if (this->lungime == this->cap)
	{
		ElementT* new_elems = new ElementT[this->cap * 2];
		this->cap = this->cap * 2;
		for (int i = 0; i < this->lungime; i++)
			new_elems[i] = this->elems[i];
		
		delete[] this->elems;
		this->elems = new_elems;
	}

	this->elems[this->lungime] = el;
	this->lungime++;

}

template <typename ElementT>
ElementT& DynamicArray<ElementT>::get(int poz) const {
	return this->elems[poz];
}

template <typename ElementT>
int DynamicArray<ElementT>::size() const noexcept {
	return this->lungime;
}

template <typename ElementT>
void DynamicArray<ElementT>::set(int poz, const ElementT& el) {
	this->elems[poz] = el;
}

template <typename ElementT>
ElementT* DynamicArray<ElementT>::getALL() const{
	return this->elems;
}
template <typename ElementT>
void DynamicArray<ElementT>::erase(int poz) {

	ElementT* els = new ElementT[this->cap];
	for (int i = 0; i < poz; i++) {
		*(els + i) = *(this->elems + i);
	}
	for (int i = poz; i < this->lungime; i++) {
		*(els + i) = *(this->elems + i + 1);
	}
	delete[] this->elems;
	this->elems = els;
	this->lungime--;
}

template <typename ElementT>
DynamicArray<ElementT>& DynamicArray<ElementT>::operator=(const DynamicArray& ot) {

	if (this == &ot) {
		return *this;
	}
	//fiindca in obiectul curent punem altceva prin
	//assignment, eliberam memoria alocata anterior

	delete[] this->elems;

	//copiem elementele din ot si setam lungime, capacitate
	this->elems = new ElementT[ot.cap];
	for (int i = 0; i < ot.lungime; i++) {
		elems[i] = ot.elems[i];  //utilizeaza operator assignment aferent tipului T
	}
	this->lungime = ot.lungime;
	this->cap = ot.cap;
	return *this;
}

template <typename ElementT>
ElementT& DynamicArray<ElementT>::operator[](int poz) noexcept{
	return this->elems[poz];
}

template<typename ElementT>
IteratorVector<ElementT> DynamicArray<ElementT>::begin() {
	return IteratorVector<ElementT>(*this);
}

template<typename ElementT>
IteratorVector<ElementT> DynamicArray<ElementT>::end() {
	return IteratorVector<ElementT>(*this, this->lungime);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------

template<typename ElementT>

class IteratorVector {
private:
	const DynamicArray<ElementT>& v;
	int poz = 0;
public:
	IteratorVector(const DynamicArray<ElementT>& v) noexcept;
	IteratorVector(const DynamicArray<ElementT>& v, int poz) noexcept;
	IteratorVector(const IteratorVector& it) noexcept;
	bool valid() const;
	ElementT& element() const;
	void next();
	ElementT& operator*();
	IteratorVector& operator++();
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;
	friend class DynamicArray<ElementT>;

};

template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const DynamicArray<ElementT>& da) noexcept :v { da } { };

template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const DynamicArray<ElementT>& v, int poz) noexcept :v{ v }, poz{ poz } {};

template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const IteratorVector<ElementT>& it) noexcept : v{ it.v }, poz{ it.poz } {};

template<typename ElementT>
bool IteratorVector<ElementT>::valid() const {
	return this->poz < this->v.lungime;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::element() const {
	return this->v.getALL()[this->poz];
}

template<typename ElementT>
void IteratorVector<ElementT>::next() {
	poz++;
}

template<typename ElementT>
IteratorVector<ElementT>& IteratorVector<ElementT>::operator++() {
	next();
	return *this;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::operator*() {
	return element();
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator!=(const IteratorVector& ot) noexcept {
	return !(*this == ot);
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator==(const IteratorVector& ot) noexcept {
	return poz == ot.poz;
}