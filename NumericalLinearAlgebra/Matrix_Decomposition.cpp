// This file was about LU and cholesky decomposition
// splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#include "Matrix_Decomposition.hpp"

boost::tuple<Matrix, Matrix> lu_no_pivoting(Matrix A)
{
	int n = A.Size1();

	Matrix L(n,n);
	Matrix U(n,n);
//	struct LU temp_lu = {m, m};

	for(int i = 0; i < (n - 1); i++)
	{
		for(int k = i; k < n; k++)
		{
			U(i,k) = A(i,k);
			L(k,i) = A(k,i) / U(i,i);
		}
		for(int j = i+1; j < n; j++)
		{
			for(int k = i+1; k < n; k++)
			{
				A(j,k) = A(j,k) - L(j,i) * U(i,k);
			}
		}
	}
	L(n-1,n-1) = 1;
	U(n-1,n-1) = A(n-1,n-1);

	return boost::make_tuple(L,U);
}

boost::tuple<Matrix, Matrix> lu_no_pivoting_tridiag(Matrix A)
{
	int n = A.Size1();
	Matrix L(n,n);
	Matrix U(n,n);
	//	Matrix m(n,n);
//	struct LU temp_lu = {m, m};

	for(int i = 0; i < n-1; i++)
	{
		L(i,i) = 1;
		L(i+1,i) = A(i+1,i) / A(i,i);
		U(i,i) = A(i,i);
		U(i,i+1) = A(i,i+1);
		A(i+1,i+1) = A(i+1,i+1) - L(i+1,i) * U(i,i+1);
	}
	L(n-1,n-1) = 1;
	U(n-1,n-1) = A(n-1,n-1);

	return boost::make_tuple(L,U);
}

boost::tuple<Matrix, Matrix> lu_no_pivoting_banded(Matrix A, int m)
{
	int n = A.Size1();

	Matrix L(n,n);
	Matrix U(n,n);
//	struct LU temp_lu = {m, m};

	for(int i = 0; i < (n - 1); i++)
	{
		for(int k = i; k < min(m+i+1,n); k++)
		{
			U(i,k) = A(i,k);
			L(k,i) = A(k,i) / U(i,i);
		}
		for(int j = i+1; j < min(m+i+1,n); j++)
		{
			for(int k = i+1; k < min(m+i+1,n); k++)
			{
				A(j,k) = A(j,k) - L(j,i) * U(i,k);
			}
		}
	}
	L(n-1,n-1) = 1;
	U(n-1,n-1) = A(n-1,n-1);

	return boost::make_tuple(L,U);
}

boost::tuple<Matrix, Matrix, Matrix> lu_row_pivoting(Matrix A)
{
	int n = A.Size1();
	Matrix P(n,n);
	Matrix L(n,n);
	Matrix U(n,n);

	P.identity_matrix();	// Generate identity matrix for P
//	struct PLU temp_plu = {m, m, m};

	for(int i = 0; i < n-1; i++)
	{
		int i_max = A.max_abs_entry_row_index(i, n - 1, i);
		A.row_pivot(i, i_max, i, n-1);
		P.row_pivot(i, i_max, 0, n-1);

		if(i > 0)
		{
			L.row_pivot(i, i_max, 0, i-1);
		}

		for(int j = i; j < n; j++)
		{
			L(j,i) = A(j,i)/A(i,i);
			U(i,j) = A(i,j);
		}

		for(int j = i+1; j < n; j++)
		{	for(int k = i+1; k < n; k++)
			{
				A(j,k) = A(j,k) - L(j,i)*U(i,k);
			}
		}
	}
	L(n-1,n-1) = 1;
	U(n-1,n-1) = A(n-1,n-1);
	
	return boost::make_tuple(P, L, U);
}


/*
boost::tuple<Matrix, Matrix, Matrix> lu_row_pivoting_banded(Matrix A, int m)
{
	int n = A.Size1();
	Matrix P(n,n);
	Matrix L(n,n);
	Matrix U(n,n);

	P.identity_matrix();	// Generate identity matrix for P
//	struct PLU temp_plu = {m, m, m};

	for(int i = 0; i < n-1; i++)
	{
		int i_max = A.max_abs_entry_row_index(i, n - 1, i);
		A.row_pivot(i, i_max, i, n-1);
		P.row_pivot(i, i_max, 0, n-1);

		if(i > 0)
		{
			L.row_pivot(i, i_max, 0, i-1);
		}

		for(int j = i; j < min(m+i+1,n); j++)
		{
			L(j,i) = A(j,i)/A(i,i);
			U(i,j) = A(i,j);
		}

		for(int j = i+1; j < min(m+i+1, n); j++)
		{	for(int k = i+1; k < min(m+i+1,n); k++)
			{
				A(j,k) = A(j,k) - L(j,i)*U(i,k);
			}
		}
	}
	L(n-1,n-1) = 1;
	U(n-1,n-1) = A(n-1,n-1);
	
	return boost::make_tuple(P, L, U);
}
*/

Matrix cholesky(Matrix A)
{
	int n = A.Size1();
	Matrix U(n,n);

	for(int i = 0; i < n-1; i++)
	{
		U(i,i) = sqrt(A(i,i));
		
		for(int k = i+1; k < n; k++)
		{
			U(i,k) = A(i,k) / U(i,i);
		}

		for(int j = i+1; j < n; j++)
		{
			for(int k = j; k < n; k++)
			{
				A(j,k) = A(j,k) - U(i,j) * U(i,k);
			}
		}

	}
	U(n-1,n-1) = sqrt(A(n-1,n-1));
	
	return U; 
}

Matrix cholesky_tridiag_spd(Matrix A)
{
	int n = A.Size1();
	Matrix U(n,n);

	for(int i = 0; i < n-1; i++)
	{
		U(i,i) = sqrt(A(i,i));
		U(i,i+1) = A(i,i+1)/U(i,i);
		A(i+1,i+1) = A(i+1,i+1) - U(i,i+1)*U(i,i+1);
	}
	U(n-1,n-1) = sqrt(A(n-1,n-1));

	return U;
}

Matrix cholesky_banded(Matrix A)
{
	int n = A.Size1();
	Matrix U(n,n);

	int j = 1;
	for(; A(0,n-j) == 0; j++);				// Calculate the band
	j = j - 1;								// This is the number of 0
	int m = n - j - 1;

	for(int i = 0; i < n-1; i++)
	{
		U(i,i) = sqrt(A(i,i));
		
		for(int k = i+1; k < min(m+i+1,n); k++)
		{
			U(i,k) = A(i,k) / U(i,i);
		}

		for(int j = i+1; j < min(m+i+1,n); j++)
		{
			for(int k = j; k < min(m+i+1,n); k++)
			{
				A(j,k) = A(j,k) - U(i,j) * U(i,k);
			}
		}

	}
	U(n-1,n-1) = sqrt(A(n-1,n-1));
	
	return U; 
}