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

#include <exception>
#include <string>

namespace mn {

class matrix_exception : public std::exception
{
public:
	matrix_exception() noexcept : message("") {}
	matrix_exception(std::string message) noexcept : message(message) {}
	matrix_exception(const char* message) noexcept : message(message) {}
	virtual ~matrix_exception() {}
	virtual const char* what() const noexcept { return message.c_str(); }
protected:
	std::string message;
};

}
