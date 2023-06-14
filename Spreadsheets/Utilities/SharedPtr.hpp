#pragma once

template<typename T>
class SharedPtr {
private:
	T* data = nullptr;
	size_t* counter = nullptr;

public:
	SharedPtr() = default;
	SharedPtr(T* data);
	SharedPtr(const SharedPtr<T>& other);
	SharedPtr(SharedPtr<T>&& other) noexcept;
	SharedPtr<T>& operator=(const SharedPtr<T>& other);
	SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;
	~SharedPtr();

	const T* operator->() const;
	T* operator->();
	const T& operator*() const;
	T& operator*();

	T* get() const;
	void reset(T* data = nullptr);
	size_t getCount() const;

	explicit operator bool() const;

private:
	void copyFrom(const SharedPtr<T>& other);
	void move(SharedPtr<T>&& other) noexcept;
	void free();
};


template<typename T>
SharedPtr<T>::SharedPtr(T* data) {
	this->data = data;
	if (this->data) {
		counter = new size_t(1);
	}
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
	copyFrom(other);
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept {
	move(std::move(other));
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
	free();
}

template<typename T>
const T* SharedPtr<T>::operator->() const {
	return data;
}

template<typename T>
T* SharedPtr<T>::operator->() {
	return data;
}

template<typename T>
const T& SharedPtr<T>::operator*() const {
	return *data;
}

template<typename T>
T& SharedPtr<T>::operator*() {
	return *data;
}

template<typename T>
T* SharedPtr<T>::get() const {
	return data;
}

template<typename T>
void SharedPtr<T>::reset(T* data) {
	if (this->data == data) {
		return;
	}

	free();
	this->data = data;
	if (this->data) {
		counter = new size_t(1);
	}
}

template<typename T>
size_t SharedPtr<T>::getCount() const {
	return counter;
}

template<typename T>
SharedPtr<T>::operator bool() const {
	return data;
}

template<typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other) {
	data = other.data;
	counter = other.counter;
	if (data) {
		(*counter)++;
	}
}

template<typename T>
void SharedPtr<T>::move(SharedPtr<T>&& other) noexcept {
	data = other.data;
	counter = other.counter;

	other.data = nullptr;
	other.counter = nullptr;
}

template<typename T>
void SharedPtr<T>::free() {
	if (!data) {
		return;
	}

	if ((*counter) == 1) {
		delete data;
		delete counter;
	}
	else {
		(*counter)--;
	}
}
//
//#pragma once
//
//template<class T>
//class SharedPtr {
//private:
//
//	T* data = nullptr;
//	size_t* count;
//
//	void Free();
//	void CopyFrom(const SharedPtr<T>&);
//	void MoveFrom(SharedPtr<T>&&);
//public:
//	SharedPtr();
//	SharedPtr(T*);
//
//	void Reset();
//
//	SharedPtr(const SharedPtr<T>&);
//	SharedPtr(SharedPtr<T>&&);
//
//	const T& operator*() const;
//	T& operator*();
//
//	const T* operator->() const;
//	T* operator->();
//
//	bool operator==(const SharedPtr<T>& other);
//	bool operator!=(const SharedPtr<T>& other);
//
//	bool Unique() const;
//	bool IsNullPtr() const;
//
//	bool operator!() const;
//
//
//	size_t RefCount() const;
//
//	SharedPtr<T>& operator=(const SharedPtr<T>&);
//	SharedPtr<T>& operator=(SharedPtr<T>&&) noexcept;
//
//	~SharedPtr();
//};
//
//template<class T>
//void SharedPtr<T>::Free() {
//	if (count && --(*count) == 0) {
//		delete data;
//		delete count;
//		data = nullptr;
//		count = nullptr;
//	}
//}
//
//template<class T>
//void SharedPtr<T>::CopyFrom(const SharedPtr<T>& other) {
//	data = other.data;
//	count = other.count;
//	(*count)++;
//}
//
//template<class T>
//void SharedPtr<T>::MoveFrom(SharedPtr<T>&& other) {
//	data = other.data;
//	count = other.count;
//	other.data = nullptr;
//	other.count = nullptr;
//}
//
//template<class T>
//SharedPtr<T>::SharedPtr() {
//	data = nullptr;
//	count = new size_t(1);
//}
//
//template<class T>
//SharedPtr<T>::SharedPtr(T* ptr) {
//	this->data = ptr;
//	count = new size_t(1);
//}
//
//template<class T>
//void SharedPtr<T>::Reset() {
//	*this = SharedPtr();
//}
//
//template<class T>
//SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
//	CopyFrom(other);
//}
//
//template<class T>
//SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) {
//	MoveFrom(std::move(other));
//}
//
//template<class T>
//bool SharedPtr<T>::Unique() const {
//	return RefCount() == 1;
//}
//
//template<class T>
//bool SharedPtr<T>::IsNullPtr() const
//{
//	return data == nullptr;
//}
//
//template<class T>
//bool SharedPtr<T>::operator!() const {
//	return data == nullptr;
//}
//
//template<class T>
//const T& SharedPtr<T>::operator*() const {
//	return *data;
//}
//
//template<class T>
//T& SharedPtr<T>::operator*() {
//	return *data;
//}
//
//template<class T>
//const T* SharedPtr<T>::operator->() const {
//	return data;
//}
//
//template<class T>
//T* SharedPtr<T>::operator->() {
//	return data;
//}
//
//template<class T>
//bool SharedPtr<T>::operator==(const SharedPtr<T>& other)
//{
//	return data == other.data;
//}
//
//template<class T>
//bool SharedPtr<T>::operator!=(const SharedPtr<T>& other)
//{
//	return !(this == other);
//}
//
//template<class T>
//size_t SharedPtr<T>::RefCount() const {
//	return *count;
//}
//
//template<class T>
//SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
//	if (this != &other) {
//		Free();
//		CopyFrom(other);
//	}
//
//	return *this;
//}
//
//template<class T>
//SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
//	if (this != &other) {
//		Free();
//		MoveFrom(std::move(other));
//	}
//
//	return *this;
//}
//
//template<class T>
//SharedPtr<T>::~SharedPtr() {
//	Free();
//}