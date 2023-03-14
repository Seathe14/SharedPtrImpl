#pragma once
template <typename T>
class SharedPtr
{
public:
	using uint = unsigned int;
	explicit SharedPtr(T* ptr = nullptr) : data(ptr), counter(new uint(0)) {
		if (ptr) {
			(*counter)++;
		}
	}
	SharedPtr(const SharedPtr& obj) : data(obj.data), counter(obj.counter) {
		(*counter)++;
	}
	SharedPtr(SharedPtr&& other) noexcept {
		data = other.data;
		counter = other.counter;
		other.data = nullptr;
		other.counter = nullptr;
	}
	SharedPtr& operator=(const SharedPtr& other) {
		decreaseCounter();
		data = other.data;
		counter = other.counter;
		(*counter)++;
		return *this;
	}
	SharedPtr& operator=(SharedPtr&& other) noexcept {
		decreaseCounter();
		data = other.data;
		counter = other.counter;
		other.data = nullptr;
		other.counter = nullptr;
		return *this;
	}
	~SharedPtr() {
		decreaseCounter();
	}
	T& operator*() {
		return *data;
	}
	T* operator->() {
		return data;
	}
private:
	T* data{ nullptr };
	uint* counter{ nullptr };
	void decreaseCounter() {
		if (data && counter) {
			(*counter)--;
			if ((*counter) == 0) {
				delete data;
			}
		}
	}
};

template<typename T, typename ... Args>
SharedPtr<T> MakeShared(Args&&... args) {
	return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

