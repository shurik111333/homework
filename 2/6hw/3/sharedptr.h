#pragma once

/// Contains pointer to object and remove object, when no SharedPtr points to object
template <typename T>
class SharedPtr
{
public:
	SharedPtr(T *obj = nullptr):
	    pointer(new Pointer(obj))
	{}

	SharedPtr(const SharedPtr<T> &ptr);
	~SharedPtr();

	/**
	 * @brief getCount
	 * @return Return number of pointers to object
	 */
	int getCount() const;
	/**
	 * @brief getPointer
	 * @return Pointer to object
	 */
	T *getPointer() const;

	void operator = (const SharedPtr<T> &ptr);
	T &operator * () const;

private:
	/**
	 * @brief Contains pointer to object and number of shared pointers
	 */
	struct Pointer
	{
		T *object;
		int count;

		Pointer(T *ptr):
		    object(ptr),
		    count(1)
		{}

		~Pointer()
		{
			delete object;
		}
	};

	Pointer *pointer;

	void removePointer();
};

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &ptr):
    pointer(ptr.pointer)
{
	pointer->count++;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
	removePointer();
}

template <typename T>
int SharedPtr<T>::getCount() const
{
	return pointer->count;
}

template <typename T>
T *SharedPtr<T>::getPointer() const
{
	return pointer->object;
}

template <typename T>
void SharedPtr<T>::operator = (const SharedPtr<T> &ptr)
{
	removePointer();
	pointer = ptr.pointer;
	pointer->count++;
}

template <typename T>
T &SharedPtr<T>::operator * () const
{
	return *pointer->object;
}

template <typename T>
void SharedPtr<T>::removePointer()
{
	pointer->count--;
	if (pointer->count == 0)
		delete pointer;
}
