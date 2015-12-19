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

/**
 * \brief Moves iterator to next row (prefix incrementation)
*/
template<typename T>
inline typename matrix<T>::row_iterator& matrix<T>::row_iterator::operator++()
{
	if (r_index < p.r_end + 1)
		++r_index;
	return *this;
}

/**
 * \brief Moves iterator to next row (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::row_iterator matrix<T>::row_iterator::operator++(int)
{
	row_iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves iterator to previous row (prefix decrementation)
*/
template<typename T>
inline typename matrix<T>::row_iterator& matrix<T>::row_iterator::operator--()
{
	if (r_index > p.r_begin)
		--r_index;
	return *this;
}

/**
 * \brief Moves iterator to previous row (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::row_iterator matrix<T>::row_iterator::operator--(int)
{
	row_iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns reference to row element at specified index
*/
template<typename T>
inline T& matrix<T>::row_iterator::operator[](const int index)
{
	return mem_block.get()[p.cols * r_index + p.c_begin + index];
}

/**
 * \brief Returns row element iterator initialized with first element
*/
template<typename T>
inline typename matrix<T>::element_iterator matrix<T>::row_iterator::first_element()
{
	return matrix<T>::element_iterator(mem_block, p, true, r_index, p.c_begin);
}

/**
 * \brief Returns row element iterator for next element after the last in row
*/
template<typename T>
inline typename matrix<T>::element_iterator matrix<T>::row_iterator::last_element()
{
	return matrix<T>::element_iterator(mem_block, p, true, r_index, p.c_end + 1);
}

/**
 * \brief Moves constant matrix iterator to next row (prefix incrementation)
*/
template<typename T>
inline typename matrix<T>::const_row_iterator& matrix<T>::const_row_iterator::operator++()
{
	if (r_index < p.r_end + 1)
		++r_index;
	return *this;
}

/**
 * \brief Moves constant matrix iterator to next row (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::const_row_iterator matrix<T>::const_row_iterator::operator++(int)
{
	const_row_iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves constant matrix iterator to previous row (prefix decrementation)
*/
template<typename T>
inline typename matrix<T>::const_row_iterator& matrix<T>::const_row_iterator::operator--()
{
	if (r_index > p.r_begin)
		--r_index;
	return *this;
}

/**
 * \brief Moves constant matrix iterator to previous row (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::const_row_iterator matrix<T>::const_row_iterator::operator--(int)
{
	const_row_iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns row element of constant matrix at specified index
*/
template<typename T>
inline const T& matrix<T>::const_row_iterator::operator[](const int index)
{
	return mem_block.get()[p.cols * r_index + p.c_begin + index];
}

/**
 * \brief Returns row element iterator of constant matrix initialized with first element
*/
template<typename T>
inline typename matrix<T>::const_element_iterator matrix<T>::const_row_iterator::first_element()
{
	return matrix<T>::const_element_iterator(mem_block, p, true, r_index, p.c_begin);
}

/**
 * \brief Returns row element iterator of constant matrix for next element after the last in row
*/
template<typename T>
inline typename matrix<T>::const_element_iterator matrix<T>::const_row_iterator::last_element()
{
	return matrix<T>::const_element_iterator(mem_block, p, true, r_index, p.c_end + 1);
}

/**
 * \brief Moves iterator to next column (prefix incrementation)
*/
template<typename T>
inline typename matrix<T>::col_iterator& matrix<T>::col_iterator::operator++()
{
	if (c_index < p.c_end + 1)
		++c_index;
	return *this;
}

/**
 * \brief Moves iterator to next column (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::col_iterator matrix<T>::col_iterator::operator++(int)
{
	col_iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves iterator to previous column (prefix decrementation)
*/
template<typename T>
inline typename matrix<T>::col_iterator& matrix<T>::col_iterator::operator--()
{
	if (c_index > p.c_begin)
		--c_index;
	return *this;
}

/**
 * \brief Moves iterator to previous column (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::col_iterator matrix<T>::col_iterator::operator--(int)
{
	col_iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns column element iterator initialized with first element
*/
template<typename T>
inline typename matrix<T>::element_iterator matrix<T>::col_iterator::first_element()
{
	return matrix<T>::element_iterator(mem_block, p, false, p.r_begin, c_index);
}

/**
 * \brief Returns column element iterator for next element after the last in column
*/
template<typename T>
inline typename matrix<T>::element_iterator matrix<T>::col_iterator::last_element()
{
	return matrix<T>::element_iterator(mem_block, p, false, p.r_end + 1, c_index);
}

/**
 * \brief Moves constant matrix iterator to next column (prefix incrementation)
*/
template<typename T>
inline typename matrix<T>::const_col_iterator& matrix<T>::const_col_iterator::operator++()
{
	if (c_index < p.c_end + 1)
		++c_index;
	return *this;
}

/**
 * \brief Moves constant matrix iterator to next column (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::const_col_iterator matrix<T>::const_col_iterator::operator++(int)
{
	const_col_iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves constant matrix iterator to previous column (prefix decrementation)
*/
template<typename T>
inline typename matrix<T>::const_col_iterator& matrix<T>::const_col_iterator::operator--()
{
	if (c_index > p.c_begin)
		--c_index;
	return *this;
}

/**
 * \brief Moves constant matrix iterator to previous column (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::const_col_iterator matrix<T>::const_col_iterator::operator--(int)
{
	const_col_iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns column element iterator of constant matrix initialized with first element
*/
template<typename T>
inline typename matrix<T>::const_element_iterator matrix<T>::const_col_iterator::first_element()
{
	return matrix<T>::const_element_iterator(mem_block, p, false, p.r_begin, c_index);
}

/**
 * \brief Returns column element iterator of constant matrix for next element after the last in column
*/
template<typename T>
inline typename matrix<T>::const_element_iterator matrix<T>::const_col_iterator::last_element()
{
	return matrix<T>::const_element_iterator(mem_block, p, false, p.r_end + 1, c_index);
}

/**
 * \brief Moves iterator to next element in row or column (prefix incrementation)
*/
template<typename T>
inline typename matrix<T>::element_iterator& matrix<T>::element_iterator::operator++()
{
	if (horizontal)
	{
		if (c_index < p.c_end + 1)
			++c_index;
	}
	else
	{
		if (r_index < p.r_end + 1)
			++r_index;
	}
	return *this;
}

/**
 * \brief Moves iterator to next element in row or column (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::element_iterator matrix<T>::element_iterator::operator++(int)
{
	element_iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves iterator to previous element in row or column (prefix decrementation)
*/
template<typename T>
inline typename matrix<T>::element_iterator& matrix<T>::element_iterator::operator--()
{
	if (horizontal)
	{
		if (c_index > p.c_begin)
			--c_index;
	}
	else
	{
		if (r_index > p.r_begin)
			--r_index;
	}
	return *this;
}

/**
 * \brief Moves iterator to previous element in row or column (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::element_iterator matrix<T>::element_iterator::operator--(int)
{
	element_iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns reference to element of row or column associated with iterator
*/
template<typename T>
inline T& matrix<T>::element_iterator::operator*() const
{
	return mem_block.get()[p.cols * r_index + c_index];
}

/**
 * \brief Returns pointer to element of row or column associated with iterator
*/
template<typename T>
inline T* matrix<T>::element_iterator::operator->() const
{
	return &(mem_block.get()[p.cols * r_index + c_index]);
}

/**
 * \brief Moves constant matrix iterator to next element in row or column (prefix incrementation)
*/
template<typename T>
inline typename matrix<T>::const_element_iterator& matrix<T>::const_element_iterator::operator++()
{
	if (horizontal)
	{
		if (c_index < p.c_end + 1)
			++c_index;
	}
	else
	{
		if (r_index < p.r_end + 1)
			++r_index;
	}
	return *this;
}

/**
 * \brief Moves constant matrix iterator to next element in row or column (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::const_element_iterator matrix<T>::const_element_iterator::operator++(int)
{
	element_iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves constant matrix iterator to previous element in row or column (prefix decrementation)
*/
template<typename T>
inline typename matrix<T>::const_element_iterator& matrix<T>::const_element_iterator::operator--()
{
	if (horizontal)
	{
		if (c_index > p.c_begin)
			--c_index;
	}
	else
	{
		if (r_index > p.r_begin)
			--r_index;
	}
	return *this;
}

/**
 * \brief Moves constant matrix iterator to previous element in row or column (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::const_element_iterator matrix<T>::const_element_iterator::operator--(int)
{
	element_iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns reference to element of row or column of constant matrix associated with iterator
*/
template<typename T>
inline const T& matrix<T>::const_element_iterator::operator*() const
{
	return mem_block.get()[p.cols * r_index + c_index];
}

/**
 * \brief Returns pointer to element of row or column of constant matrix associated with iterator
*/
template<typename T>
inline const T* matrix<T>::const_element_iterator::operator->() const
{
	return &(mem_block.get()[p.cols * r_index + c_index]);
}

/**
 * \brief Moves iterator to next element of matrix (prefix incrementation)
*/
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

/**
 * \brief Moves iterator to next element of matrix (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::iterator matrix<T>::iterator::operator++(int)
{
	iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves iterator to previous element of matrix (prefix decrementation)
*/
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

/**
 * \brief Moves iterator to previous element of matrix (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::iterator matrix<T>::iterator::operator--(int)
{
	iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns reference to element of matrix associated with iterator
*/
template<typename T>
inline T& matrix<T>::iterator::operator*() const
{
	return mem_block.get()[current_row * p.cols + current_col];
}

/**
 * \brief Returns pointer to element of matrix associated with iterator
*/
template<typename T>
inline T* matrix<T>::iterator::operator->() const
{
	return &(mem_block.get()[current_row * p.cols + current_col]);
}

/**
 * \brief Moves iterator to next element of constant matrix (prefix incrementation)
*/
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

/**
 * \brief Moves iterator to next element of constant matrix (postfix incrementation)
*/
template<typename T>
inline typename matrix<T>::const_iterator matrix<T>::const_iterator::operator++(int)
{
	const_iterator old(*this);
	++(*this);
	return old;
}

/**
 * \brief Moves iterator to previous element of constant matrix (prefix decrementation)
*/
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

/**
 * \brief Moves iterator to previous element of constant matrix (postfix decrementation)
*/
template<typename T>
inline typename matrix<T>::const_iterator matrix<T>::const_iterator::operator--(int)
{
	const_iterator old(*this);
	--(*this);
	return old;
}

/**
 * \brief Returns reference to element of constant matrix associated with iterator
*/
template<typename T>
inline const T& matrix<T>::const_iterator::operator*() const
{
	return mem_block.get()[current_row * p.cols + current_col];
}

/**
 * \brief Returns pointer to element of constant matrix associated with iterator
*/
template<typename T>
inline const T* matrix<T>::const_iterator::operator->() const
{
	return &(mem_block.get()[current_row * p.cols + current_col]);
}

}
