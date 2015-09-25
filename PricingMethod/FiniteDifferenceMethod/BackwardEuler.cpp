// This file was created to be class of Backward Euler
//
// Zhenfeng Liang
//
// 11/18/2014 in New York ,NY

#include <iostream>
#include "BackwardEuler.hpp"
#include "FDMGlobal.hpp"
#include "../../NumericalLinearAlgebra/Matrix.hpp"

namespace Derivatives
{
	BackwardEuler::BackwardEuler() : FDMToHeatPDE() {}

	BackwardEuler::BackwardEuler(int M, int N, double t0, double t_final, double x_left, double x_right, 
		Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, Exact_func u_exact)
		: FDMToHeatPDE(M, N, t0, t_final, x_left, x_right, f_begin, g_left, g_right, u_exact) {}
	
	BackwardEuler::BackwardEuler(const BackwardEuler& source) : FDMToHeatPDE(source) {}

	BackwardEuler::~BackwardEuler(){}

	// Assignment
	BackwardEuler& BackwardEuler::operator = (const BackwardEuler& source)
	{
		if (this == &source) { std::cout << "These two Backward Euler are the same" << std::endl; return *this; }
		FDMToHeatPDE::operator = (source);
		return *this;
	}
		
	Matrix BackwardEuler::u_approx(std::string solve_method, std::string optype, Matrix early_ex_premium) const
	{

		Matrix result = FDM::BackwardEulerPricer(M(), N(), t0(), t_final(), x_left(), x_right(),
			f_begin(), g_left(), g_right(), solve_method, optype, early_ex_premium);
		return result;
	}

	// Return the basic info of the Option
	std::string BackwardEuler::Who(){ return "I am a Backward Euler Method.";}		
}