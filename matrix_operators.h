/*
	mn-matrix

	Open source C++ header-only library that provides basic matrix operations.
	Copyright (C) 2015  Marek Nalepa

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "matrix_exception.h"

namespace mn {

template<typename T>
inline bool matrix<T>::operator==(const matrix<T>& m) const
{
	if (rows() != m.rows() || cols() != m.cols())
		return false;
	for (auto i1 = begin(), i2 = m.begin(); i1 != end() && i2 != m.end(); ++i1, ++i2)
	{
		if (*i1 != *i2)
			return false;
	}
	return true;
}

template<typename T>
inline bool matrix<T>::operator!=(const matrix<T>& m) const
{
	return !operator==(m);
}

template<typename T>
inline matrix<T>& matrix<T>::operator+=(const matrix<T>& m)
{
	if (rows() != m.rows() || cols() != m.cols())
		throw matrix_exception("dimensions mismatch");
	auto i1 = begin();
	auto i2 = m.begin();
	while (i1 != end() && i2 != m.end())
		*i1++ += *i2++;
	return *this;
}

template<typename T>
inline matrix<T>& matrix<T>::operator+=(const T& value)
{
	for (auto i = begin(); i != end(); ++i)
		*i += value;
	return *this;
}

template<typename T>
inline matrix<T>& matrix<T>::operator-=(const matrix<T>& m)
{
	if (rows() != m.rows() || cols() != m.cols())
		throw matrix_exception("dimensions mismatch");
	auto i1 = begin();
	auto i2 = m.begin();
	while (i1 != end() && i2 != m.end())
		*i1++ -= *i2++;
	return *this;
}

template<typename T>
inline matrix<T>& matrix<T>::operator-=(const T& value)
{
	for (auto i = begin(); i != end(); ++i)
		*i -= value;
	return *this;
}

template<typename T>
inline matrix<T>& matrix<T>::operator*=(const T& value)
{
	for (auto i = begin(); i != end(); ++i)
		*i *= value;
	return *this;
}

template<typename T>
inline matrix<T>& matrix<T>::operator/=(const T& value)
{
	if (value == 0)
		throw matrix_exception("divide by zero");
	for (auto i = begin(); i != end(); ++i)
		*i /= value;
	return *this;
}

template<typename T>
inline matrix<T> matrix<T>::operator*(const matrix<T>& m)
{
	if (cols() != m.rows())
		throw matrix_exception("dimensions mismatch");
	matrix<T> product(rows(), m.cols());
	for (int row = 0; row < product.rows(); ++row)
	{
		for (int col = 0; col < product.cols(); ++col)
		{
			T sum = 0;
			for (int i = 0; i < cols(); ++i)
				sum += (*this)[row][i] * m[i][col];
			product[row][col] = sum;
		}
	}

	return product;
}

}
