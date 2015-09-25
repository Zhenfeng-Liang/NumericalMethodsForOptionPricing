// This file was about LU and cholesky decomposition
// splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#include "Forward_Backward_subst.hpp"



Matrix forward_subst(const Matrix& L, const Matrix& vector_b)
{
	int n = L.Size2();
	Matrix x(n,1);

	x(0,0) = vector_b(0,0) / (L(0,0));
	for(int j = 1; j < n; j++)
	{
		double sum = 0;
		for(int k = 0; k <= j-1; k++)
		{
			sum += L(j,k)*x(k,0);
		}

		x(j,0) = (vector_b(j,0) - sum) / L(j,j);
	}
	return x;
}

Matrix forward_subst_bidiag(const Matrix& L, const Matrix& vector_b)
{
	int n = L.Size2();
	Matrix x(n,1);

	x(0,0) = vector_b(0,0) / L(0,0);
	
	for(int j = 1; j < n; j++)
		x(j,0) = (vector_b(j,0) - L(j,j-1) * x(j-1,0)) / L(j,j);

	return x;

}

Matrix forward_subst_banded(const Matrix& L, const Matrix& vector_b)
{
	int n = L.Size2();
	Matrix x(n,1);

	int j = 1;
	for(; L(n-j,0) == 0; j++);				// Calculate the band
	j = j - 1;								// This is the number of 0
	int m = n - j - 1;

	x(0,0) = vector_b(0,0) / L(0,0);

	for(int j = 1; j < n; j++)
	{
		double sum = 0;
		for(int k = max(0,j-m); k <= j-1; k++)
		{
			sum += L(j,k)*x(k,0);
		}
		x(j,0) = (vector_b(j,0) - sum)/L(j,j);
	}
	return x;
}

Matrix backward_subst(const Matrix& U, const Matrix& vector_b)
{
	int n = U.Size2();
	Matrix x(n,1);

	x(n-1,0) = vector_b(n-1,0) / U(n-1,n-1);
	for(int j = n-2; j >= 0; j--)
	{
		double sum = 0;
		for(int k = j+1; k < n; k++)
		{
			sum += U(j,k) * x(k,0);
		}
		x(j,0) = (vector_b(j,0) - sum) / U(j,j);
	}
	return x;
}

Matrix backward_subst_bidiag(const Matrix& U, const Matrix& vector_b)
{
	int n = U.Size2();
	Matrix x(n,1);

	x(n-1,0) = vector_b(n-1,0) / U(n-1,n-1);
	
	for(int j = (n-2); j >= 0; j--)
		x(j,0) = (vector_b(j,0) - U(j,j+1) * x(j+1,0)) / U(j,j);

	return x;
}

Matrix backward_subst_banded(const Matrix& U, const Matrix& vector_b)
{
	int n = U.Size2();
	Matrix x(n,1);

	int j = 1;
	for(; U(0,n-j) == 0; j++);				// Calculate the band
	j = j - 1;								// This is the number of 0
	int m = n - j - 1;
	
	x(n-1,0) = vector_b(n-1,0) / U(n-1,n-1);
	for(int j = n-2; j >= 0; j--)
	{
		double sum = 0;
		for(int k = j+1; k <= min(j+m,n-1); k++)
		{
			sum += U(j,k) * x(k,0);
		}
		x(j,0) = (vector_b(j,0) - sum) / U(j,j);
	}
	return x;
}