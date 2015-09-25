// This file was about least square method and its application to
// implied volatility splitted from the NLA big file
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY


#ifndef LEAST_SQUARE_HPP
#define LEAST_SQUARE_HPP

#define _USE_MATH_DEFINES
#include "Matrix.hpp"
#include "Solving_Linear_System.hpp"
#include <boost/tuple/tuple.hpp>
#include <boost/math/distributions/normal.hpp>

using namespace boost::math;

// OLS Calculate the coeffieient, A is the data and return x,as the coeffient vector.
Matrix least_squares(const Matrix& A, const Matrix& y)
{
	int n = A.Size2();
	Matrix x(n,1);
	x = linear_solve_cholesky(A.Trans()*A, A.Trans()*y);

	return x;
}

boost::tuple<Matrix, Matrix> least_squares_imp_volatility(const Matrix& vector_C, const Matrix& vector_P, const Matrix& vector_K, double S, double T)
{
	int n = vector_C.Size1();
	Matrix sig_c(n,1);
	Matrix sig_p(n,1);

	Matrix y = vector_C - vector_P;
	Matrix A(n, 2);

	for(int j = 0; j < n; j++)
	{
		A(j,0) = 1;
		A(j,1) = - vector_K(j,0);
	}

	Matrix x = least_squares(A, y);
	double PVF = x(0,0);
	double disc = x(1,0);
	
	for(int j = 0; j < n; j++)
	{
		double x_call_new = 0.25;
		double x_call_old = x_call_new - 1;

		while(abs(x_call_new - x_call_old) > 1e-6)
		{
			x_call_old = x_call_new;
			
			double temp1 = log(PVF / vector_K(j,0) / disc) / (x_call_old * sqrt(T));
			double d1 = temp1 + (x_call_old * sqrt(T)) / 2;
			double d2 = temp1 - (x_call_old * sqrt(T)) / 2;
			
			normal_distribution<float> myNormal;
			double N_d1 = cdf(myNormal, d1);
			double N_d2 = cdf(myNormal, d2);

			double F_c = PVF * N_d1 - vector_K(j,0) * disc * N_d2 - vector_C(j,0);
			double f_c = PVF * sqrt(T / (2 * M_PI)) * exp(- d1 * d1 / 2);

			x_call_new = x_call_old - F_c/f_c;
		}
		sig_c(j,0) = x_call_new;

		double x_put_new = 0.25;
		double x_put_old = x_put_new - 1;

		while(abs(x_put_new - x_put_old) > 1e-6)
		{
			x_put_old = x_put_new;
			
			double temp1 = log(PVF / vector_K(j,0) / disc) / (x_put_old * sqrt(T));
			double d1 = temp1 + (x_put_old * sqrt(T)) / 2;
			double d2 = temp1 - (x_put_old * sqrt(T)) / 2;
			
			normal_distribution<float> myNormal;
			double N_d1 = cdf(myNormal, -d1);
			double N_d2 = cdf(myNormal, -d2);

			double F_p = vector_K(j,0) * disc * N_d2 - PVF * N_d1 -  vector_P(j,0);
			double f_p = PVF * sqrt(T / (2 * M_PI)) * exp(- d1 * d1 / 2);

			x_put_new = x_put_old - F_p/f_p;
		}
		sig_p(j,0) = x_put_new;
	}

	return boost::make_tuple(sig_c, sig_p);
}

#endif