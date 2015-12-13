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

#include <chrono>
#include <random>

namespace mn {

static long long seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::default_random_engine generator(static_cast<unsigned int>(seed));

template<typename T>
inline typename matrix<T> matrix<T>::zeros(int rows, int cols)
{
	matrix<T> m(rows, cols);
	for (auto i = m.begin(); i != m.end(); ++i)
		*i = 0;
	return m;
}

template<typename T>
inline typename matrix<T> matrix<T>::zeros(int rows_cols)
{
	return zeros(rows_cols, rows_cols);
}

template<typename T>
inline typename matrix<T> matrix<T>::ones(int rows, int cols)
{
	matrix<T> m(rows, cols);
	for (auto i = m.begin(); i != m.end(); ++i)
		*i = 1;
	return m;
}

template<typename T>
inline typename matrix<T> matrix<T>::ones(int rows_cols)
{
	return ones(rows_cols, rows_cols);
}

template<typename T>
inline typename matrix<T> matrix<T>::identity(int rows_cols)
{
	matrix<T> m = zeros(rows_cols);
	for (int i = 0; i < m.rows(); ++i)
		m[i][i] = 1;
	return m;
}

template<typename T>
template<typename R>
inline typename matrix<T> matrix<T>::rand(int rows, int cols, R& random_distribution)
{
	matrix<T> m(rows, cols);
	for (auto i = m.begin(); i != m.end(); ++i)
		*i = random_distribution(generator);
	return m;
}

template<typename T>
template<typename R>
inline typename matrix<T> matrix<T>::rand(int rows_cols, R& random_distribution)
{
	return rand(rows_cols, rows_cols, random_distribution);
}

}
