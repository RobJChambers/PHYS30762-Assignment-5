// Robbie Chambers Assignment 5 source code
// Errors key : 101 - Index out of range
//              102 - Dimension incompatibility (adding,subtracting)
//              103 - Dimension incompatibility (multiplication)
#include "matricesHeader.h"

#include <iostream>
#include <cmath>
#include <string>

int main()
{
    // Declaring and defining strings
    std::string a_string{ "1 2 3 9 8 7 4 2 6" };
    std::string b_string{ "5 5 4 1 2 3 6 9 8" };
    std::string c_string{ "3 4 1 2 5 6" };
    // Declaring stringstreams
    std::stringstream a_stream;
    std::stringstream b_stream;
    std::stringstream c_stream;
    // Inserting strings
    a_stream << a_string;
    b_stream << b_string;
    c_stream << c_string;
    // Parameterised constructors
    matrix a(3,3), b(3,3), c(2,3);
    // Demonstrating
    a_stream >> a;
    b_stream >> b;
    c_stream >> c;
    // Outputting the matrices
    std::cout << "A = " << a << std::endl;
    std::cout << "B = " << b << std::endl;
    std::cout << "C = " << c << std::endl;

    // Demonstrating operations
    std::cout << "A + B = " << a + b << std::endl;
    std::cout << "A - B = " << a - b << std::endl;
    std::cout << "A.B = " << a * b << std::endl;
    std::cout << "C.B =  " << c * b << std::endl;
    std::cout << "However, when we try to multiple B.C we get this error: " << std::endl;
    std::cout << "Attempting B.C returns: " << b * c << std::endl;

    // Calculating determinants
    std::cout << "The determinant of A is " << a.determinant() << std::endl;
    std::cout << "The determinant of B is " << b.determinant() << std::endl;

    // Demonstrating minors of matrix A
    std::cout << "Minor of matrix A, row 2 and column 2 removed: " << a.minor(2, 2) << std::endl;

    // Copy constructor and editing
    matrix d{ a };
    d.change_entry(2, 2, 15);
    std::cout << "Creating a copy of A, called D, and changing an element." << std::endl;
    std::cout << "The orginal A = " << a << std::endl;
    std::cout << "D = " << d << std::endl;

    // Move constructor demonstrating the empty old A and the new moved A containing its data
    matrix e{ std::move(a) };
    std::cout << "A has been altered due to move constructor in declaration of a new matrix, E" << std::endl;
    std::cout << "A is now: " << a << std::endl;
    std::cout << "The new, moved A, called E is now: " << e << std::endl;

    // Copy assignment demonstration
    matrix f;
    f = e;
    std::cout << "Using the copy assignment operator on E gives F:" << std::endl;
    std::cout << "F =" << f << std::endl;
    matrix g;
    g = std::move(f);
    std::cout << "F can then be moved to G using move assignment." << std::endl;
    std::cout << "This yields:" << std::endl;
    std::cout << "F = " << f << std::endl;
    std::cout << "G = " << g << std::endl;
    return 1;
}
