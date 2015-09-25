// This file was about solving linear system using LU and cholesky decomposition
// splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#include "Matrix_Decomposition.hpp"
#include "Solving_Linear_System.hpp"
#include "Forward_Backward_subst.hpp"
#include "Read_Write_Csv.hpp"

Matrix linear_solve_LU_no_pivoting(const Matrix& A, const Matrix& vector_b)
{
	int n = A.Size1();
	Matrix L(n,n);
	Matrix U(n,n);
	boost::tie(L, U) = lu_no_pivoting(A);	// Calculate lu decomposition, and assign the result to L and U

	Matrix y = forward_subst(L, vector_b);
	Matrix x = backward_subst(U, y);

	return x;
}

Matrix linear_solve_LU_no_pivoting_tridiag_spd(const Matrix& A, const Matrix& vector_b)
{
	int n = A.Size1();
	Matrix L(n,n);
	Matrix U(n,n);

	boost::tie(L, U) = lu_no_pivoting_tridiag(A);

	Matrix y = forward_subst_bidiag(L, vector_b);
	Matrix x = backward_subst_bidiag(U, y);

	return x;
}

Matrix linear_solve_cholesky(const Matrix& A, const Matrix& vector_b)
{
	Matrix U = cholesky(A);

	Matrix y = forward_subst(U.Trans(),vector_b);
	Matrix x = backward_subst(U,y);
	
	return x;
}

Matrix linear_solve_cholesky_tridiag_spd(const Matrix& A, const Matrix& vector_b)
{
	Matrix U = cholesky_tridiag_spd(A);	
	Matrix y = forward_subst_bidiag(U.Trans(), vector_b);
	Matrix x = backward_subst_bidiag(U, y);

	return x;
}

Matrix linear_solve_cholesky_banded(const Matrix& A, const Matrix& vector_b)
{
	Matrix U = cholesky_banded(A);	
	Matrix y = forward_subst_banded(U.Trans(), vector_b);
	Matrix x = backward_subst_banded(U, y);

	return x;
}



boost::tuple<Matrix, int, double> jacobi_iter_residual_based(const Matrix& A, const Matrix& b, const Matrix& x0, double tol)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_inv_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_inv_A(j,k) = 1 / A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x = x0;
	Matrix r0 = b - (A * x0);
	Matrix r = r0;
	double stop_iter_resid = tol * r0.norm();
	Matrix b_new = D_inv_A * b;
	int ic= 0;

	while(r.norm() > stop_iter_resid)
	{
		x = b_new - D_inv_A * (L_A * x + U_A * x);
		r = b - (A * x);
		ic++;
		if(ic <= 3) WriteMatrix(x, "jacobi_first_3.csv");
	}

	return boost::make_tuple(x, ic, r.norm());
}

boost::tuple<Matrix, int> jacobi_iter_consecutive_appro(const Matrix& A, const Matrix& b, const Matrix& x0, double tol)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_inv_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_inv_A(j,k) = 1 / A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}

	Matrix x_old = x0;

	Matrix b_new = D_inv_A * b;
	Matrix diff(n,1);
	diff(n-1,0) = 1;
	int ic= 0;
	Matrix x_new = x0;

	while(diff.norm() > tol)
	{
		x_new = b_new - D_inv_A * (L_A * x_old + U_A * x_old);
		diff = x_new - x_old;
		x_old = x_new;
		ic++;
	}

	return boost::make_tuple(x_new, ic);
}


boost::tuple<Matrix, int, double> gauss_siedel_iter_residual_based(const Matrix& A, const Matrix& b, const Matrix& x0, double tol)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x = x0;
	Matrix r0 = b - (A * x0);
	Matrix r = r0;
	double stop_iter_resid = tol * r0.norm();
	Matrix b_new = forward_subst(D_A + L_A, b);
	int ic = 0;

	while(r.norm() > stop_iter_resid)
	{
		x = b_new - forward_subst(D_A + L_A, U_A * x);
		r = b -(A * x);
		ic++;
		if(ic <= 3) WriteMatrix(x, "gauss_first_3.csv");
	}
	
	return boost::make_tuple(x, ic, r.norm());
}

boost::tuple<Matrix, int, double> gauss_siedel_iter_residual_based_tridiag(const Matrix& A, const Matrix& b, const Matrix& x0, double tol)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x = x0;
	Matrix r0 = b - (A * x0);
	Matrix r = r0;
	double stop_iter_resid = tol * r0.norm();
	Matrix b_new = forward_subst_bidiag(D_A + L_A, b);
	int ic = 0;

	while(r.norm() > stop_iter_resid)
	{
		x = b_new - forward_subst_bidiag(D_A + L_A, U_A * x);
		r = b -(A * x);
		ic++;
	}
	
	return boost::make_tuple(x, ic, r.norm());
}

boost::tuple<Matrix, int, double> gauss_siedel_iter_residual_based_banded(const Matrix& A, const Matrix& b, const Matrix& x0, double tol)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x = x0;
	Matrix r0 = b - (A * x0);
	Matrix r = r0;
	double stop_iter_resid = tol * r0.norm();
	Matrix b_new = forward_subst_banded(D_A + L_A, b);
	int ic = 0;

	while(r.norm() > stop_iter_resid)
	{
		x = b_new - forward_subst_banded(D_A + L_A, U_A * x);
		r = b -(A * x);
		ic++;
	}
	
	return boost::make_tuple(x, ic, r.norm());
}

boost::tuple<Matrix, int> gauss_siedel_iter_consecutive_appro(const Matrix& A, const Matrix& b, const Matrix& x0, double tol)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x_old = x0;
	Matrix b_new = forward_subst(D_A + L_A, b);
	int ic = 0;
	Matrix x_new = x0;
	Matrix diff(n,1);
	diff(n-1,0) = 1;

	while(diff.norm() > tol)
	{
		x_new = b_new - forward_subst(D_A + L_A, U_A * x_old);
		diff = x_new - x_old;
		x_old = x_new;
		ic++;
	}
	
	return boost::make_tuple(x_new, ic);
}


boost::tuple<Matrix, int, double> sor_iter_residual_based(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x = x0;
	Matrix r0 = b - (A * x0);
	Matrix r = r0;
	double stop_iter_resid = tol * r0.norm();
	Matrix b_new = omega * forward_subst(D_A + omega * L_A, b);
	int ic = 0;
	
	while(r.norm() > stop_iter_resid)
	{
		x = forward_subst(D_A + (omega * L_A), (1 - omega) * (D_A * x) - (omega * U_A * x)) + b_new;
		r = b -(A * x);
		ic++;
		if(ic <= 3) WriteMatrix(x, "sor_first_3.csv");

	}
	
	return boost::make_tuple(x, ic, r.norm());
}

boost::tuple<Matrix, int, double> sor_iter_residual_based_tridiag(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x = x0;
	Matrix r0 = b - (A * x0);
	Matrix r = r0;
	double stop_iter_resid = tol * r0.norm();
	Matrix b_new = omega * forward_subst_bidiag(D_A + omega * L_A, b);
	int ic = 0;
	
	while(r.norm() > stop_iter_resid)
	{
		x = forward_subst_bidiag(D_A + (omega * L_A), (1 - omega) * (D_A * x) - (omega * U_A * x)) + b_new;
		r = b -(A * x);
		ic++;
	}
	
	return boost::make_tuple(x, ic, r.norm());
}

boost::tuple<Matrix, int, double> sor_iter_residual_based_banded(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x = x0;
	Matrix r0 = b - (A * x0);
	Matrix r = r0;
	double stop_iter_resid = tol * r0.norm();
	Matrix b_new = omega * forward_subst_banded(D_A + omega * L_A, b);
	int ic = 0;
	
	while(r.norm() > stop_iter_resid)
	{
		x = forward_subst_banded(D_A + (omega * L_A), (1 - omega) * (D_A * x) - (omega * U_A * x)) + b_new;
		r = b -(A * x);
		ic++;
	}
	
	return boost::make_tuple(x, ic,  r.norm());
}

boost::tuple<Matrix, int> sor_iter_consecutive_appro(const Matrix& A, const Matrix& b, const Matrix& x0, double tol, double omega)
{
	int n = A.Size1();
	Matrix L_A(n,n), U_A(n,n), D_A(n,n);
	for(int j = 0; j < n; j++)
	{
		for(int k = 0; k < n; k++)
		{
			if(k < j)
			{
				L_A(j,k) = A(j,k);
			}
			if(k == j)
			{
				D_A(j,k) = A(j,k);
			}
			if(k > j)
			{
				U_A(j,k) = A(j,k);
			}
		}
	}	
	Matrix x_old = x0;
	Matrix b_new = omega * forward_subst(D_A + omega * L_A, b);
	int ic = 0;
	Matrix diff(n,1);
	diff(n-1,0) = 1;
	Matrix x_new = x0;
	while(diff.norm() > tol)
	{
		x_new = forward_subst(D_A + (omega * L_A), (1 - omega) * (D_A * x_old) - (omega * U_A * x_old)) + b_new;
		diff = x_new - x_old;
		x_old = x_new;
		ic++;
	}
	
	return boost::make_tuple(x_new, ic);
}

