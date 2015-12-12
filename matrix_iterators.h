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
inline bool matrix<T>::iterator::operator==(const typename matrix<T>::iterator& i) const
{
	return (mem_block == i.mem_block &&
		p == i.p &&
		current_row == i.current_row &&
		current_col == i.current_col);
}

template<typename T>
inline bool matrix<T>::iterator::operator!=(const typename matrix<T>::iterator& i) const
{
	return !operator==(i);
}

template<typename T>
inline typename matrix<T>::iterator& matrix<T>::iterator::operator++()
{
	if (current_row == -1 || current_col == -1)
		return *this;
	++current_col;
	if (current_col > p.c_end)
	{
		current_col = p.c_begin;
		++current_row;
	}
	if (current_row > p.r_end)
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
	if (current_row == p.r_begin && current_col == p.c_begin)
		return *this;
	if (current_row == -1 || current_col == -1)
	{
		current_row = p.r_end;
		current_col = p.c_end;
		return *this;
	}
	--current_col;
	if (current_col < p.c_begin)
	{
		current_col = p.c_end;
		--current_row;
	}
	if (current_row < p.r_begin)
	{
		current_row = p.r_begin;
		current_col = p.c_begin;
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
	return mem_block.get()[current_row * p.cols + current_col];
}

template<typename T>
inline T* matrix<T>::iterator::operator->() const
{
	return &(mem_block.get()[current_row * p.cols + current_col]);
}

template<typename T>
inline bool matrix<T>::const_iterator::operator==(const typename matrix<T>::const_iterator& i) const
{
	return (mem_block == i.mem_block &&
		p == i.p &&
		current_row == i.current_row &&
		current_col == i.current_col);
}

template<typename T>
inline bool matrix<T>::const_iterator::operator!=(const typename matrix<T>::const_iterator& i) const
{
	return !operator==(i);
}

template<typename T>
inline typename matrix<T>::const_iterator& matrix<T>::const_iterator::operator++()
{
	if (current_row == -1 || current_col == -1)
		return *this;
	++current_col;
	if (current_col > p.c_end)
	{
		current_col = p.c_begin;
		++current_row;
	}
	if (current_row > p.r_end)
	{
		current_row = -1;
		current_col = -1;
	}

	return *this;
}

template<typename T>
inline typename matrix<T>::const_iterator matrix<T>::const_iterator::operator++(int)
{
	const_iterator old(*this);
	++(*this);
	return old;
}

template<typename T>
inline typename matrix<T>::const_iterator& matrix<T>::const_iterator::operator--()
{
	if (current_row == p.r_begin && current_col == p.c_begin)
		return *this;
	if (current_row == -1 || current_col == -1)
	{
		current_row = p.r_end;
		current_col = p.c_end;
		return *this;
	}
	--current_col;
	if (current_col < p.c_begin)
	{
		current_col = p.c_end;
		--current_row;
	}
	if (current_row < p.r_begin)
	{
		current_row = p.r_begin;
		current_col = p.c_begin;
	}
	
	return *this;
}

template<typename T>
inline typename matrix<T>::const_iterator matrix<T>::const_iterator::operator--(int)
{
	const_iterator old(*this);
	--(*this);
	return old;
}

template<typename T>
inline const T& matrix<T>::const_iterator::operator*() const
{
	return mem_block.get()[current_row * p.cols + current_col];
}

template<typename T>
inline const T* matrix<T>::const_iterator::operator->() const
{
	return &(mem_block.get()[current_row * p.cols + current_col]);
}

}
