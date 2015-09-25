// This file incorporate the ublas matrix class to
// build my matrix function library for NLA class.
//
// Zhenfeng Liang
//
// 22:08 08/17/2014 In Elmhurst, New York
// 8/30/2014 Changed all the m_data way access member to () reading and writing elements.

#ifndef MATRIXFUNCTION_HPP
#define MATRIXFUMCTION_HPP

#include "Matrix.hpp"


class MatrixFunction
{
private:
	Matrix m_matrix;
public:
	MatrixFunction(const Matrix& newmatrix);
	~MatrixFunction();

	Matrix percent_return();
	Matrix ln_return();

	Matrix percent_cov();
	Matrix ln_cov();

	Matrix percent_corr();
	Matrix ln_corr();

	// Given the return matrix
	Matrix cov();

};

#endif