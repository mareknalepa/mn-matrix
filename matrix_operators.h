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

/**
 * \brief Compares two matrices
 *
 * Returns true if two matrices are equal (are of the same size and contain the same elements).
 *
 * \param m Second matrix to compare
 * \return True if equal
*/
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

/**
 * \brief Compares two matrices if they are not equal
 *
 * Returns true if two matrices are not equal (are of different size or contain different elements).
 *
 * \param m Second matrix to compare
 * \return True if not equal
*/
template<typename T>
inline bool matrix<T>::operator!=(const matrix<T>& m) const
{
	return !operator==(m);
}

/**
 * \brief Adds two matrices
 *
 * Allocates new matrix containing sum of two matrices.
 *
 * \param m Matrix to add to current
 * \return New matrix containing sum
*/
template<typename T>
inline matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
	matrix<T> result = copy();
	result += m;
	return result;
}

/**
 * \brief Adds matrix and value
 *
 * Allocates new matrix containing sum of matrix and value.
 *
 * \param value Value to add to current matrix
 * \return New matrix containing sum
*/
template<typename T>
inline matrix<T> matrix<T>::operator+(const T& value) const
{
	matrix<T> result = copy();
	result += value;
	return result;
}

/**
 * \brief Adds another matrix to current
 *
 * Adds matrix to current without allocating memory.
 *
 * \param m Matrix to add to current
 * \return Reference to modified matrix
 * \throws mn::matrix_exception
*/
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

/**
 * \brief Adds value to current matrix
 *
 * Adds value to every element of current matrix without allocating memory.
 *
 * \param value Value to add to current matrix
 * \return Reference to modified matrix
*/
template<typename T>
inline matrix<T>& matrix<T>::operator+=(const T& value)
{
	for (auto i = begin(); i != end(); ++i)
		*i += value;
	return *this;
}

/**
 * \brief Subtracts two matrices
 *
 * Allocates new matrix containing difference of two matrices.
 *
 * \param m Matrix to subtract from current
 * \return New matrix containing difference
*/
template<typename T>
inline matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{
	matrix<T> result = copy();
	result -= m;
	return result;
}

/**
 * \brief Subtracts value from matrix
 *
 * Allocates new matrix containing difference of current matrix and value.
 *
 * \param value Value to subtract from current matrix
 * \return New matrix containing difference
*/
template<typename T>
inline matrix<T> matrix<T>::operator-(const T& value) const
{
	matrix<T> result = copy();
	result -= value;
	return result;
}

/**
 * \brief Subtracts another matrix from current
 *
 * Subtracts matrix from current without allocating memory.
 *
 * \param m Matrix to subtract from current
 * \return Reference to modified matrix
 * \throws mn::matrix_exception
*/
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

/**
 * \brief Subtracts value from current matrix
 *
 * Subtracts value from every element of current matrix without allocating memory.
 *
 * \param value Value to subtract from current matrix
 * \return Reference to modified matrix
*/
template<typename T>
inline matrix<T>& matrix<T>::operator-=(const T& value)
{
	for (auto i = begin(); i != end(); ++i)
		*i -= value;
	return *this;
}

/**
 * \brief Multiplies two matrices
 *
 * Allocates new matrix containing product of two matrices.
 *
 * \param m Matrix to right-hand-side multiply with current
 * \return New matrix containing product
 * \throws mn::matrix_exception
*/
template<typename T>
inline matrix<T> matrix<T>::operator*(const matrix<T>& m) const
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

/**
 * \brief Multiplies matrix by value
 *
 * Allocates new matrix containing product of matrix and value.
 *
 * \param value Value to multiply current matrix by
 * \return New matrix containing product
*/
template<typename T>
inline matrix<T> matrix<T>::operator*(const T& value) const
{
	matrix<T> result = copy();
	result *= value;
	return result;
}

/**
 * \brief Multiplies current matrix by value
 *
 * Multiplies every element of current matrix by value without allocating memory.
 *
 * \param value Value to multiply current matrix by
 * \return Reference to modified matrix
*/
template<typename T>
inline matrix<T>& matrix<T>::operator*=(const T& value)
{
	for (auto i = begin(); i != end(); ++i)
		*i *= value;
	return *this;
}

/**
 * \brief Divides matrix by value
 *
 * Allocates new matrix containing matrix divided by value.
 *
 * \param value Value to divide current matrix by
 * \return New matrix containing product
*/
template<typename T>
inline matrix<T> matrix<T>::operator/(const T& value) const
{
	matrix<T> result = copy();
	result /= value;
	return result;
}

/**
 * \brief Divides current matrix by value
 *
 * Divides every element of current matrix by value without allocating memory.
 *
 * \param value Value to divide current matrix by
 * \return Reference to modified matrix
 * \throws mn::matrix_exception
*/
template<typename T>
inline matrix<T>& matrix<T>::operator/=(const T& value)
{
	if (value == 0)
		throw matrix_exception("divide by zero");
	for (auto i = begin(); i != end(); ++i)
		*i /= value;
	return *this;
}

/**
 * \brief Calculates matrix determinant
 *
 * Calculates matrix determinant using Laplace expansion (recursive method).
 *
 * \return Matrix determinant
 * \throws mn::matrix_exception
*/
template<typename T>
inline T matrix<T>::det() const
{
	if (!is_square())
		throw matrix_exception("not square matrix");
	if (rows() == 1)
		return (*this)[0][0];
	if (rows() == 2)
		return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

	T determinant = 0;
	matrix<T> submatrix(rows() - 1, cols() - 1);
	for (int col = 0; col < cols(); ++col)
	{
		for (int submatrix_col = 0, matrix_col = 0; matrix_col < cols(); ++matrix_col)
		{
			if (matrix_col != col)
			{
				for (int row = 1; row < rows(); ++row)
					submatrix[row - 1][submatrix_col] = (*this)[row][matrix_col];
				++submatrix_col;
			}
		}
		determinant += (*this)[0][col] * pow(-1.0, 2.0 + col) * submatrix.det();
	}
	return determinant;
}

}
