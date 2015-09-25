// This file was about cublic spline interpolation
// splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#ifndef CUBIC_SPLINE_HPP
#define CUBIC_SPLINE_HPP

#include "Matrix.hpp"
#include "Solving_Linear_System.hpp"
#include <boost/tuple/tuple.hpp>
#include "Read_Write_Csv.hpp"
// Run time Error!!!初步怀疑是w指针取【-1】和【n-1】处发生内存溢出！！！！！!
// 经验证，该猜想正确。该算法处理为将w赋予一个新的（n+1，1）维矩阵！！！
// Note: there is a lot different than the pseudocode
boost::tuple<Matrix, Matrix, Matrix, Matrix> cubic_spline_interpo(const Matrix& x, const Matrix& v)
{
	int n = (x.Size1() - 1);

	Matrix z(n,1);
	z(0,0) = 0;

	Matrix vector_a(n+1,1);
	Matrix vector_b(n+1,1);
	Matrix vector_c(n+1,1);
	Matrix vector_d(n+1,1);

	vector_a(0,0) = vector_b(0,0) = 0;
	vector_c(0,0) = vector_d(0,0) = 0;

	for(int i = 1; i <= n-1; i++)
	{
		double temp1 = (v(i+1,0) - v(i,0))/(x(i+1,0) - x(i,0));
		double temp2 = (v(i,0) - v(i-1,0))/(x(i,0) - x(i-1,0));
		z(i,0) = 6 * (temp1 - temp2);
	}

	Matrix M(n-1,n-1);

	for(int i = 1; i <= n-1; i++)
	{
		M(i-1,i-1) = 2 * (x(i+1,0) - x(i-1,0));
	}
	for(int i = 1; i <= n-2; i++)
	{
		M(i-1,i) = (x(i+1,0) - x(i,0));
	}
	for(int i = 2; i <= n-1; i++)
	{
		M(i-1,i-2) = (x(i,0) - x(i-1,0));
	}

	Matrix new_z(n-1,1);
	for(int i = 0; i < n-1; i++)
	{
		new_z(i,0) = z(i+1,0);
	}

	WriteMatrix(M, "M.csv");
	Matrix w = linear_solve_LU_no_pivoting_tridiag_spd(M, new_z);
	Matrix new_w(n+1,1);
	for(int i = 1; i <= n-1; i++)
	{
		new_w(i,0) = w(i-1,0);
	}
	new_w(0,0) = 0; new_w(n,0) = 0;

	for(int i = 1; i <= n; i++)
	{
		double temp1 = (new_w(i-1,0)*x(i,0) - new_w(i,0)*x(i-1,0));
		double temp2 = (x(i,0) - x(i-1,0));

		vector_c(i,0) = 0.5 * temp1 / temp2;

		double temp3 = (new_w(i,0) - new_w(i-1,0));
		double temp4 = (x(i,0) - x(i-1,0));

		vector_d(i,0) = temp3 / temp4 / 6;
	}

	double* q = new double [n];
	double* r = new double [n+1];
	r[0] = 0;

	for(int i = 1; i <= n; i++)
	{
		q[i-1] = v(i-1,0) - vector_c(i,0) * x(i-1,0) * x(i-1,0) 
				- vector_d(i,0) * x(i-1,0) * x(i-1,0) * x(i-1,0);
		
		r[i] = v(i,0) - vector_c(i,0) * x(i,0) * x(i,0)
				- vector_d(i,0) * x(i,0) * x(i,0) * x(i,0);
	}

	for(int i = 1; i <= n; i++)
	{
		double temp1 = (q[i-1]*x(i,0) - r[i]*x(i-1,0));
		double temp2 = (x(i,0) - x(i-1,0));

		vector_a(i,0) = temp1 / temp2;

		double temp3 = r[i] - q[i-1];
		double temp4 = x(i,0) - x(i-1,0);

		vector_b(i,0) = temp3 / temp4;
	}

	delete [] q;
	delete [] r;

	return boost::make_tuple(vector_a, vector_b, vector_c, vector_d);
}

#endif