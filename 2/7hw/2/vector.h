#pragma once

#include <stdexcept>

using std::out_of_range;

template <int n>
class Vector
{
public:
	/**
	 * @brief Create vector, in which all coordinates are equal value
	 * @param value
	 */
	Vector(const int value = 0);
	/**
	 * @brief Copies first n elements from input array as coordinates
	 * @param v
	 */
	Vector(const int *v);
	Vector(const Vector<n> &v);

	bool isNull() const noexcept;
	/**
	 * @brief at
	 * @param i
	 * @return Return i-th coordinate, i must be form 0 till n - 1
	 */
	int at(const int i) const throw(out_of_range);
	/**
	 * @brief operator []
	 * @param i
	 * @return Return link to i-th coordinate, i must be form 0 till n - 1
	 */
	int &operator [] (const int i) throw(out_of_range);
	bool operator == (const Vector<n> &v) const noexcept;
	Vector<n> operator - (const Vector<n> &v) const noexcept;
	Vector<n> operator + (const Vector<n> &v) const noexcept;
	/**
	 * @brief operator * Scalar product of two n-dimensional vectors
	 * @param v
	 * @return
	 */
	int operator * (const Vector<n> &v) const noexcept;

private:
	int vector[n];
};

template <int n>
Vector<n>::Vector(const int value)
{
	for (int i = 0; i < n; i++)
		vector[i] = value;
}

template <int n>
Vector<n>::Vector(const int *v)
{
	for (int i = 0; i < n; i++)
		vector[i] = v[i];
}

template <int n>
Vector<n>::Vector(const Vector<n> &v)
{
	for (int i = 0; i < n; i++)
		vector[i] = v.at(i);
}

template <int n>
bool Vector<n>::isNull() const noexcept
{
	bool res = true;
	for (int i = 0; i < n; i++)
		res &= (vector[i] == 0);
	return res;
}

template <int n>
int Vector<n>::at(const int i) const throw(out_of_range)
{
	if (i < 0 || i >= n)
		throw out_of_range("Coordinate with index " +
	                       std::to_string(i) +
	                       " does not exist in vector");
	return vector[i];
}

template <int n>
int &Vector<n>::operator [](const int i) throw(out_of_range)
{
	if (i < 0 || i >= n)
		throw out_of_range("Coordinate with index " +
	                       std::to_string(i) +
	                       " does not exist in vector");
	return vector[i];
}

template <int n>
bool Vector<n>::operator == (const Vector<n> &v) const noexcept
{
	bool res = true;
	for (int i = 0; i < n; i++)
		res &= (this->at(i) == v.at(i));
	return res;
}

template <int n>
Vector<n> Vector<n>::operator - (const Vector<n> &v) const noexcept
{
	int res[n];
	for (int i = 0; i < n; i++)
		res[i] = this->at(i) - v.at(i);
	return Vector<n>(res);
}

template <int n>
Vector<n> Vector<n>::operator + (const Vector<n> &v) const noexcept
{
	int res[n];
	for (int i = 0; i < n; i++)
		res[i] = this->at(i) + v.at(i);
	return Vector<n>(res);
}

template <int n>
int Vector<n>::operator * (const Vector<n> &v) const noexcept
{
	int res = 0;
	for (int i = 0; i < n; i++)
		res += this->at(i) * v.at(i);
	return res;
}
