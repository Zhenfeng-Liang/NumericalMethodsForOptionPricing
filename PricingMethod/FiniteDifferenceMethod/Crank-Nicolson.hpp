// This file was created to be class of Crank-Nicolson
//
// Zhenfeng Liang
//
// 11/18/2014 in New York ,NY

#ifndef CRANKNICOLSON_HPP
#define CRANKNICOLSON_HPP

#include "FDMToHeatPDE.hpp"

namespace Derivatives
{
	class CrankNicolson : public FDMToHeatPDE
	{
	public:
		CrankNicolson();

		CrankNicolson(int M, int N, double t0, double t_final, double x_left, double x_right, 
			Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, Exact_func u_exact);
		
		CrankNicolson(const CrankNicolson& source);
		
		virtual ~CrankNicolson();

		// Assignment
		CrankNicolson& operator = (const CrankNicolson& source);
		
		virtual Matrix u_approx(std::string solve_method, std::string optype, Matrix early_ex_premium) const;

		// Return the basic info of the Option
		virtual std::string Who();	
	};
}

#endif