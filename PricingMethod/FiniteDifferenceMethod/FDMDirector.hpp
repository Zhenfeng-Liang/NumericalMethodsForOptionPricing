// This file was created to direct to use FDMTOHeatPDE class to price option.
//
// Zhenfeng Liang 
//
// 11/28/2014

// NOTE!!!!!! CANNOT CALCULATE SEVERAL FDMS AT THE SAME TIME!!!!!SINCE WE ARE USING NAMESPACE TO STORE VARIABLES. BUT
// CONSIDER TO CHANGE TO THE FUNCTION POINTER AND USE THE STRUCT TO INITIALIZE THE BOUNDARY CONDITION.

#ifndef FDMDIRECTOR_HPP
#define FDMDIRECTOR_HPP

#include <memory>
#include <string>
#include <functional>


#include "FDMToHeatPDE.hpp"
#include "FDMGlobal.hpp"

#include "../../Option/Option.hpp"

using namespace Derivatives;

class Matrix;

typedef std::function<double (double x)> Boundary_func;
typedef std::function<double (double x, double t)> Exact_func;
typedef std::shared_ptr<FDMToHeatPDE> FDMHeatPDEPtr;
typedef std::shared_ptr<Option> OptionPtr;


class FDMDirector
{
private:
	// Given by outside
	std::shared_ptr<Option> _op_ptr;
	int _M;
	double _alpha_temp;
	std::string _fdm_method;

	// Given by outside according to the Option type and put call type.
	Boundary_func f_begin;
	Boundary_func g_left;
	Boundary_func g_right;
	Exact_func u_exact;
	FDMHeatPDEPtr fdmpde_ptr;

	// Calculate in the constructor
	int _N;
	double x_left;
	double x_right;
	double a;
	double b;
	double tao_final;
	double delta_tao;
	double delta_x;
	double x_compute;
	double alpha;

	// For Barrier option
	int N_left;
	int N_right;

	// For American Option
	Matrix early_ex_premium();

	// Initialize the FDM parameters according to the Option type
	void Euro_Amer_init_();
	void DAO_init_();
	void UAO_init_();

	void DAO_init_on_the_grid();

	// Calculate approximate value according to the Option type
	double cal_approx_not_on_the_grid(std::string solve_method);
	double cal_approx_on_the_grid(std::string solve_method);
	
	Vec cal_greeks_not_on_the_grid(std::string solve_method);
	Vec cal_greeks_on_the_grid(std::string solve_method);

public:
	FDMDirector(std::shared_ptr<Option> op_ptr, int M, double alpha_temp, std::string fdm_method);

	double alpha_real() const;

	Matrix u_approx(std::string solve_method);

	Vec approxi_1(std::string solve_method);

	Vec approxi_2(std::string solve_method);

	double error_RMS(std::string solve_method);

	Vec CalGreeks(std::string solve_method);

	Vec Variance_Reduction(std::string solve_method);

	Matrix early_ex_domain();

	// Output the N, x_left, x_right calculated
	Matrix N_x_left_x_right();
};
#endif