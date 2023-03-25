// Robbie Chambers Assignment 5 source code
// Errors key : 101 - Index out of range
//              102 - Dimension incompatibility (adding,subtracting)
//              103 - Dimension incompatibility (multiplication)
#include "matricesHeader.h"

#include <iostream>
#include <cmath>
#include <string>

//Overloading dot product for vectors
// double dot(const std::vector<double> vec1, const std::vector<double> vec2)
// {
//     if(vec1.size() == vec2.size()){
//         double product = 0;
//         for(int i = 0; i<vec1.size(); ++i){
//             product += vec1[i] * vec2[i];
//         }
//         return product;
//     }else{
//         std::cerr << "Vector inner product not valid between vectors of size "
//         << vec1.size() << " and " << vec2.size() << std::endl;
//         throw 104;
//     }
// };

int main()
{
    std::string a_string{ "1 2 3 9 8 7 4 2 6" };
    std::string b_string{ "5 5 4 1 2 3 6 9 8" };
    std::string c_string{ "3 4 1 2 5 6" };
    std::stringstream a_stream;
    std::stringstream b_stream;
    std::stringstream c_stream;
    a_stream << a_string;
    b_stream << b_string;
    c_stream << c_string;
    matrix a(3,3), b(3,3), c(2,3);
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
    std::cout << "However, when we try to multiply B.C we get this error: " << std::endl;
    std::cout << "Attempting B.C returns: " << b * c << std::endl;

    // Calculating determinants
    std::cout << "The determinant of A is " << a.determinant() << std::endl;
    std::cout << "The determinant of B is " << b.determinant() << std::endl;

    // Copy constructor and editing
    matrix a_prime(a);
    a_prime.change_entry(2, 2, 15);
    std::cout << "Creating a copy of A, A', and changing an element." << std::endl;
    std::cout << "The orginal A = " << a << std::endl;
    std::cout << "The new A, A' = " << a_prime << std::endl;

    // Move constructor demonstrating the empty old A and the new moved A containing its data
    matrix moved_a;
    moved_a = std::move(a);
    std::cout << "Moving A:" << std::endl;
    std::cout << "A is now: " << a << std::endl;
    std::cout << "The new, moved A is now: " << moved_a << std::endl;

    return 1;
}