// This file incorporate the ublas matrix class to
// build my matrix function library for NLA class.
//
// Zhenfeng Liang
//
// 22:08 08/17/2014 In Elmhurst, New York
// 8/30/2014 Changed all the m_data way access member to () reading and writing elements.

#include "Matrix_Function.hpp"

MatrixFunction::MatrixFunction(const Matrix& newmatrix):m_matrix(newmatrix)
{
}

MatrixFunction::~MatrixFunction()
{
}

Matrix MatrixFunction::percent_return()
{
	Matrix temp(m_matrix.Size1()-1, m_matrix.Size2());

	for( int k = 0; k < m_matrix.Size2(); ++k)
	{
		for( int j = 0; j < (m_matrix.Size1() - 1); j++)
		{
			temp(j,k) = (m_matrix(j+1,k) - m_matrix(j,k))/m_matrix(j,k);
		}
	}

	return temp;
}

Matrix MatrixFunction::ln_return()
{
	Matrix temp(m_matrix.Size1()-1, m_matrix.Size2());

	for( int k = 0; k < m_matrix.Size2(); ++k)
	{
		for( int j = 0; j < (m_matrix.Size1() - 1); j++)
		{
			temp(j,k) = log(m_matrix(j+1,k)/m_matrix(j,k));
		}
	}

	return temp;
}


Matrix MatrixFunction::percent_cov()
{
	Matrix T(percent_return());

	for( int k = 0; k < T.Size2(); k++)
	{
		double miu_k = 0;

		for( int j = 0; j < T.Size1(); j++)
		{
			miu_k += T(j,k);
		}

		miu_k /= T.Size1();

		for( int j = 0; j < T.Size1(); j++)
		{
			T(j,k) -= miu_k;
		}
	}

	return (T.Trans() * T)/(T.Size1() - 1);
}

Matrix MatrixFunction::ln_cov()
{
	Matrix T(ln_return());

	for( int k = 0; k < T.Size2(); k++)
	{
		double miu_k = 0;

		for( int j = 0; j < T.Size1(); j++)
		{
			miu_k += T(j,k);
		}

		miu_k /= T.Size1();

		for( int j = 0; j < T.Size1(); j++)
		{
			T(j,k) -= miu_k;
		}
	}

	return (T.Trans() * T)/(T.Size1() - 1);
}

Matrix MatrixFunction::percent_corr()
{
	Matrix temp(percent_cov());
	Matrix D_inv(temp.Size1(), temp.Size2());

	for ( int j = 0; j < temp.Size1(); ++j)
	{
		for( int k = 0; k < temp.Size2(); ++k)
		{
			D_inv(j,k) = 0;
			
			if(j == k)
			{
				D_inv(j,k) = 1/(sqrt(temp(j,k)));
			}
		}
	
	}

	temp = D_inv * temp;
	
	return (temp * D_inv);
}

Matrix MatrixFunction::ln_corr()
{
	Matrix temp(ln_cov());
	Matrix D_inv(temp.Size1(), temp.Size2());

	for ( int j = 0; j < temp.Size1(); ++j)
	{
		for( int k = 0; k < temp.Size2(); ++k)
		{
			D_inv(j,k) = 0;
			
			if(j == k)
			{
				D_inv(j,k) = 1/(sqrt(temp(j,k)));
			}
		}
	
	}

	temp = (D_inv * temp);
	
	return (temp * D_inv);
}

Matrix MatrixFunction::cov()
{
	Matrix T(m_matrix);

	for( int k = 0; k < T.Size2(); k++)
	{
		double miu_k = 0;

		for( int j = 0; j < T.Size1(); j++)
		{
			miu_k += T(j,k);
		}

		miu_k /= T.Size1();

		for( int j = 0; j < T.Size1(); j++)
		{
			T(j,k) -= miu_k;
		}
	}

	return (T.Trans() * T)/(T.Size1() - 1);
}