// This file was created to be class of Forward Euler
//
// Zhenfeng Liang
//
// 11/18/2014 in New York ,NY

#ifndef FORWARDEULER_HPP
#define FORWARDEULER_HPP

#include "FDMToHeatPDE.hpp"

namespace Derivatives
{
	class ForwardEuler : public FDMToHeatPDE
	{
	public:
		ForwardEuler();

		ForwardEuler(int M, int N, double t0, double t_final, double x_left, double x_right, 
			Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, Exact_func u_exact);
		
		ForwardEuler(const ForwardEuler& source);
		
		virtual ~ForwardEuler();

		// Assignment
		ForwardEuler& operator = (const ForwardEuler& source);
		
		virtual Matrix u_approx(std::string solve_method, std::string optype, Matrix early_ex_premium) const;

		// Return the basic info of the Option
		virtual std::string Who();	
	};
}

#endif