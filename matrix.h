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

#include <memory>

#include "matrix_exception.h"

namespace mn {

template<typename T>
class matrix
{
public:
	class iterator;
	class const_iterator;
protected:
	class properties;
	class row_proxy;
	std::shared_ptr<T> mem_block;
	properties p;
public:
	matrix();
	matrix(const matrix& m);
	matrix(int rows, int cols);
	matrix& operator=(const matrix& m);

	const int rows() const;
	const int cols() const;
	bool is_continuous() const;
	bool is_square() const;

	row_proxy operator[](const int index);
	const row_proxy operator[] (const int index) const;

	bool operator==(const matrix<T>& m) const;
	bool operator!=(const matrix<T>& m) const;
	matrix<T>& operator+=(const matrix<T>& m);
	matrix<T>& operator+=(const T& value);
	matrix<T>& operator-=(const matrix<T>& m);
	matrix<T>& operator-=(const T& value);
	matrix<T>& operator*=(const T& value);
	matrix<T>& operator/=(const T& value);
	matrix<T> operator*(const matrix<T>& m);
	T det() const;

	matrix<T> submatrix(int rows_from, int rows_to, int cols_from, int cols_to) const;
	matrix<T> transpose() const;
	matrix<T> copy() const;
	T* raw();

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
};

template<typename T>
class matrix<T>::properties
{
public:
	properties() :
		rows(1), cols(1), r_begin(0), r_end(0), c_begin(0), c_end(0), continuous(true), transposed(false) {}
	properties(int rows, int cols) :
		rows(rows), cols(cols), r_begin(0), r_end(rows - 1), c_begin(0), c_end(cols - 1), continuous(true), transposed(false) {}
	bool operator==(const properties& p) const { return rows == p.rows && cols == p.cols && r_begin == p.r_begin && r_end == p.r_end && c_begin == p.c_begin && c_end == p.c_end && continuous == p.continuous && transposed == p.transposed; }
	bool operator!=(const properties& p) const { return !operator==(p); }
	int rows;
	int cols;
	int r_begin;
	int r_end;
	int c_begin;
	int c_end;
	bool continuous;
	bool transposed;
};

template<typename T>
class matrix<T>::row_proxy
{
private:
	const std::shared_ptr<T>& mem_block;
	const typename matrix<T>::properties& p;
	const int row;
public:
	row_proxy(const std::shared_ptr<T>& mem_block, const typename matrix<T>::properties& p, const int row) : mem_block(mem_block), p(p), row(row) {}
	T& operator[](const int index);
	const T& operator[] (const int index) const;
};

template<typename T>
class matrix<T>::iterator
{
protected:
	std::shared_ptr<T> mem_block;
	typename matrix<T>::properties p;
	int current_row;
	int current_col;
public:
	iterator() :
		mem_block(std::nullptr_t(0)), current_row(-1), current_col(-1) {}
	iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, int row, int col) :
		mem_block(mem_block), p(p), current_row(row), current_col(col) {}
	iterator(const iterator& i) :
		mem_block(i.mem_block), p(i.p), current_row(i.current_row), current_col(i.current_col) {}
	iterator& operator=(const iterator& i);
	bool operator==(const iterator& i) const;
	bool operator!=(const iterator& i) const;
	iterator& operator++();
	iterator operator++(int);
	iterator& operator--();
	iterator operator--(int);
	T& operator*() const;
	T* operator->() const;
};

template<typename T>
class matrix<T>::const_iterator
{
protected:
	std::shared_ptr<T> mem_block;
	typename matrix<T>::properties p;
	int current_row;
	int current_col;
public:
	const_iterator() :
		mem_block(std::nullptr_t(0)), current_row(-1), current_col(-1) {}
	const_iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, int row, int col) :
		mem_block(mem_block), p(p), current_row(row), current_col(col) {}
	const_iterator(const const_iterator& i) :
		mem_block(i.mem_block), p(i.p), current_row(i.current_row), current_col(i.current_col) {}
	const_iterator(const typename matrix<T>::iterator& i):
		mem_block(i.mem_block), p(i.p), current_row(i.current_row), current_col(i.current_col) {}
	const_iterator& operator=(const const_iterator& i);
	bool operator==(const const_iterator& i) const;
	bool operator!=(const const_iterator& i) const;
	const_iterator& operator++();
	const_iterator operator++(int);
	const_iterator& operator--();
	const_iterator operator--(int);
	const T& operator*() const;
	const T* operator->() const;
};

template<typename T>
inline matrix<T>::matrix() :
	mem_block(new T[1], [](T* ptr) { delete[] ptr; })
{
}

template<typename T>
inline matrix<T>::matrix(const matrix& m) :
	mem_block(m.mem_block), p(m.p)
{
}

template<typename T>
inline matrix<T>::matrix(int rows, int cols) :
	mem_block(new T[rows * cols], [](T* ptr) { delete[] ptr; }), p(rows, cols)
{
}

template<typename T>
inline matrix<T>& matrix<T>::operator=(const matrix& m)
{
	if (&m != this)
	{
		mem_block = m.mem_block;
		p = m.p;
	}
	return *this;
}

template<typename T>
inline const int matrix<T>::rows() const
{
	if (!p.transposed)
		if (p.continuous)
			return p.rows;
		else
			return p.r_end - p.r_begin + 1;
	else
		if (p.continuous)
			return p.cols;
		else
			return p.c_end - p.c_begin + 1;
}

template<typename T>
inline const int matrix<T>::cols() const
{
	if (!p.transposed)
		if (p.continuous)
			return p.cols;
		else
			return p.c_end - p.c_begin + 1;
	else
		if (p.continuous)
			return p.rows;
		else
			return p.r_end - p.r_begin + 1;
}

template<typename T>
inline bool matrix<T>::is_continuous() const
{
	return p.continuous;
}

template<typename T>
inline bool matrix<T>::is_square() const
{
	return rows() == cols();
}

template<typename T>
inline T& matrix<T>::row_proxy::operator[](const int index)
{
	if (p.transposed)
		return mem_block.get()[p.cols * (index + p.r_begin) + p.c_begin + row];
	return mem_block.get()[p.cols * (row + p.r_begin) + p.c_begin + index];
}

template<typename T>
inline const T& matrix<T>::row_proxy::operator[](const int index) const
{
	if (p.transposed)
		return mem_block.get()[p.cols * (index + p.r_begin) + p.c_begin + row];
	return mem_block.get()[p.cols * (row + p.r_begin) + p.c_begin + index];
}

template<typename T>
inline typename matrix<T>::row_proxy matrix<T>::operator[](const int index)
{
	return row_proxy(mem_block, p, index);
}

template<typename T>
inline typename const matrix<T>::row_proxy matrix<T>::operator[](const int index) const
{
	return row_proxy(mem_block, p, index);
}

template<typename T>
inline matrix<T> matrix<T>::submatrix(int rows_from, int rows_to, int cols_from, int cols_to) const
{
	matrix<T> subm = matrix(*this);
	if (!p.transposed)
	{
		if (rows_from < 0 || rows_to >= p.rows || cols_from < 0 || cols_to >= p.cols)
			throw matrix_exception("region out of bounds");
		if (rows_from > rows_to || cols_from > cols_to)
			throw matrix_exception("invalid region");
		subm.p.continuous = false;
		subm.p.r_begin = rows_from;
		subm.p.r_end = rows_to;
		subm.p.c_begin = cols_from;
		subm.p.c_end = cols_to;
	}
	else
	{
		if (rows_from < 0 || rows_to >= p.cols || cols_from < 0 || cols_to >= p.rows)
			throw matrix_exception("region out of bounds");
		if (rows_from > rows_to || cols_from > cols_to)
			throw matrix_exception("invalid region");
		subm.p.continuous = false;
		subm.p.c_begin = rows_from;
		subm.p.c_end = rows_to;
		subm.p.r_begin = cols_from;
		subm.p.r_end = cols_to;
	}
	
	return subm;
}

template<typename T>
inline matrix<T> matrix<T>::transpose() const
{
	matrix<T> transposed = matrix(*this);
	transposed.p.transposed = !p.transposed;

	return transposed;
}

template<typename T>
inline matrix<T> matrix<T>::copy() const
{
	matrix<T> copy = matrix<T>(rows(), cols());
	if (p.continuous && !p.transposed)
		std::memcpy(mem_block.get(), copy.mem_block.get(), p.rows * p.cols * sizeof(T));
	else
	{
		int row = 0;
		int col = 0;
		for (auto i = begin(); i != end(); ++i)
		{
			copy[row][col] = *i;
			++col;
			if (col == cols())
			{
				col = 0;
				++row;
			}
		}
	}

	return copy;
}

template<typename T>
inline T* matrix<T>::raw()
{
	return mem_block.get();
}

template<typename T>
inline typename matrix<T>::iterator matrix<T>::begin()
{
	return iterator(mem_block, p, p.r_begin, p.c_begin);
}

template<typename T>
inline typename matrix<T>::const_iterator matrix<T>::begin() const
{
	return const_iterator(mem_block, p, p.r_begin, p.c_begin);
}

template <typename T>
inline typename matrix<T>::iterator matrix<T>::end()
{
	return iterator(mem_block, p, -1, -1);
}

template <typename T>
inline typename matrix<T>::const_iterator matrix<T>::end() const
{
	return const_iterator(mem_block, p, -1, -1);
}

}

#include "matrix_operators.h"
#include "matrix_iterators.h"
