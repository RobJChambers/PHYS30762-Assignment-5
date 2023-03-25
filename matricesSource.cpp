// Robbie Chambers Assignment 5 source code
// Errors key : 101 - Index out of range
//              102 - Dimension incompatibility (adding,subtracting)
//              103 - Dimension incompatibility (multiplication)
//              104 - Vector length incompatibility
#include "matricesHeader.h"

#include <iostream>
#include <cmath>
#include <string>

// Checks the input is a double
bool is_double(std::string user_input)
{
	bool valid{ true };
	try {
		double x = std::stod(user_input);
		valid = true;
	}
	catch (std::invalid_argument user_input) {
		valid = false;
	}

	return valid;

}

// Returns true is 'y' input, false if 'n' input. Otherwise asks to retry.
bool yes_no_as_bool()
{
	bool valid{ false };
	char x;
	while (!valid) {
		std::cin >> x;
		std::cin.ignore(1000, '\n');
		if (x == 'y') {
			valid = true;
			break;
		}
		else if (x == 'n') {
			valid = false;
			break;
		}
		else {
			std::cerr << "Invalid input. Please try again." << std::endl;
			valid = false;
		}
	}
	return valid;
}
//Overloading dot product for vectors
double dot_product(const std::vector<double> vec1, const std::vector<double> vec2)
{
    if(vec1.size() == vec2.size()){
        double product = 0;
        for(int i = 0; i<vec1.size(); ++i){
            product += vec1[i] * vec2[i];
        }
        return product;
    }else{
        std::cerr << "Vector inner product not valid between vectors of size "
        << vec1.size() << " and " << vec2.size() << std::endl;
        throw 104;
    }
};

/*Overloading the insert operator. Checks whether matrix is empty.If so inserts
"Empty matrix"*/
std::ostream& operator<<(std::ostream& os, const matrix& mat)
{
	if (mat.rows == 0 || mat.columns == 0) {
		std::cout << "Empty matrix" << std::endl;
	}
	else if (mat.columns == 1) {
		os << std::endl << "[";
		for (int i = 0; i < mat.rows * mat.columns; ++i) {
			os << " " << mat.data[i];
			if (i != mat.rows * mat.columns - 1) {
				os << std::endl;
			}
		}
		os << "]";
	}else {
		os << std::endl << "[";
		for (int i = 0; i < mat.rows * mat.columns; ++i) {
			os << " " << mat.data[i];
			if (i == 0) { continue; }
			if (i == mat.rows * mat.columns-1) { continue; }
			else if ((i+1) % mat.columns == 0) {
				os << std::endl;
			}
		}
		os << "]";
	}
	return os;
}
// Overloading extraction operator. 
std::istream& operator>>(std::istream& is, matrix& mat)
{
	std::string input;
	int i = 0;
	while (is >> input) {
		if (i > mat.rows * mat.columns) {
			std::cout << "Input at index " << i << "overflows the size of the target matrix. All remaining characters will be ignored.";
			return is;
		}
		if (is_double(input)) {
			mat.data[i] = std::stod(input);
		}else{
			std::cout << input << " is not a valid matrix element. Would you like to replace or ignore this entry" << std::endl;
			std::cout << "Please enter 'y' to replace, 'n' to ignore." << std::endl;
			// If ignored
			if (!yes_no_as_bool()) {
				continue;
			}
			// If replaced
			std::string new_element;
			while (true) {
				std::cout << "Please enter a replacement number." << std::endl;
				while (getline(std::cin, new_element)) {
					if (!new_element.empty()) {
						break;
					}
				};
				if (is_double(new_element)) {
					mat.data[i] = std::stod(new_element);
					break;
				}else{
					std::cout << new_element << " is not a valid matrix element. Please enter a real double." << std::endl;
				}
			}
		}
		++i;
	}
	return is;
}

// Constructors
// Default
matrix::matrix() {}
// Parameterised (size)
matrix::matrix(int r, int c)
{
	rows = r;
	columns = c;
	size = r * c;
	data = new double[r * c];
}
// Copy constructor
matrix::matrix(matrix& mat)
{
	rows = mat.rows;
	columns = mat.columns;
	size = mat.size;
	data = nullptr;

	if (mat.size > 0) {
		data = new double[mat.size];
		for (int i = 0; i < mat.size; ++i) { data[i] = mat.data[i]; }
	}
}
// Move constructor
matrix::matrix(matrix &&mat) noexcept
{
	rows = mat.rows;
	columns = mat.columns;
	size = mat.size;
	data = mat.data;
	mat.rows = 0;
	mat.size = 0;
	mat.columns = 0;
	mat.data = nullptr;
}
// Destructor
matrix::~matrix() { delete data; }

// Member functions
int matrix::number_of_rows() const { return rows; }
int matrix::number_of_columns() const { return columns; }
int matrix::get_size() const {return size;}
int matrix::index(int i, int j) const { return (j - 1) + (i - 1) * columns; }

// Change entry: takes an index (integer) at which the value should be replace by the second given parameter (double).
void matrix::change_entry(int i, int j, double x) { data[index(i,j)] = x; }

/* Takes an integer input to index a row of the matrix. Checks it does not 
exceed dimensions of the matrix. Returns a vector containing the relevant 
elements.
NOTE: This uses mathematical indexing rather than computing indexing*/
std::vector<double> matrix::get_row(int i) const
{
    if(i>rows){
        std::cerr << "Index, " << i << ", out of range for matrix with " << rows << " rows" << std::endl;
        throw 101;
    }else{
        std::vector<double> output_row;
        // Index of first element of indexed rows
        int start = (i-1)*columns;
        // Index of last element
        int end = start + columns;

        for(int entry=start; entry < end; ++entry){
            output_row.push_back(data[entry]);
        }
        return output_row;
    }
}
/* Takes an integer input to index a column of the matrix. Checks it does not 
exceed dimensions of the matrix. Returns a vector containing the relevant 
elements.
NOTE: This uses mathematical indexing rather than computing indexing*/
std::vector<double> matrix::get_column(int i) const
{
    if(i>columns){
        std::cerr << "Index, " << i << ", out of range for matrix with " <<
        columns << " columns" << std::endl;
        throw 101;
    }else{
        std::vector<double> output_column;
        for(int entry=i-1; entry < size; entry += rows){
            output_column.push_back(data[entry]);
        }
        return output_column;
    }
}


// Overloading operators
// Deep Copy Assignment Operator
matrix matrix::operator=(const matrix& mat2)
{
	if (&mat2 == this) { std::cout << "Warning: Attempted self-assignment" << std::endl; return *this; }

	if (rows != mat2.rows || columns != mat2.columns) {
		std::cout << "Warning: Assingment changes matrix shape" << std::endl;
	}

	delete data;
	rows = mat2.rows;
	columns = mat2.columns;
	size = rows * columns;
	data = new double [size];
	for (int i = 0; i < size; ++i) {
		data[i] = mat2.data[i];
	}

	return *this;
}

// Move Assignment Operator
matrix matrix::operator=(matrix&& mat) noexcept
{
	rows = mat.rows;
	columns = mat.columns;
	size = mat.size;
	data = mat.data;
	mat.rows = 0;
	mat.size = 0;
	mat.columns = 0;
	mat.data = nullptr;
	return *this;
}


// Python-style 2D matrix indexing
double& matrix::operator()(int i, int j){return data[index(i,j)];}
// Addition: Checks dimensions match then adds element-wise, or gives error message respectively
matrix matrix::operator+(const matrix mat2)const
{
    if(rows == mat2.rows && columns == mat2.columns){
        matrix temp_matrix(rows, columns);
        for(int i = 0; i < size; ++i){
            temp_matrix.data[i] = data[i] + mat2.data[i];
        }
        return temp_matrix;
    }else{
        std::cerr << "Matrix with shape [" << mat2.rows << "," << mat2.columns <<
        "] could not be added to matrix with shape [" << rows << "," << columns << "]." << std::endl;
        throw 102;
    }
}

// Subtraction: Checks dimensions match then subtracts element-wise, or gives error message respectively
matrix matrix::operator-(const matrix mat2)const
{
    if(rows == mat2.rows && columns == mat2.columns){
        matrix temp_matrix(rows, columns);
        for(int i = 0; i < size; ++i){
            temp_matrix.data[i] = data[i] - mat2.data[i];
        }
        return temp_matrix;
    }else{
        std::cerr << "Matrix with shape [" << mat2.rows << "," << mat2.columns <<
        "] could not be subtracted from matrix with shape [" << rows << "," << 
        columns << "]." << std::endl;
        throw 102;
    }
}

//Multiplication
matrix matrix::operator*(const matrix mat2)const
{
	try {
		if (columns == mat2.rows) {
			matrix temp_matrix(rows, mat2.columns);
			for (int i = 1; i < rows + 1;++i) {
				for (int j = 1; j < mat2.columns + 1; ++j) {
					temp_matrix(i, j) = dot_product(get_row(i), mat2.get_column(j));
				}
			}
			return temp_matrix;
		}else {
			throw 103;
		}
	}
	catch (...) {
		std::cerr << "Matrix with shape [" << rows << "," << columns <<
			"] could not be multiplied with matrix with shape [" << mat2.rows 
			<< "," << mat2.columns << "]." << std::endl;
		matrix empty;
		return empty;
	}  
}

// Other member functions
// Dot product
double matrix::dot(const matrix mat2) const
{
	if (rows == mat2.rows && columns == mat2.columns) {
		double product = 0;
		for (int i = 0; i < size;++i) {
			product += data[i] * mat2.data[i];
		}
		return product;
	}
	else {
		std::cerr << "Inner product of matrix with shape [" << mat2.rows << ","
			<< mat2.columns << "] could not be calculated with matrix with shape ["
			<< rows << "," << columns << "]." << std::endl;
		throw 103;
	}
};

// Delete Row
matrix matrix::delete_row(const int m)
{
	if (m <= rows && m > 0) {
		matrix new_matrix(rows - 1, columns);
		for (int i = 0; i < new_matrix.size; ++i) {
			// Skipping the row if it matches the starting index
			if (i >= index(m, 1)) {
				new_matrix.data[i] = data[i + columns];
				continue;
			}
			new_matrix.data[i] = data[i];
		}
		return new_matrix;
	}else {
		std::cout << "Could not delete row:" << std::endl;
		std::cout << m << " is out of range for " << rows << " rows." << std::endl;
		return *this;
	}
};

// Delete column
matrix matrix::delete_column(const int m) 
{
	if (m <= columns && columns > 0) {
		matrix new_matrix(rows, columns - 1);
		int count = 0;
		for (int i = 0; i < new_matrix.size; ++i) {
			// Skipping elements that have been deleted
			if ((i + count) % columns == m - 1) {
				++count;
			}
			new_matrix.data[i] = data[i+count];

		}
		return new_matrix;
	}
	else {
		std::cout << "Could not delete column:" << std::endl;
		std::cout << m << " is out of range for " << columns << " columns." << std::endl;
		return *this;
	}
}

// Create minor
matrix matrix::minor(int m, int n)
{
	matrix temp1 = delete_row(m);
	matrix temp2 = temp1.delete_column(n);
	return temp2;

}

// Finding determinant
double matrix::determinant()
{
	if (!is_square()) {
		std::cerr << "Cannot find determinant of matrix with dimensions (" <<
			rows << "," << columns << ")." << std::endl;
		return 0;
	}

	if (rows == 0 || columns == 0) return 1;

	if (rows == 1 || columns == 1) return data[0];

	double determinant = 0;
	for (int i = 0; i < rows; ++i) {
		determinant += pow(-1, i) * data[i] * minor(1, i + 1).determinant();
	}
	return determinant;
}

// Is square: returns true if matrix is square, else returns false
bool matrix::is_square()
{
	return rows == columns;
}