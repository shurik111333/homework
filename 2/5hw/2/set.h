#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

template <typename T>
class Set
{
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
		Treap *left;
		Treap *right;

		/**
		 * @brief Recalculate size and height of treap.
		 */
		void update();

		Treap(const T &value):
		    value(value),
		    priority(rand()),
		    size(1),
		    height(1),
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

public:
	Set():
	    set(nullptr)
	{
		srand(time(0));
	}
	~Set();

	void insert(const T &value);
	void remove(const T &value);
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
	void intersec(Set<T> &set, Set<T> &result) const;
	/**
	 * @brief Merge two sets in result.
	 * @param set
	 * @param result
	 */
	void merge(Set<T> &set, Set<T> &result) const;
	/**
	 * @brief Copy all values from current set to result with input predicate.
	 *        Without predicate all values will be copied.
	 * @param result
	 * @param p Predicate, which return true for values, that must be copied.
	 */
	void copyTo(Set<T> &result, const function<bool(const T&)> &p = [] (const T&) {return true;}) const;
};

// Set ------------------------------------------------------

template <typename T>
Set<T>::~Set()
{
	this->clear();
}

template <typename T>
void Set<T>::insert(const T &value)
{
	SplitedTreap left = Treap::splitByValue(set, value);
	if (left.right == nullptr)
	{
		set = Treap::merge(left.left, new Treap(value));
		return;
	}
	SplitedTreap right = Treap::splitByNumber(left.right, 1);
	assert(Treap::getSize(right.left) == 1);
	if (value < right.left->value)
		right.left = Treap::merge(new Treap(value), right.left);
	set = Treap::merge(left.left, Treap::merge(right));
}

template <typename T>
void Set<T>::remove(const T &value)
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
bool Set<T>::exist(const T &value)
{
	SplitedTreap left = Treap::splitByValue(set, value);
	if (left.right == nullptr)
		return false;
	SplitedTreap right = Treap::splitByNumber(left.right, 1);
	bool result = !(value < right.left->value);
	set = Treap::merge(left.left, Treap::merge(right));
	return result;
}

template <typename T>
int Set<T>::size() const
{
	return Treap::getSize(set);
}

template <typename T>
void Set<T>::clear()
{
	Treap::removeTree(set);
	set = nullptr;
}

template <typename T>
void Set<T>::intersec(Set<T> &set, Set<T> &result) const
{
	copyTo(result, [&set] (const T &value) ->bool {return set.exist(value);});
}

template <typename T>
void Set<T>::merge(Set<T> &set, Set<T> &result) const
{
	copyTo(result);
	set.copyTo(result);
}

template <typename T>
void Set<T>::copyTo(Set<T> &result, const function<bool (const T &)> &p) const
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
			result.insert(t->value);
		q.push(t->left);
		q.push(t->right);
	}
}

// Set::Treap -----------------------------------------------

template <typename T>
void Set<T>::Treap::update()
{
	size = getSize(left) + getSize(right) + 1;
	height = std::max(getHeight(left), getHeight(right)) + 1;
}

template <typename T>
int Set<T>::Treap::getPriority() const
{
	return priority;
}

template <typename T>
void Set<T>::Treap::removeTree(Treap *treap)
{
	if (treap == nullptr)
		return;
	removeTree(treap->left);
	removeTree(treap->right);
	delete treap;
}

template <typename T>
int Set<T>::Treap::getHeight(Treap *t)
{
	return t == nullptr ? 0 : t->height;
}

template <typename T>
int Set<T>::Treap::getSize(Set::Treap *treap)
{
	return treap == nullptr ? 0 : treap->size;
}

template <typename T>
typename Set<T>::Treap *Set<T>::Treap::merge(Treap *leftTreap, Treap *rightTreap)
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
typename Set<T>::Treap *Set<T>::Treap::merge(SplitedTreap treap)
{
	return merge(treap.left, treap.right);
}

template <typename T>
typename Set<T>::SplitedTreap Set<T>::Treap::splitByValue(Treap *treap, const T &value)
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
typename Set<T>::SplitedTreap Set<T>::Treap::splitByNumber(Set::Treap *treap, int number)
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
