// This file was created to implement the global function of the FDM methods.
//
// Zhenfeng Liang
//
// 11/18/2014

#include <functional>
#include <vector>

class Matrix;
typedef std::function<double (double x)> Boundary_func;
typedef std::vector<double> Vec;

namespace Derivatives
{
	namespace FDM
	{
		Vec Mesh_vec(double x_left, double x_right, int num_interval);

		Matrix ForwardEulerPricer(int M, int N, double t0, double t_final, double x_left, double x_right, 
				Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, std::string optype, Matrix early_ex_premium);

		Matrix BackwardEulerPricer(int M, int N, double t0, double t_final, double x_left, double x_right, Boundary_func 
			f_begin, Boundary_func g_left, Boundary_func g_right, std::string solve_method, std::string optype, Matrix early_ex_premium);

		Matrix CrankNicolsonPricer(int M, int N, double t0, double t_final, double x_left, double x_right, Boundary_func 
			f_begin, Boundary_func g_left, Boundary_func g_right, std::string solve_method, std::string optype, Matrix early_ex_premium);
	}
}