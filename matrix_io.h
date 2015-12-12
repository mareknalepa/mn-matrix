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
inline std::istream& operator>>(std::istream& i, matrix<T>& m)
{
	for (auto iterator = m.begin(); iterator != m.end(); ++iterator)
	{
		i >> *iterator;
	}

	return i;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& o, const matrix<T>& m)
{
	o << "[" << std::endl;
	for (auto row = m.first_row(); row != m.last_row(); ++row)
	{
		o << "\t";
		auto element = row.first_element();
		auto before_last = --(row.last_element());
		while (element != before_last)
		{
			o << *element << "\t";
			++element;
		}
		if (element != row.last_element())
			o << *element;
		o << std::endl;
	}
	o << "]" << std::endl;
	
	return o;
}

}
