// This file was created to be a parent class of Foward Euler, Backward Euler, Crank-Nicolson
//
// Zhenfeng Liang
//
// 11/18/2014 in New York ,NY


#include "FDMToHeatPDE.hpp"
#include "FDMGlobal.hpp"
#include "../../NumericalLinearAlgebra/Matrix.hpp"
#include <iostream>

namespace Derivatives
{
	FDMToHeatPDE::FDMToHeatPDE():_M(8),_N(8),_t0(0),_t_final(1),_x_left(-2),_x_right(2),
		_f_begin([] (double x) {return exp(x);}), _g_left([] (double tao) {return exp(tao - 2);}), 
		_g_right([] (double tao) {return exp(tao + 2);}), _u_exact([] (double x, double t) {return exp(x+t);})
	{
	}

	FDMToHeatPDE::FDMToHeatPDE(int M, int N, double t0, double t_final, double x_left, double x_right, 
			Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, Exact_func u_exact):_M(M),_N(N),_t0(t0),_t_final(t_final),
			_x_left(x_left),_x_right(x_right), _f_begin(f_begin), _g_left(g_left), _g_right(g_right), _u_exact(u_exact)
	{
	}

	FDMToHeatPDE::FDMToHeatPDE(const FDMToHeatPDE& fdm):_M(fdm._M),_N(fdm._N),_t0(fdm._t0),_t_final(fdm._t_final),
		_x_left(fdm._x_left),_x_right(fdm._x_right), _f_begin(fdm._f_begin), _g_left(fdm._g_left), _g_right(fdm._g_right),
		_u_exact(fdm._u_exact)
	{
	}

	FDMToHeatPDE::~FDMToHeatPDE()
	{
	}

	// Assignment
	FDMToHeatPDE& FDMToHeatPDE::operator = (const FDMToHeatPDE& source)
	{
		if (this == &source) 
		{
			std::cout << "These two FDM Method to Heat PDE are the same" << std::endl;
			return *this;
		}
		
		_M = source._M;
		_N = source._N;
		_t0 = source._t0;
		_t_final = source._t_final;
		_x_left = source._x_left;
		_x_right = source._x_right;
		_f_begin = source._f_begin;
		_g_left = source._g_left;
		_g_right = source._g_right;
		_u_exact = source._u_exact;

		return *this;
	}

	double FDMToHeatPDE::max_pointwise_error(std::string solve_method, std::string optype) const
	{
		Matrix dummy(_M+1, _N+1);
		Matrix fdm_result = u_approx(solve_method, optype, dummy);
		double maxerror = 0;
		Vec x = FDM::Mesh_vec(_x_left, _x_right, _N);
		for (int i = 1; i <= _N-1; i++)
		{
			double temp = std::abs(fdm_result(_M, i) - _u_exact(x[i], _t_final));
			maxerror = std::max<double> (temp, maxerror);
		}
		return maxerror;
	}

	double FDMToHeatPDE::error_RMS(std::string solve_method, std::string optype) const
	{
		Matrix dummy(_M+1, _N+1);
		Matrix fdm_result = u_approx(solve_method, optype, dummy);
		double rms_error = 0;
		Vec x = FDM::Mesh_vec(_x_left, _x_right, _N);
		for(int i = 0; i <= _N; i++)
		{
			double temp1 = _u_exact(x[i], _t_final);
			double temp2 = fdm_result(_M, i) - temp1;
			rms_error += temp2 * temp2 / (temp1 * temp1);
		}

		rms_error = std::sqrt(rms_error / (_N+1));
		return rms_error;
	}
}
