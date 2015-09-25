// This file was created to be a parent class of Foward Euler, Backward Euler, Crank-Nicolson
//
// Zhenfeng Liang
//
// 11/18/2014 in New York ,NY

#ifndef FDMTOHEATPDE_HPP
#define FDMTOHEATPDE_HPP

#include <functional>
typedef std::function<double (double x)> Boundary_func;
typedef std::function<double (double x, double t)> Exact_func;
class Matrix;

namespace Derivatives
{
	class FDMToHeatPDE
	{
	private:
		int _M;
		int _N;
		double _t0;
		double _t_final;
		double _x_left;
		double _x_right;
		Boundary_func _f_begin;
		Boundary_func _g_left;
		Boundary_func _g_right;
		Exact_func _u_exact;
	public:
		FDMToHeatPDE();
		FDMToHeatPDE(int M, int N, double t0, double t_final, double x_left, double x_right, 
			Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, Exact_func _u_exact);
		
		FDMToHeatPDE(const FDMToHeatPDE& fdm);
		virtual ~FDMToHeatPDE();

		// Assignment
		FDMToHeatPDE& operator = (const FDMToHeatPDE& source);
		
		int M() const	{return _M;}
		int N() const	{return _N;}
		double t0() const	{return _t0;}
		double t_final() const	{return _t_final;}
		double x_left() const	{return _x_left;}
		double x_right() const	{return _x_right;}
		Boundary_func f_begin() const	{return _f_begin;}
		Boundary_func g_left() const	{return _g_left;}
		Boundary_func g_right() const	{return _g_right;}
		Exact_func u_exact() const	{return _u_exact;}

		// PVMF
		// solve_method is the method used to solve the matrix, SOR or LU(symetric tridiagonal LU without pivoting).
		// Foward Euler don't need to use this method.
		virtual Matrix u_approx(std::string solve_method, std::string optype, Matrix early_ex_premium) const = 0;

		double max_pointwise_error(std::string solve_method, std::string optype) const;
		double error_RMS(std::string solve_method, std::string optype) const;

		// Return the basic info of the MC
		virtual std::string Who() = 0;
		
	};
}

#endif