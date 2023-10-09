#pragma once
#include <iostream>
using namespace std;
template<typename type>
class Array
{
private:
	type* arr;
	size_t size;
	size_t UpperBound;
public:
	Array();
	Array(size_t size);
	Array(type* arr, size_t size);
	Array(const Array& other);
	~Array();

	type* GetArr() const;

	void SetSize(size_t size, size_t grow = 1);
	size_t GetSize() const;
	size_t GetUpperBound() const;
	bool  IsEmpty() const;
	void FreeExtra();
	void RemoveAll();
	void SetAt(size_t index, type item);
	type GetAt(size_t index);
	void Add(const type item, const size_t grow = 1);
	void Append(const Array& R);
	type* GetData() const;
	void InsertAt(size_t index, type item);
	void RemoveAt(size_t index);

	Array& operator=(const Array& other) noexcept;
	type operator[](const type index) noexcept;

	void Init();
	bool ValidIndex(size_t index);
};

template<typename type>
Array<type>& Array<type>::operator=(const Array<type>& other) noexcept {
	if (other != this) {
		delete[] arr;
		size = other.size;
		arr = new type[size];
		for (int i = 0; i < size; i++)
			arr[i] = other.arr[i];
	}
}

template<typename type>
Array<type>::Array() {
	size = 0;
	UpperBound = 0;
	arr = NULL;
}

template<typename type>
Array<type>::Array(size_t size) : size(size), UpperBound(0) {
	arr = new type[this->size];
}

template<typename type>
Array<type>::Array(type* arr, size_t size) : Array(size) {
	for (int i = 0; i < size; i++)
		this->arr[i] = arr[i];
}

template<typename type>
Array<type>::Array(const Array<type>& other) : Array(other.arr, other.size) {}

template<typename type>
Array<type>::~Array() { delete[] arr; }

template<typename type>
type* Array<type>::GetArr() const { return arr; }

template<typename type>
void Array<type>::SetSize(size_t size, size_t grow) {
	type* temp;
	int n = 0;
	if (this->size > size) {
		temp = new type[size * grow];
		for (int i = 0; i < size; i++) {
			temp[n++] = arr[i];
			for (int j = 1; j < grow; j++)
				temp[n++] = 0;
		}
		delete[] arr;
		arr = temp;
		this->size = size * grow;
	}
	else if (this->size < size) {
		temp = new type[size * grow];
		for (int i = 0; i < this->size; i++) {
			temp[n++] = arr[i];
			for (int j = 1; j < grow; j++)
				temp[n++] = 0;
		}
		for (int i = this->size; i < size; i++) {
			temp[n++] = 0;
			for (int j = 1; j < grow; j++)
				temp[n++] = 0;
		}
		delete[] arr;
		arr = temp;
		this->size = size * grow;
	}
	else if (this->size == size) {
		temp = new type[size * grow];
		for (int i = 0; i < this->size; i++) {
			temp[n++] = arr[i];
			for (int j = 1; j < grow; j++)
				temp[n++] = 0;
		}
		delete[] arr;
		arr = temp;
		this->size = size * grow;
	}
}

template<typename type>
size_t Array<type>::GetSize() const { return size; }

template<typename type>
ostream& operator<<(ostream& out, const Array<type>& R) {
	for (int i = 0; i < R.GetSize(); i++)
		out << R.GetArr()[i] << ' ';
	out << endl;
	return out;
}

template<typename type>
size_t Array<type>::GetUpperBound() const {
	return UpperBound;
}

template<typename type>
bool Array<type>::IsEmpty() const {
	return size == 0;
}

template<typename type>
void Array<type>::FreeExtra() {
	for (int i = size - UpperBound; i < size; i++)
		arr[i] = arr[i + 1];
	size -= UpperBound;
	type* temp = new type[size];
	for (int i = 0; i < size; i++)
		temp[i] = arr[i];
	delete[] arr;
	arr = temp;
}

template<typename type>
void Array<type>::RemoveAll() {
	size = 0;
	arr = NULL;
}

template<typename type>
bool Array<type>::ValidIndex(size_t index) {
	return (index >= 0) && (index < size);
}

template<typename type>
type Array<type>::GetAt(size_t index) {
	if (ValidIndex(index))
		return arr[index];
	exit(-1);
}

template<typename type>
void Array<type>::SetAt(size_t index, type item) {
	if (ValidIndex(index))
		arr[index] = item;
	else
		cout << "Incorrect index!" << endl;
}

template<typename type>
type Array<type>::operator[](const type index) noexcept {
	if (ValidIndex(index))
		return arr[index];
	exit(-1);
}

template<typename type>
void Array<type>::Add(const type item, const size_t grow) {
	size++;
	type* temp = new type[size * grow];
	int n = 0;
	for (int i = 0; i < size; i++) {
		temp[n++] = arr[i];
		for (int j = 1; j < grow; j++)
			temp[n++] = 0;
	}
	size *= grow;
	temp[size - grow] = item;
	delete[] arr;
	arr = temp;
	UpperBound = grow - 1;
}

template<typename type>
void Array<type>::Append(const Array& R) {
	type* temp = new type[size + R.size];
	for (int i = 0; i < size; i++)
		temp[i] = arr[i];
	for (int i = size, j = 0; i < size + R.size; i++, j++)
		temp[i] = R.arr[j];
	delete[] arr;
	arr = temp;
	size += R.size;
	UpperBound = R.size - 1;
}

template<typename type>
type* Array<type>::GetData() const {
	return arr;
}

template<typename type>
void Array<type>::InsertAt(size_t index, type item) {
	if (ValidIndex(index) == false)
		exit(-1);
	size++;
	type* temp = new type[size];

	for (int i = 0; i < index; i++)
		temp[i] = arr[i];
	for (int i = index; i < size - 1; i++)
		temp[i + 1] = arr[i];
	temp[index] = item;
	delete[] arr;
	arr = temp;
	UpperBound = 0;
}

template<typename type>
void Array<type>::RemoveAt(size_t index) {
	if (ValidIndex(index) == false)
		exit(-1);
	for (int i = index; i < size - 1; i++)
		arr[i] = arr[i + 1];
	size--;
	type* temp = new type[size];
	for (int i = 0; i < size; i++)
		temp[i] = arr[i];
	delete[] arr;
	arr = temp;
}

template<typename type>
void Array<type>::Init() {
	if (is_same<type, float>::value) {
		float a;
		for (int i = 0; i < size; i++) {
			arr[i] = rand() % 100;
			a = rand() % 100;
			while (a > 1)
				a /= 10;
			arr[i] += a;
		}
	}
	else {
		for (int i = 0; i < size; i++)
			arr[i] = rand() % 100;
	}
}