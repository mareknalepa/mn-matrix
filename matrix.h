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
protected:
	class row_proxy;
	const int n_rows;
	const int n_cols;
	bool continuous;
	int rows_begin;
	int rows_end;
	int cols_begin;
	int cols_end;
	std::shared_ptr<T> mem_block;
public:
	matrix();
	matrix(const matrix& m);
	matrix(int rows, int cols);
	~matrix();
	void init();
	const int rows() const;
	const int cols() const;
	row_proxy operator[](const int index);
	const row_proxy operator[] (const int index) const;
	matrix<T>& region(int rows_from, int rows_to, int cols_from, int cols_to);
	matrix<T>& whole();
	T* raw();
};

template<typename T>
class matrix<T>::row_proxy
{
private:
	std::shared_ptr<T> mem_block;
	const int offset;
public:
	row_proxy(std::shared_ptr<T> mem_block, const int offset) : mem_block(mem_block), offset(offset) {}
	T& operator[](const int index);
	const T& operator[] (const int index) const;
};

template<typename T>
inline matrix<T>::matrix() : rows(1), cols(1), mem_block(new T[1], [](T* ptr) { delete[] ptr; })
{
	init();
}

template<typename T>
inline matrix<T>::matrix(const matrix& m) : n_rows(m.n_rows), n_cols(m.n_cols), mem_block(new T[n_rows * n_cols], [](T* ptr) { delete[] ptr; })
{
	init();
	std::memcpy(mem_block.get(), m.mem_block.get(), n_rows * n_cols * sizeof(T));
}

template<typename T>
inline matrix<T>::matrix(int rows, int cols) : n_rows(rows), n_cols(cols), mem_block(new T[n_rows * n_cols], [](T* ptr) { delete[] ptr; })
{
	init();
}

template<typename T>
inline matrix<T>::~matrix()
{
}

template<typename T>
inline void matrix<T>::init()
{
	continuous = true;
	rows_begin = 0;
	rows_end = n_rows - 1;
	cols_begin = 0;
	cols_end = n_cols - 1;
}

template<typename T>
inline const int matrix<T>::rows() const
{
	if (continuous)
		return n_rows;
	else
		return rows_end - rows_begin + 1;
}

template<typename T>
inline const int matrix<T>::cols() const
{
	if (continuous)
		return n_cols;
	else
		return cols_end - cols_begin + 1;
}

template<typename T>
inline T& matrix<T>::row_proxy::operator[](const int index)
{
	return mem_block.get()[offset + index];
}

template<typename T>
inline const T& matrix<T>::row_proxy::operator[](const int index) const
{
	return mem_block.get()[offset + index];
}

template<typename T>
inline typename matrix<T>::row_proxy matrix<T>::operator[](const int index)
{
	return row_proxy(mem_block, n_cols * (index + rows_begin) + cols_begin);
}

template<typename T>
inline typename const matrix<T>::row_proxy matrix<T>::operator[](const int index) const
{
	return row_proxy(mem_block, n_cols * (index + rows_begin) + cols_begin);
}

template<typename T>
inline matrix<T>& matrix<T>::region(int rows_from, int rows_to, int cols_from, int cols_to)
{
	if (rows_from < 0 || rows_to >= n_rows || cols_from < 0 || cols_to >= n_cols)
	{
		throw matrix_exception("region out of bounds");
	}
	if (rows_from > rows_to || cols_from > cols_to)
	{
		throw matrix_exception("invalid region");
	}

	continuous = false;
	rows_begin = rows_from;
	rows_end = rows_to;
	cols_begin = cols_from;
	cols_end = cols_to;

	return *this;
}

template<typename T>
inline matrix<T>& matrix<T>::whole()
{
	init();
	return *this;
}

template<typename T>
inline T* matrix<T>::raw()
{
	return mem_block.get();
}

}
