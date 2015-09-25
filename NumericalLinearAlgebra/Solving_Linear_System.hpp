// This file was about solving linear system using LU and cholesky decomposition
// and iterative methods, jacobi, gauss-seidel and sor methods splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#ifndef SOLVINGLINEARSYSTEM_HPP
#define SOLVINGLINEARSYSTEM_HPP

#include "Matrix.hpp"
#include <boost/tuple/tuple.hpp>

Matrix linear_solve_LU_no_pivoting(const Matrix& A, const Matrix& vector_b);

Matrix linear_solve_LU_no_pivoting_tridiag_spd(const Matrix& A, const Matrix& vector_b);

Matrix linear_solve_cholesky(const Matrix& A, const Matrix& vector_b);

Matrix linear_solve_cholesky_tridiag_spd(const Matrix& A, const Matrix& vector_b);

Matrix linear_solve_cholesky_banded(const Matrix& A, const Matrix& vector_b);


//**************************************************************************************************************************************************//
// Iterative methods for solving linear systems
// Return solution x, number of iteration and 2-norm of vector residual 
boost::tuple<Matrix, int, double> jacobi_iter_residual_based(const Matrix& A, const Matrix& b, const Matrix& x0, double tol);
boost::tuple<Matrix, int> jacobi_iter_consecutive_appro(const Matrix& A, const Matrix& b, const Matrix& x0, double tol);

// Note, in order to get the same iteration result as jacobo_itera, tol_gauss should be about 1e-3 * tol_jacobi
// Gauss_siedel_iteration converge faster than jacobi
// Return solution x, number of iteration and 2-norm of vector residual 
boost::tuple<Matrix, int, double> gauss_siedel_iter_residual_based(const Matrix& A, const Matrix& b, const Matrix& x0, double tol);	
boost::tuple<Matrix, int, double> gauss_siedel_iter_residual_based_tridiag(const Matrix& A, const Matrix& b, const Matrix& x0, double tol);	
boost::tuple<Matrix, int, double> gauss_siedel_iter_residual_based_banded(const Matrix& A, const Matrix& b, const Matrix& x0, double tol);

boost::tuple<Matrix, int> gauss_siedel_iter_consecutive_appro(const Matrix& A, const Matrix& b, const Matrix& x0, double tol);	


// Note!!!!This function does not converge for omega != 1. When omega = 1, it is gauss iteration.
// Return solution x, number of iteration and 2-norm of vector residual 
boost::tuple<Matrix, int, double> sor_iter_residual_based(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega);
boost::tuple<Matrix, int, double> sor_iter_residual_based_tridiag(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega);
boost::tuple<Matrix, int, double> sor_iter_residual_based_banded(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega);

boost::tuple<Matrix, int> sor_iter_consecutive_appro(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega);	


#endif