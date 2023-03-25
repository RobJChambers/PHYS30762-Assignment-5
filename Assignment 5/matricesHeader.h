#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdlib.h>
/** /brief
* Dot product for vectors.
* 
* Calculates the cumulative sum of the product of the corresponding elements in
* each input vector. The function checks the inputs are of the same length and
* if so, iterates through each of the elements in both vectors, adding the
* product of which to a cumulative sum.
* 
* @param[in] vec1 First input vector of doubles.
* 
* @param[in] vec2 Second input vector of doubles.
* 
* @param[out] product A double
*/
double dot_product(const std::vector<double> vec1, const std::vector<double> vec2);

class matrix
{
	// Friends
	friend std::ostream& operator<<(std::ostream& os, const matrix& mat);
	friend std::istream& operator>>(std::istream& os, matrix& mat);

private:
	double* data{ nullptr }; //!< Array of doubles containing the elements of the array.
	int rows{ 0 }; //!< Number of rows in the matrix.
	int columns{ 0 }; //!< Number of columns in the matrix.
	int size{ 0 }; //!< Size of the matrix, given by No. rows * No. columns.
public:
/** /brief 
* Default constructor
*
* Default Constructor initialises data as a nullptr. Initialises size, rows and
* columns to 0.
*/
	matrix();

/** /brief
* Parameterised constructor taking r (int) and c (int) as arguments.
*
* r (int) represents the number of rows, and c (int) the number of columns.
* Initialises data as an empty array of doubles of size r x c.
* Initialises rows as r, columns as c, and size (int) as r x c.
*
* @param[in] r Integer of the number of rows in the matrix.
* @param[in] c Integer of the number of columns in the matrix.
*/
	matrix(int r, int c);

/** /brief
* Parameterised copy constructor taking 'mat' argument.
*
* Takes mat (Matrix) as an argument. This is a reference matrix, the data of 
* which is deep copied to the newly created matrix.
*
* @param[in] mat Matrix to be deep copied.
*/
	matrix(matrix& mat);

/** /brief
* A matrix move constructor.
* 
* Takes an argument &&mat, an rvalue reference to the Matrix that is to be 
* moved. The data of this matrix is (deep) copied to the new matrix, and then
* deleted. The result is a new matrix, identical to the reference matrix but 
* with a different variable name, and the reference matrix that now has the 
* values that would be assigned by the default constructor.
* 
* @see matrix()
* @see operator=()
*/
	matrix(matrix &&mat) noexcept;
/**
* A Matrix destructor.
* 
* A destructor for the Matriz class. Deletes the array (data) stored on the
* heap.
*/
	~matrix();

// Access functions
/**
* Returns the number of rows.
* 
* @param[out] columns Integer return value giving the number of columns in the 
*					  matrix
*/
	int number_of_rows() const;

/**
* Returns the number of rows.
*
* @param[out] rows Integer return value giving the number of rows in the matrix
*/
	int number_of_columns() const;

/**
* Returns the size of the matrix.
*
* @param[out] size Integer return value giving the size of the matrix
*/
	int get_size() const;

/**
* Calculates the 1D location of mathematical index (i,j)
* 
* Calculates the position in the 1 dimensional array of elements corresponding
* to the index (i,j) using the formula loc = (j-1) + (i-1) * n where n is the 
* number of columns. This is the return value.
* 
* @param[out] loc Location (int) of the indexed element.
*/
	int index(int i, int j) const;

/**
* Changes the value of the entry at index (i,j).
* 
* Finds the location of (i,j) using index() function, taking the first two
* arguments as row and column indices respectively. Then replaces the entry
* at the given index with the value of the third argument.
* 
* @param[in] i Row index (int).
* @param[in] j Column index (int).
* @param[in] x Value to replace (i,j) element
*/
	void change_entry(int i, int j, double x);

/**
* Returns vector containing all the elements in a given row.
* 
* 
*/
	std::vector<double> get_row(int i) const;
	std::vector<double> get_column(int i) const;

// Operator overloading
	matrix operator=(const matrix& mat2);
	matrix operator=(matrix&& mat2) noexcept;
	double& operator()(int m, int n);
	matrix operator+(const matrix mat2)const;
	matrix operator-(const matrix mat2)const;
    matrix operator*(const matrix mat2)const;

// Other member functions

	double dot(const matrix mat2)const;
	matrix delete_row(const int m);
	matrix delete_column(const int n);
	matrix minor(const int m, const int n);
	double determinant();
	bool is_square();
};