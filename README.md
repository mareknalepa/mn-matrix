# mn-matrix
Open source C++ header-only library that provides basic matrix operations.

## Basic concepts
This library assumes, that matrix is stored in memory as one, continuous block
(not like trivial approach, where matrix is mean as two-dimensional array). To access
single element, its coordinates are recalculated to address particular offset in
one-dimensional array.

Whenever it is possible, library tries not to copy whole memory block. When copy
constructor is used, only small object describing matrix is created. This small
object points to original memory block, thus sharing it with original matrix.
Explicit matrix copying (including memory block) is user responsibility. This
approach reduces complexity of basic operations.

This library provides also a functionality which allows user to create submatrices.
It is similar to copying through copy constructor - only small object is created
and pointing to original memory block. But there is a small difference - new object
points only to selected region of original matrix. Every modification made on
submatrix affects the origial matrix too. Of course user can make explicit copy of
submatrix which prevents changes from affecting original.

## Creating matrix objects
To create 3x4 sized matrix:

    mn::matrix<double> m1(10, 20);

To create square matrices:

    mn::matrix<double> m2(5);

### Using predefined generators
To create zero matrix:

    auto m3 = mn::matrix<double>::zeros(2, 8);
    auto m4 = mn::matrix<double>::zeros(4);

Creating matrix with ones in every element:

    auto m5 = mn::matrix<double>::ones(7, 3);
    auto m6 = mn::matrix<double>::ones(6);

Random matrices:

    auto m7 = mn::matrix<double>::rand(3, 1, std::normal_distribution<double>(1.0, 0.5));
    auto m8 = mn::matrix<int>::rand(8, std::uniform_int_distribution<int>(0, 10));

## Accessing elements
Accessing elements with specified coordinates using subscript operators:

    m[4][3] = 4.323;
    std::cout << m[6][1];

Accessing using row -> element iterators:

    for (auto row = m.first_row(); row != m.last_row(); ++row)
		for (auto element = row.first_element(); element != row.last_element(); ++element)
			std::cout << *element << std::endl;

Accessing using col -> element iterators:

    for (auto col = m.first_col(); col != m.last_col(); ++col)
        for (auto element = col.first_element(); element != col.last_element(); ++element)
            std::cout << *element << std::endl;

Accessing using standard, STL-like iterator:

    for (auto i = m.begin(); i != m.end(); ++i)
        std::cout << *i;

## Input and output
Matrix can be loaded from any standard C++ stream (standard input or file stream):

    std::cin >> m;

This method assumes, that input stream contains sufficient number of valid values.

Library provides convenient method to quickly print matrix to any stream:

    std::cout << m;

Matrix is printed row-by-row, each row in single line. Beginning and ending of matrix
is marked by square brackets.

## Copying and submatrices
When using copy constructor or copy assignment operator, the memory block of matrix
is not copied.

    mn::matrix<double> mclone(m);
    mn::matrix<double> mcopy = m;

To create submatrix, user have to specify interesting region of original matrix:

    auto subm = m.submatrix(1, 3, 6, 7);

Above example creates submatrix containing rows 1-3 and columns 6-7 inclusive.

## Arithmetic
Library provides serveral arithmetic operators allowing adding, subtracting and
multiplying matrices. Some examples:

    auto sum = m1 + m2;
    auto product = m1 * m2;
    auto diff = m1 - 5;
    m5 *= 3;
    m6 += m2;
    m4 /= 2;

Note, that every arithmetic operation has to be performed on matrices which dimensions
satisfy rules of the operation (adding is possible only on same-sized matrices, while
in multiplying inner dimensions must match).

