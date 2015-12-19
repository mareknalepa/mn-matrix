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

/**
 * \brief mn::matrix_exception
 *
 * Represents exceptions thrown by methods dealing with matrices.
 * It can carry text message describing unexpected situation.
 *
*/
class matrix_exception : public std::exception
{
public:
	/**
	 * \brief Default constructor
	 *
	 * Creates empty matrix_exception object.
	*/
	matrix_exception() noexcept : message("") {}

	/**
	 * \brief Constructor with string message
	 *
	 * Creates matrix_exception object initialized with message string.
	 *
	 * \param message String message
	*/
	matrix_exception(std::string message) noexcept : message(message) {}

	/**
	 * \brief Constructor with C-style string message
	 *
	 * Creates matrix_exception object initialized with C-style message string.
	 *
	 * \param message C-style string message
	*/
	matrix_exception(const char* message) noexcept : message(message) {}

	/**
	 * \brief Returns exception message
	 *
	 * \return C-style string with exception message
	*/
	virtual const char* what() const noexcept { return message.c_str(); }
protected:
	std::string message;
};

}
