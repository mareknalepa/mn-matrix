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

namespace mn {

template<typename T>
inline typename matrix<T>::iterator& matrix<T>::iterator::operator=(const typename matrix<T>::iterator& i)
{
	if (&i != this)
	{
		mem_block = i.mem_block;
		n_rows = i.n_rows;
		n_cols = i.n_cols;
		reg = i.reg;
		current_row = i.current_row;
		current_col = i.current_col;
	}
	return *this;
}

template<typename T>
inline bool matrix<T>::iterator::operator==(const typename matrix<T>::iterator& i) const
{
	return (mem_block == i.mem_block &&
		n_rows == i.n_rows &&
		n_cols == i.n_cols &&
		reg == i.reg &&
		current_row == i.current_row &&
		current_col == i.current_col);
}

template<typename T>
inline bool matrix<T>::iterator::operator!=(const typename matrix<T>::iterator& i) const
{
	return !(mem_block == i.mem_block &&
		n_rows == i.n_rows &&
		n_cols == i.n_cols &&
		reg == i.reg &&
		current_row == i.current_row &&
		current_col == i.current_col);
}

template<typename T>
inline typename matrix<T>::iterator& matrix<T>::iterator::operator++()
{
	if (current_row == -1 || current_col == -1)
		return *this;
	++current_col;
	if (current_col > reg.cols_end)
	{
		current_col = reg.cols_begin;
		++current_row;
	}
	if (current_row > reg.rows_end)
	{
		current_row = -1;
		current_col = -1;
	}
	return *this;
}

template<typename T>
inline typename matrix<T>::iterator matrix<T>::iterator::operator++(int)
{
	iterator old(*this);
	++(*this);
	return old;
}

template<typename T>
inline typename matrix<T>::iterator& matrix<T>::iterator::operator--()
{
	if (current_row == reg.rows_begin && current_col == reg.cols_begin)
		return *this;
	if (current_row == -1 || current_col == -1)
	{
		current_row = reg.rows_end;
		current_col = reg.cols_end;
		return *this;
	}
	--current_col;
	if (current_col < reg.cols_begin)
	{
		current_col = reg.cols_end;
		--current_row;
	}
	if (current_row < reg.rows_begin)
	{
		current_row = reg.rows_begin;
		current_col = reg.cols_begin;
	}
	return *this;
}

template<typename T>
inline typename matrix<T>::iterator matrix<T>::iterator::operator--(int)
{
	iterator old(*this);
	--(*this);
	return old;
}

template<typename T>
inline T& matrix<T>::iterator::operator*() const
{
	return mem_block.get()[current_row * n_cols + current_col];
}

template<typename T>
inline T* matrix<T>::iterator::operator->() const
{
	return &(mem_block.get()[current_row * n_cols + current_col]);
}

template<typename T>
inline typename matrix<T>::const_iterator& matrix<T>::const_iterator::operator=(const typename matrix<T>::const_iterator& i)
{
	if (&i != this)
	{
		mem_block = i.mem_block;
		n_rows = i.n_rows;
		n_cols = i.n_cols;
		reg = i.reg;
		current_row = i.current_row;
		current_col = i.current_col;
	}
	return *this;
}

template<typename T>
inline bool matrix<T>::const_iterator::operator==(const typename matrix<T>::const_iterator& i) const
{
	return (mem_block == i.mem_block &&
		n_rows == i.n_rows &&
		n_cols == i.n_cols &&
		reg == i.reg &&
		current_row == i.current_row &&
		current_col == i.current_col);
}

template<typename T>
inline bool matrix<T>::const_iterator::operator!=(const typename matrix<T>::const_iterator& i) const
{
	return !(mem_block == i.mem_block &&
		n_rows == i.n_rows &&
		n_cols == i.n_cols &&
		reg == i.reg &&
		current_row == i.current_row &&
		current_col == i.current_col);
}

template<typename T>
inline typename matrix<T>::const_iterator& matrix<T>::const_iterator::operator++()
{
	if (current_row == -1 || current_col == -1)
		return *this;
	++current_col;
	if (current_col > reg.cols_end)
	{
		current_col = reg.cols_begin;
		++current_row;
	}
	if (current_row > reg.rows_end)
	{
		current_row = -1;
		current_col = -1;
	}
	return *this;
}

template<typename T>
inline typename matrix<T>::const_iterator matrix<T>::const_iterator::operator++(int)
{
	iterator old(*this);
	++(*this);
	return old;
}

template<typename T>
inline typename matrix<T>::const_iterator& matrix<T>::const_iterator::operator--()
{
	if (current_row == reg.rows_begin && current_col == reg.cols_begin)
		return *this;
	if (current_row == -1 || current_col == -1)
	{
		current_row = reg.rows_end;
		current_col = reg.cols_end;
		return *this;
	}
	--current_col;
	if (current_col < reg.cols_begin)
	{
		current_col = reg.cols_end;
		--current_row;
	}
	if (current_row < reg.rows_begin)
	{
		current_row = reg.rows_begin;
		current_col = reg.cols_begin;
	}
	return *this;
}

template<typename T>
inline typename matrix<T>::const_iterator matrix<T>::const_iterator::operator--(int)
{
	iterator old(*this);
	--(*this);
	return old;
}

template<typename T>
inline const T& matrix<T>::const_iterator::operator*() const
{
	return mem_block.get()[current_row * n_cols + current_col];
}

template<typename T>
inline const T* matrix<T>::const_iterator::operator->() const
{
	return &(mem_block.get()[current_row * n_cols + current_col]);
}

}
