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

namespace mn {

template<typename T>
class matrix {
protected:
	const int n_rows;
	const int n_cols;
	T* mem_block;
public:
	class matrix_row_proxy {
	private:
		T* mem_block;
	public:
		matrix_row_proxy(T* mem_block) : mem_block(mem_block) {}
		T& operator[](const int index);
		const T& operator[] (const int index) const;
	};

	matrix();
	matrix(const matrix& m);
	matrix(int rows, int cols);
	~matrix();
	const int rows() const;
	const int cols() const;
	matrix_row_proxy operator[](const int index);
	const matrix_row_proxy operator[] (const int index) const;
	T* raw();
};

template<typename T>
inline matrix<T>::matrix(): rows(1), cols(1)
{
	mem_block = new T[1];
}

template<typename T>
inline matrix<T>::matrix(const matrix& m): n_rows(m.n_rows), n_cols(m.n_cols)
{
	mem_block = new T[n_rows * n_cols];
	std::memcpy(mem_block, m.mem_block, n_rows * n_cols * sizeof(T));
}

template<typename T>
inline matrix<T>::matrix(int rows, int cols): n_rows(rows), n_cols(cols)
{
	mem_block = new T[n_rows * n_cols];
}

template<typename T>
inline matrix<T>::~matrix()
{
	delete[] mem_block;
}

template<typename T>
inline const int matrix<T>::rows() const
{
	return n_rows;
}

template<typename T>
inline const int matrix<T>::cols() const
{
	return n_cols;
}

template<typename T>
inline T& matrix<T>::matrix_row_proxy::operator[](const int index)
{
	return mem_block[index];
}

template<typename T>
inline const T& matrix<T>::matrix_row_proxy::operator[](const int index) const
{
	return mem_block[index];
}

template<typename T>
inline typename matrix<T>::matrix_row_proxy matrix<T>::operator[](const int index)
{
	return matrix_row_proxy(&mem_block[index * n_cols]);
}

template<typename T>
inline typename const matrix<T>::matrix_row_proxy matrix<T>::operator[](const int index) const
{
	return matrix_row_proxy(&mem_block[index * n_cols]);
}

template<typename T>
inline T* matrix<T>::raw()
{
	return mem_block;
}

}
