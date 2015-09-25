// This file was about LU and cholesky decomposition
// splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#ifndef MATRIXDECOMPOSITION_HPP
#define MATRIXDECOMPOSITION_HPP

#include "Matrix.hpp"
#include <boost/tuple/tuple.hpp>

boost::tuple<Matrix, Matrix> lu_no_pivoting(Matrix A);				// Output tuple(L,U)

boost::tuple<Matrix, Matrix> lu_no_pivoting_tridiag(Matrix A);		// Output tuple(L,U)

boost::tuple<Matrix, Matrix> lu_no_pivoting_banded(Matrix A, int m); // Output tuple(L,U)

boost::tuple<Matrix, Matrix, Matrix> lu_row_pivoting(Matrix A);		// Output tuple(P,L,U)


Matrix cholesky(Matrix A);

Matrix cholesky_tridiag_spd(Matrix A);

Matrix cholesky_banded(Matrix A);

#endif