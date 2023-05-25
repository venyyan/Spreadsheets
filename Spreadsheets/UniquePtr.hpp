#pragma once

template <typename T>
class UniquePtr {
private:
	T* ptr = nullptr;
public:
	UniquePtr() = default;
	UniquePtr(T* ptr);

	UniquePtr(const UniquePtr& other) = delete;
	UniquePtr& operator=(const UniquePtr& other) = delete;

	UniquePtr(UniquePtr&& other) noexcept;
	UniquePtr& operator=(UniquePtr&& other) noexcept;

	~UniquePtr();

private:
	void MoveFrom(UniquePtr&& other);
	void Free();
public:
	T& operator*();
	T operator*() const;

	T* operator->() const;

	operator bool() const;
	bool operator!() const;
};

template <typename T>
UniquePtr<T>::UniquePtr<T>(T* ptr) {
	this->ptr = ptr;
}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept {
	MoveFrom(std::move(other));
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
	if (this != &other) {
		Free();
		MoveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
UniquePtr<T>::~UniquePtr() {
	Free();
}

template <typename T>
void UniquePtr<T>::MoveFrom(UniquePtr&& other) {
	this->ptr = other.ptr;
	other.ptr = nullptr;
}

template <typename T>
void UniquePtr<T>::Free() {
	delete ptr;
}

template <typename T>
T& UniquePtr<T>::operator*() {
	return *this->ptr;
}

template <typename T>
T UniquePtr<T>::operator*() const {
	return *this->ptr;
}

template <typename T>
UniquePtr<T>::operator bool() const {
	return (this->ptr != nullptr);
}

template <typename T>
bool UniquePtr<T>::operator!() const {
	return (this->ptr == nullptr);
}

template <typename T>
T* UniquePtr<T>::operator->() const {
	return this->ptr;
}