#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

///@brief Multiset
template <typename T>
class Bag
{
public:
	Bag():
	    set(nullptr)
	{
		srand(time(0));
	}
	~Bag();

	void insert(const T &value, int count = 1);
	/**
	 * @brief remove Remove all elements with input value
	 * @param value
	 */
	void remove(const T &value);
	/**
	 * @brief find
	 * @param value
	 * @return Return number of elements, that equals value. Return 0, if value does not exist
	 */
	int find(const T &value);
	bool exist(const T &value);
	int size() const;
	/**
	 * @brief Remove all values form set. This calls destructor for each value.
	 */
	void clear();
	/**
	 * @brief Intersec two sets.
	 * @param set Set for intersec.
	 * @param result Result of intersec will be in result. This calls clear() for result.
	 */
	void intersec(Bag<T> &set, Bag<T> &result) const;
	/**
	 * @brief Merge two sets in result.
	 * @param set
	 * @param result
	 */
	void merge(Bag<T> &set, Bag<T> &result) const;

private:
	/**
	 * @brief Cartesian tree with random priority.
	 */
	class Treap;

	struct SplitedTreap
	{
		Treap *left;
		Treap *right;
	};

	class Treap
	{
	public:
		const T value;
		const int priority;
		int size;
		int height;
		int count;
		Treap *left;
		Treap *right;

		/**
		 * @brief Recalculate size and height of treap.
		 */
		void update();
		//const int
		Treap(const T &value, int count = 1):
		    value(value),
		    priority(rand()),
		    size(1),
		    height(1),
		    count(count),
		    left(nullptr),
		    right(nullptr)
		{}
		~Treap()
		{}

		int getPriority() const;
		static void removeTree(Treap *treap);
		static int getHeight(Treap *treap);
		static int getSize(Treap *treap);
		/**
		 * @brief Merge two treaps. All values in left treap must be less, than values in right treap.
		 * @param leftTreap
		 * @param rightTreap
		 * @return Merge of two treaps.
		 */
		static Treap *merge(Treap *leftTreap, Treap *rightTreap);
		static Treap *merge(SplitedTreap treap);
		/**
		 * @brief Cut input treap in two treaps. Left treap contains all values, that less input value.
		 *        Right treap contains all other values.
		 * @param treap
		 * @param value
		 * @return
		 */
		static SplitedTreap splitByValue(Treap *treap, const T &value);
		/**
		 * @brief Cut first "number" values from input treap.
		 * @param treap
		 * @param number
		 * @return
		 */
		static SplitedTreap splitByNumber(Treap *treap, int number);
	};

	Treap *set;

	/**
	 * @brief Copy all values from current set to result with input predicate.
	 *        Without predicate all values will be copied.
	 * @param result
	 * @param p Predicate, which return true for values, that must be copied.
	 */
	void copyTo(Bag<T> &result, const function<bool (const T&)> &p = [] (const T&) -> bool {return true;}) const;
};

// Set ------------------------------------------------------

template <typename T>
Bag<T>::~Bag()
{
	this->clear();
}

template <typename T>
void Bag<T>::insert(const T &value, int count)
{
	if (count < 1)
		return;
	SplitedTreap left = Treap::splitByValue(set, value);
	if (left.right == nullptr)
	{
		set = Treap::merge(left.left, new Treap(value, count));
		return;
	}
	SplitedTreap right = Treap::splitByNumber(left.right, 1);
	assert(Treap::getSize(right.left) == 1);
	if (value < right.left->value)
		right.left = Treap::merge(new Treap(value, count), right.left);
	else
		right.left->count += count;
	set = Treap::merge(left.left, Treap::merge(right));
}

template <typename T>
void Bag<T>::remove(const T &value)
{
	SplitedTreap left = Treap::splitByValue(set, value);
	if (left.right == nullptr)
		return;
	SplitedTreap right = Treap::splitByNumber(left.right, 1);
	if (!(value < right.left->value))
	{
		delete right.left;
		right.left = nullptr;
	}
	set = Treap::merge(left.left, Treap::merge(right));
}

template <typename T>
int Bag<T>::find(const T &value)
{
	SplitedTreap left = Treap::splitByValue(set, value);
	if (left.right == nullptr)
		return 0;
	SplitedTreap right = Treap::splitByNumber(left.right, 1);
	int result = 0;
	if (!(value < right.left->value))
		result = right.left->count;
	set = Treap::merge(left.left, Treap::merge(right));
	return result;
}

template <typename T>
bool Bag<T>::exist(const T &value)
{
	return find(value) > 0;
}

template <typename T>
int Bag<T>::size() const
{
	return Treap::getSize(set);
}

template <typename T>
void Bag<T>::clear()
{
	Treap::removeTree(set);
	set = nullptr;
}

template <typename T>
void Bag<T>::intersec(Bag<T> &set, Bag<T> &result) const
{
	queue<Treap*> q;
	q.push(this->set);
	while (!q.empty())
	{
		Treap *t = q.front();
		q.pop();
		if (t == nullptr)
			continue;
		result.insert(t->value, min(t->count, set.find(t->value)));
		q.push(t->left);
		q.push(t->right);
	}
}

template <typename T>
void Bag<T>::merge(Bag<T> &set, Bag<T> &result) const
{
	copyTo(result);
	set.copyTo(result);
}

template <typename T>
void Bag<T>::copyTo(Bag<T> &result, const function<bool (const T&)> &p) const
{
	queue<Treap*> q;
	q.push(this->set);
	while (!q.empty())
	{
		Treap *t = q.front();
		q.pop();
		if (t == nullptr)
			continue;
		if (p(t->value))
			result.insert(t->value, t->count);
		q.push(t->left);
		q.push(t->right);
	}
}

// Set::Treap -----------------------------------------------

template <typename T>
void Bag<T>::Treap::update()
{
	size = getSize(left) + getSize(right) + 1;
	height = std::max(getHeight(left), getHeight(right)) + 1;
}

template <typename T>
int Bag<T>::Treap::getPriority() const
{
	return priority;
}

template <typename T>
void Bag<T>::Treap::removeTree(Treap *treap)
{
	if (treap == nullptr)
		return;
	removeTree(treap->left);
	removeTree(treap->right);
	delete treap;
}

template <typename T>
int Bag<T>::Treap::getHeight(Treap *t)
{
	return t == nullptr ? 0 : t->height;
}

template <typename T>
int Bag<T>::Treap::getSize(Bag::Treap *treap)
{
	return treap == nullptr ? 0 : treap->size;
}

template <typename T>
typename Bag<T>::Treap *Bag<T>::Treap::merge(Treap *leftTreap, Treap *rightTreap)
{
	if (leftTreap == nullptr)
		return rightTreap;
	if (rightTreap == nullptr)
		return leftTreap;
	Treap *result = nullptr;
	if (leftTreap->getPriority() < rightTreap->getPriority())
	{
		leftTreap->right = merge(leftTreap->right, rightTreap);
		result = leftTreap;
	}
	else
	{
		rightTreap->left = merge(leftTreap, rightTreap->left);
		result = rightTreap;
	}
	result->update();
	return result;
}

template <typename T>
typename Bag<T>::Treap *Bag<T>::Treap::merge(SplitedTreap treap)
{
	return merge(treap.left, treap.right);
}

template <typename T>
typename Bag<T>::SplitedTreap Bag<T>::Treap::splitByValue(Treap *treap, const T &value)
{
	if (treap == nullptr)
		return {nullptr, nullptr};
	SplitedTreap result = {nullptr, nullptr};
	if (treap->value < value)
	{
		SplitedTreap tmp = splitByValue(treap->right, value);
		treap->right = tmp.left;
		result = {treap, tmp.right};
	}
	else
	{
		SplitedTreap tmp = splitByValue(treap->left, value);
		treap->left = tmp.right;
		result = {tmp.left, treap};
	}
	treap->update();
	return result;
}

template <typename T>
typename Bag<T>::SplitedTreap Bag<T>::Treap::splitByNumber(Bag::Treap *treap, int number)
{
	if (treap == nullptr)
		return {nullptr, nullptr};
	SplitedTreap result = {nullptr, nullptr};
	if (number < getSize(treap->left) + 1)
	{
		SplitedTreap tmp = splitByNumber(treap->left, number);
		treap->left = tmp.right;
		result = {tmp.left, treap};
	}
	else
	{
		SplitedTreap tmp = splitByNumber(treap->right, number - getSize(treap) - 1);
		treap->right = tmp.left;
		result = {treap, tmp.right};
	}
	treap->update();
	return result;
}
