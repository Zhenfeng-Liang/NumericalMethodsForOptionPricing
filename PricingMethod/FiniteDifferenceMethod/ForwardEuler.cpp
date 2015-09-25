// This file was created to be class of Forward Euler
//
// Zhenfeng Liang
//
// 11/18/2014 in New York ,NY

#include <iostream>
#include "ForwardEuler.hpp"
#include "FDMGlobal.hpp"
#include "../../NumericalLinearAlgebra/Matrix.hpp"

namespace Derivatives
{
	ForwardEuler::ForwardEuler() : FDMToHeatPDE() {}

	ForwardEuler::ForwardEuler(int M, int N, double t0, double t_final, double x_left, double x_right, 
		Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, Exact_func u_exact)
		: FDMToHeatPDE(M, N, t0, t_final, x_left, x_right, f_begin, g_left, g_right, u_exact) {}
	
	ForwardEuler::ForwardEuler(const ForwardEuler& source) : FDMToHeatPDE(source) {}

	ForwardEuler::~ForwardEuler(){}

	// Assignment
	ForwardEuler& ForwardEuler::operator = (const ForwardEuler& source)
	{
		if (this == &source) { std::cout << "These two Forward Euler are the same" << std::endl; return *this; }
		FDMToHeatPDE::operator = (source);
		return *this;
	}
		
	Matrix ForwardEuler::u_approx(std::string solve_method, std::string optype, Matrix early_ex_premium) const
	{
		Matrix result = FDM::ForwardEulerPricer(M(), N(), t0(), t_final(), x_left(), x_right(),
			f_begin(), g_left(), g_right(), optype, early_ex_premium);
		return result;
	}

	// Return the basic info of the Option
	std::string ForwardEuler::Who(){ return "I am a Forward Euler Method.";}		
}