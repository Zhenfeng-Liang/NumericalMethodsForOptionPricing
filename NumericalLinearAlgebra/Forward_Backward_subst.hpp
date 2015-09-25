// This file was about LU and cholesky decomposition
// splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#ifndef FORWARD_BACKWARD_SUBST_HPP
#define FORWARD_BACKWARD_SUBST_HPP

#include "Matrix.hpp"

Matrix forward_subst(const Matrix& L, const Matrix& vector_b);

Matrix forward_subst_bidiag(const Matrix& L, const Matrix& vector_b);

Matrix forward_subst_banded(const Matrix& L, const Matrix& vector_b);

Matrix backward_subst(const Matrix& U, const Matrix& vector_b);

Matrix backward_subst_bidiag(const Matrix& U, const Matrix& vector_b);

Matrix backward_subst_banded(const Matrix& U, const Matrix& vector_b);


#endif