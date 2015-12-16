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
	class row_iterator;
	class const_row_iterator;
	class col_iterator;
	class const_col_iterator;
	class element_iterator;
	class const_element_iterator;
	class iterator;
	class const_iterator;
protected:
	class properties;
	std::shared_ptr<T> mem_block;
	properties p;
public:
	matrix();
	matrix(int rows, int cols);

	static matrix<T> zeros(int rows, int cols);
	static matrix<T> zeros(int rows_cols);
	static matrix<T> ones(int rows, int cols);
	static matrix<T> ones(int rows_cols);
	static matrix<T> identity(int rows_cols);

	template<typename R>
	static matrix<T> rand(int rows, int cols, R& random_distribution);
	template<typename R>
	static matrix<T> rand(int rows_cols, R& random_distribution);

	const int rows() const;
	const int cols() const;
	bool is_continuous() const;
	bool is_square() const;

	row_iterator operator[](const int index);
	const_row_iterator operator[](const int index) const;
	row_iterator first_row();
	const_row_iterator first_row() const;
	row_iterator last_row();
	const_row_iterator last_row() const;
	col_iterator first_col();
	const_col_iterator first_col() const;
	col_iterator last_col();
	const_col_iterator last_col() const;
	row_iterator row(const int index);
	const_row_iterator row(const int index) const;
	col_iterator col(const int index);
	const_col_iterator col(const int index) const;

	bool operator==(const matrix<T>& m) const;
	bool operator!=(const matrix<T>& m) const;

	matrix<T> operator+(const matrix<T>& m) const;
	matrix<T> operator+(const T& value) const;
	matrix<T>& operator+=(const matrix<T>& m);
	matrix<T>& operator+=(const T& value);

	matrix<T> operator-(const matrix<T>& m) const;
	matrix<T> operator-(const T& value) const;
	matrix<T>& operator-=(const matrix<T>& m);
	matrix<T>& operator-=(const T& value);

	matrix<T> operator*(const matrix<T>& m) const;
	matrix<T> operator*(const T& value) const;
	matrix<T>& operator*=(const T& value);

	matrix<T> operator/(const T& value) const;
	matrix<T>& operator/=(const T& value);

	T det() const;

	matrix<T> submatrix(int rows_from, int rows_to, int cols_from, int cols_to) const;
	matrix<T> transpose() const;
	matrix<T> append_h(matrix<T> m) const;
	matrix<T> append_v(matrix<T> m) const;
	matrix<T> copy() const;
	T* raw();

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	template<typename S>
	friend inline std::istream& operator>>(std::istream& i, matrix<T>& m);
	template<typename S>
	friend inline std::ostream& operator<<(std::ostream& o, const matrix<T>& m);
};

template<typename T>
class matrix<T>::properties
{
public:
	properties() :
		rows(1), cols(1), r_begin(0), r_end(0), c_begin(0), c_end(0), continuous(true) {}
	properties(int rows, int cols) :
		rows(rows), cols(cols), r_begin(0), r_end(rows - 1), c_begin(0), c_end(cols - 1), continuous(true) {}
	bool operator==(const properties& p) const { return rows == p.rows && cols == p.cols && r_begin == p.r_begin && r_end == p.r_end && c_begin == p.c_begin && c_end == p.c_end && continuous == p.continuous; }
	bool operator!=(const properties& p) const { return !operator==(p); }
	int rows;
	int cols;
	int r_begin;
	int r_end;
	int c_begin;
	int c_end;
	bool continuous;
};

template<typename T>
class matrix<T>::row_iterator
{
private:
	const std::shared_ptr<T> mem_block;
	const typename matrix<T>::properties p;
	int r_index;
public:
	row_iterator() : r_index(-1) {}
	row_iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, int row) : mem_block(mem_block), p(p), r_index(row) {}
	bool operator==(const row_iterator& r) const { return mem_block == r.mem_block && p == r.p && r_index == r.r_index; }
	bool operator!=(const row_iterator& r) const { return !operator==(r); }
	row_iterator& operator++();
	row_iterator operator++(int);
	row_iterator& operator--();
	row_iterator operator--(int);
	T& operator[](const int index);
	typename matrix<T>::element_iterator first_element();
	typename matrix<T>::element_iterator last_element();
};

template<typename T>
class matrix<T>::const_row_iterator
{
private:
	const std::shared_ptr<T> mem_block;
	const typename matrix<T>::properties p;
	int r_index;
public:
	const_row_iterator() : r_index(-1) {}
	const_row_iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, int row) : mem_block(mem_block), p(p), r_index(row) {}
	bool operator==(const const_row_iterator& r) const { return mem_block == r.mem_block && p == r.p && r_index == r.r_index; }
	bool operator!=(const const_row_iterator& r) const { return !operator==(r); };
	const_row_iterator& operator++();
	const_row_iterator operator++(int);
	const_row_iterator& operator--();
	const_row_iterator operator--(int);
	const T& operator[](const int index);
	typename matrix<T>::const_element_iterator first_element();
	typename matrix<T>::const_element_iterator last_element();
};

template<typename T>
class matrix<T>::col_iterator
{
private:
	const std::shared_ptr<T> mem_block;
	const typename matrix<T>::properties p;
	int c_index;
public:
	col_iterator() : c_index(-1) {}
	col_iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, int col) : mem_block(mem_block), p(p), c_index(col) {}
	bool operator==(const col_iterator& c) const { return mem_block == c.mem_block && p == c.p && c_index == c.c_index; }
	bool operator!=(const col_iterator& c) const { return !operator==(c); }
	col_iterator& operator++();
	col_iterator operator++(int);
	col_iterator& operator--();
	col_iterator operator--(int);
	typename matrix<T>::element_iterator first_element();
	typename matrix<T>::element_iterator last_element();
};

template<typename T>
class matrix<T>::const_col_iterator
{
private:
	const std::shared_ptr<T> mem_block;
	const typename matrix<T>::properties p;
	int c_index;
public:
	const_col_iterator() : c_index(-1) {}
	const_col_iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, int col) : mem_block(mem_block), p(p), c_index(col) {}
	bool operator==(const const_col_iterator& c) const { return mem_block == c.mem_block && p == c.p && c_index == c.c_index; }
	bool operator!=(const const_col_iterator& c) const { return !operator==(c); };
	const_col_iterator& operator++();
	const_col_iterator operator++(int);
	const_col_iterator& operator--();
	const_col_iterator operator--(int);
	typename matrix<T>::const_element_iterator first_element();
	typename matrix<T>::const_element_iterator last_element();
};

template<typename T>
class matrix<T>::element_iterator
{
private:
	const std::shared_ptr<T> mem_block;
	const typename matrix<T>::properties p;
	bool horizontal;
	int r_index;
	int c_index;
public:
	element_iterator() : horizontal(true), r_index(-1), c_index(-1) {}
	element_iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, bool h, int row, int col) : mem_block(mem_block), p(p), horizontal(h), r_index(row), c_index(col) {}
	bool operator==(const element_iterator& e) const { return mem_block == e.mem_block && p == e.p && horizontal == e.horizontal && r_index == e.r_index && c_index == e.c_index; }
	bool operator!=(const element_iterator& e) const { return !operator==(e); }
	element_iterator& operator++();
	element_iterator operator++(int);
	element_iterator& operator--();
	element_iterator operator--(int);
	T& operator*() const;
	T* operator->() const;
};

template<typename T>
class matrix<T>::const_element_iterator
{
private:
	const std::shared_ptr<T> mem_block;
	const typename matrix<T>::properties p;
	bool horizontal;
	int r_index;
	int c_index;
public:
	const_element_iterator() : horizontal(true), r_index(-1), c_index(-1) {}
	const_element_iterator(std::shared_ptr<T> mem_block, typename matrix<T>::properties p, bool h, int row, int col) : mem_block(mem_block), p(p), horizontal(h), r_index(row), c_index(col) {}
	bool operator==(const const_element_iterator& e) const { return mem_block == e.mem_block && p == e.p && horizontal == e.horizontal && r_index == e.r_index && c_index == e.c_index; }
	bool operator!=(const const_element_iterator& e) const { return !operator==(e); }
	const_element_iterator& operator++();
	const_element_iterator operator++(int);
	const_element_iterator& operator--();
	const_element_iterator operator--(int);
	const T& operator*() const;
	const T* operator->() const;
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
inline matrix<T>::matrix(int rows, int cols) :
	mem_block(new T[rows * cols], [](T* ptr) { delete[] ptr; }), p(rows, cols)
{
}

template<typename T>
inline const int matrix<T>::rows() const
{
	return p.r_end - p.r_begin + 1;
}

template<typename T>
inline const int matrix<T>::cols() const
{
	return p.c_end - p.c_begin + 1;
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
inline typename matrix<T>::row_iterator matrix<T>::operator[](const int index)
{
	return row(index);
}

template<typename T>
inline typename matrix<T>::const_row_iterator matrix<T>::operator[](const int index) const
{
	return row(index);
}

template<typename T>
inline typename matrix<T>::row_iterator matrix<T>::first_row()
{
	return row_iterator(mem_block, p, p.r_begin);
}


template<typename T>
inline typename matrix<T>::const_row_iterator matrix<T>::first_row() const
{
	return const_row_iterator(mem_block, p, p.r_begin);
}

template<typename T>
inline typename matrix<T>::row_iterator matrix<T>::last_row()
{
	return row_iterator(mem_block, p, p.r_end + 1);
}

template<typename T>
inline typename matrix<T>::const_row_iterator matrix<T>::last_row() const
{
	return const_row_iterator(mem_block, p, p.r_end + 1);
}

template<typename T>
inline typename matrix<T>::col_iterator matrix<T>::first_col()
{
	return col_iterator(mem_block, p, p.c_begin);
}

template<typename T>
inline typename matrix<T>::const_col_iterator matrix<T>::first_col() const
{
	return const_col_iterator(mem_block, p, p.c_begin);
}

template<typename T>
inline typename matrix<T>::col_iterator matrix<T>::last_col()
{
	return col_iterator(mem_block, p, p.c_end + 1);
}

template<typename T>
inline typename matrix<T>::const_col_iterator matrix<T>::last_col() const
{
	return const_col_iterator(mem_block, p, p.c_end + 1);
}

template<typename T>
inline typename matrix<T>::row_iterator matrix<T>::row(const int index)
{
	return row_iterator(mem_block, p, p.r_begin + index);
}

template<typename T>
inline typename matrix<T>::const_row_iterator matrix<T>::row(const int index) const
{
	return const_row_iterator(mem_block, p, p.r_begin + index);
}

template<typename T>
inline typename matrix<T>::col_iterator matrix<T>::col(const int index)
{
	return col_iterator(mem_block, p, p.c_begin + index);
}

template<typename T>
inline typename matrix<T>::const_col_iterator matrix<T>::col(const int index) const
{
	return const_col_iterator(mem_block, p, p.c_begin + index);
}

template<typename T>
inline matrix<T> matrix<T>::submatrix(int rows_from, int rows_to, int cols_from, int cols_to) const
{
	matrix<T> subm = matrix(*this);
	if (rows_from < 0 || rows_to >= p.rows || cols_from < 0 || cols_to >= p.cols)
		throw matrix_exception("region out of bounds");
	if (rows_from > rows_to || cols_from > cols_to)
		throw matrix_exception("invalid region");
	subm.p.continuous = false;
	subm.p.r_begin = rows_from;
	subm.p.r_end = rows_to;
	subm.p.c_begin = cols_from;
	subm.p.c_end = cols_to;

	return subm;
}

template<typename T>
inline matrix<T> matrix<T>::transpose() const
{
	matrix<T> transposed = matrix<T>(cols(), rows());
	auto src_row = first_row();
	auto dst_col = transposed.first_col();
	while (src_row != last_row() && dst_col != transposed.last_col())
	{
		auto src_element = src_row.first_element();
		auto dst_element = dst_col.first_element();
		while (src_element != src_row.last_element() && dst_element != dst_col.last_element())
		{
			*dst_element = *src_element;
			++src_element;
			++dst_element;
		}
		++src_row;
		++dst_col;
	}

	return transposed;
}

template<typename T>
inline matrix<T> matrix<T>::append_h(matrix<T> m) const
{
	int rows_n = (rows() > m.rows()) ? rows() : m.rows();
	matrix<T> appended(rows_n, cols() + m.cols());
	for (int r = 0; r < rows(); ++r)
	{
		for (int c = 0; c < cols(); ++c)
		{
			appended[r][c] = (*this)[r][c];
		}
	}
	for (int r = 0; r < m.rows(); ++r)
	{
		for (int c = 0; c < m.cols(); ++c)
		{
			appended[r][c + cols()] = m[r][c];
		}
	}
	if (rows() > m.rows())
	{
		for (int r = m.rows(); r < appended.rows(); ++r)
		{
			for (int c = cols(); c < appended.cols(); ++c)
			{
				appended[r][c] = 0;
			}
		}
	}
	else
	{
		for (int r = rows(); r < appended.rows(); ++r)
		{
			for (int c = 0; c < cols(); ++c)
			{
				appended[r][c] = 0;
			}
		}
	}

	return appended;
}

template<typename T>
inline matrix<T> matrix<T>::append_v(matrix<T> m) const
{
	int cols_n = (cols() > m.cols()) ? cols() : m.cols();
	matrix<T> appended(rows() + m.rows(), cols_n);
	for (int r = 0; r < rows(); ++r)
	{
		for (int c = 0; c < cols(); ++c)
		{
			appended[r][c] = (*this)[r][c];
		}
	}
	for (int r = 0; r < m.rows(); ++r)
	{
		for (int c = 0; c < m.cols(); ++c)
		{
			appended[r + rows()][c] = m[r][c];
		}
	}
	if (cols() > m.cols())
	{
		for (int r = rows(); r < appended.rows(); ++r)
		{
			for (int c = m.cols(); c < appended.cols(); ++c)
			{
				appended[r][c] = 0;
			}
		}
	}
	else
	{
		for (int r = 0; r < rows(); ++r)
		{
			for (int c = cols(); c < appended.cols(); ++c)
			{
				appended[r][c] = 0;
			}
		}
	}

	return appended;
}

template<typename T>
inline matrix<T> matrix<T>::copy() const
{
	matrix<T> copy = matrix<T>(rows(), cols());
	auto src = begin();
	auto dst = copy.begin();
	for (; src != end() && dst != copy.end(); ++src, ++dst)
	{
		*dst = *src;
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

#include "matrix_generators.h"
#include "matrix_operators.h"
#include "matrix_iterators.h"
#include "matrix_io.h"
