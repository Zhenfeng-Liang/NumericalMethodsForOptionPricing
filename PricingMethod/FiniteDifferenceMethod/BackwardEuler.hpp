// This file was created to be class of Backward Euler
//
// Zhenfeng Liang
//
// 11/18/2014 in New York ,NY

#ifndef BACKWARDEULER_HPP
#define BACKWARDEULER_HPP

#include "FDMToHeatPDE.hpp"

namespace Derivatives
{
	class BackwardEuler : public FDMToHeatPDE
	{
	public:
		BackwardEuler();

		BackwardEuler(int M, int N, double t0, double t_final, double x_left, double x_right, 
			Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, Exact_func u_exact);
		
		BackwardEuler(const BackwardEuler& source);
		
		virtual ~BackwardEuler();

		// Assignment
		BackwardEuler& operator = (const BackwardEuler& source);
		
		virtual Matrix u_approx(std::string solve_method, std::string optype, Matrix early_ex_premium) const;

		// Return the basic info of the Option
		virtual std::string Who();	
	};
}

#endif