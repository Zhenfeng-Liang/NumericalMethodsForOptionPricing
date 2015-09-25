// This file was created to implement the global function of the FDM methods.
//
// Zhenfeng Liang
//
// 11/18/2014

#include "../../NumericalLinearAlgebra/Matrix.hpp"
#include "../../NumericalLinearAlgebra/Solving_Linear_System.hpp"
#include "FDMGlobal.hpp"
#include <vector>


namespace Derivatives
{
	namespace FDM
	{
		Matrix SOR_entry_by_entry_American(Matrix A, Matrix b, Matrix x0, double tol, double omega)
		{ // x0 is the early_ex_premium for each row.

			int p = A.Size1();
			Matrix x_old = x0;
			Matrix x_new(p, 1);
			Matrix diff(p,1);
			diff(p-1,0) = 1;

			while(diff.norm() > tol)
			{
				for(int j = 0; j < p; j++)
				{
					double temp1 = 0;
					double temp2 = 0;
					for(int k = 0; k <= j - 1; k++) { temp1 += A(j,k) * x_new(k, 0); }
					for(int k = j + 1; k <= p-1; k++) { temp2 += A(j,k) * x_old(k,0); }

					x_new(j,0) = (1 - omega) * x_old(j,0) - omega * (temp1 + temp2) / A(j,j) + omega * b(j,0) / A(j,j);

					// x0 is the early_ex_premium for each row, so I just compare with x0.
					x_new(j,0) = std::max(x_new(j,0), x0(j,0));
				}
				diff = x_new - x_old;
				x_old = x_new;
			}
			return x_new;
		}

		Vec Mesh_vec(double x_left, double x_right, int num_interval)
		{
			double delta_x = (x_right - x_left) / num_interval;
			Vec result;
			result.push_back(x_left);
			for(int count = 1; count <= (num_interval-1); count++) { result.push_back(x_left + count * delta_x);}
			result.push_back(x_right);
			return result;
		}

		Matrix ForwardEulerPricer(int M, int N, double t0, double t_final, double x_left, double x_right, 
			Boundary_func f_begin, Boundary_func g_left, Boundary_func g_right, std::string optype, Matrix early_ex_premium)
		{
			double delta_t = (t_final - t0) / M;
			double delta_x = (x_right - x_left) / N;
			Vec x = Mesh_vec(x_left, x_right, N);
			Vec t = Mesh_vec(t0, t_final, M);
			double alpha = delta_t / (delta_x * delta_x);

			Matrix result(M+1, N+1);

			Matrix u_old(N-1, 1);
			Matrix u_new(N-1, 1);
	
			// Initialize final matrix
			result(0,0) = g_left(t0); 
			result(0,N) = g_right(t0);

			for(int i = 0; i < u_old.Size1(); i++) 
			{// Initialize u when t=0, i.e u^0 and the final matrix.

				result(0,i+1) = u_old(i,0) = f_begin(x[i+1]);
			}
		
			Matrix A(N-1, N-1);
			for(int i = 0; i < N-1; i++)
			{// Initialize Matrix A
				A(i,i) = 1-2*alpha;
				if(i < N-2) A(i, i+1) = alpha;
				if(i > 0) A(i, i-1) = alpha;
			}

			for(int m = 0; m <= M-1; m++, u_old = u_new)
			{// Start to calculate Matrix 

				Matrix b(N-1,1);
				b(0,0) = alpha * g_left(t[m]);
				b(N-2, 0) = alpha * g_right(t[m]);

				u_new = A * u_old + b;

				if(optype == "American") {
					for(int i = 0; i < N - 1; i++) { u_new(i, 0) = std::max(u_new(i,0), early_ex_premium(m,i)); }  
				}

				result(m+1, 0) = g_left(t[m+1]);
				result(m+1, N) = g_right(t[m+1]);
				for(int k = 1; k <= N-1; k++) { result(m+1,k) = u_new(k-1,0); }
			}

			return result;
		}


		Matrix BackwardEulerPricer(int M, int N, double t0, double t_final, double x_left, double x_right, Boundary_func
			f_begin, Boundary_func g_left, Boundary_func g_right, std::string solve_method, std::string optype, Matrix early_ex_premium)			
		{
			double delta_t = (t_final - t0) / M;
			double delta_x = (x_right - x_left) / N;
			Vec x = Mesh_vec(x_left, x_right, N);
			Vec t = Mesh_vec(t0, t_final, M);
			double alpha = delta_t / (delta_x * delta_x);

			Matrix result(M+1, N+1);

			Matrix u_old(N-1, 1);
			Matrix u_new(N-1, 1);
	
			// Initialize final matrix
			result(0,0) = g_left(t0); 
			result(0,N) = g_right(t0);

			for(int i = 0; i < u_old.Size1(); i++) 
			{// Initialize u when t=0, i.e u^0 and the final matrix.

				result(0,i+1) = u_old(i,0) = f_begin(x[i+1]);
			}
		
			Matrix A(N-1, N-1);
			for(int i = 0; i < N-1; i++)
			{// Initialize Matrix A
				A(i,i) = 1 + 2*alpha;
				if(i < N-2) A(i, i+1) = -alpha;
				if(i > 0) A(i, i-1) = -alpha;
			}

			for(int m = 0; m <= M-1; m++, u_old = u_new)
			{// Start to calculate Matrix 

				Matrix b(N-1,1);
				b(0,0) = alpha * g_left(t[m+1]);
				b(N-2, 0) = alpha * g_right(t[m+1]);

				if(optype == "American")
				{ // If it is an American Option. We only use SOR_entry_by_entry because LU cannot update the line.

					Matrix x0(N-1,1);
					for(int k = 0; k < N-1; k++) {x0(k,0) = early_ex_premium(m,k);}
				
					double omega = 1.2;
					double tol = 1e-6;			
					b = u_old + b;
					u_new = SOR_entry_by_entry_American(A, b, x0, tol, omega);
				}
				else if(optype != "American")
				{ // If it is not American Option, including European, DownAndOut for now. 
				  // You need to specify the method to solve this linear system.

					if(solve_method == "SOR")
					{
						Matrix x0(N-1,1);
						for(int k = 0; k < N-1; k++) {x0(k,0) = early_ex_premium(m,k);}
				
						double omega = 1.2;
						double tol = 1e-6;			
						b = u_old + b;
						int temp;
						boost::tie(u_new, temp) = sor_iter_consecutive_appro(A, b, u_old, 1e-6, 1.2);
					}
					else if(solve_method == "LU")
					{
						u_new = linear_solve_cholesky_tridiag_spd(A, u_old + b);
					}
					else
					{
						std::cout << "We cannot price using the method you require." << std::endl;
					}
				}
				result(m+1, 0) = g_left(t[m+1]);
				result(m+1, N) = g_right(t[m+1]);
				for(int k = 1; k <= N-1; k++) { result(m+1,k) = u_new(k-1,0); }
			}

			return result;
		}



		Matrix CrankNicolsonPricer(int M, int N, double t0, double t_final, double x_left, double x_right, Boundary_func
			f_begin, Boundary_func g_left, Boundary_func g_right, std::string solve_method, std::string optype, Matrix early_ex_premium)			
		{
			double delta_t = (t_final - t0) / M;
			double delta_x = (x_right - x_left) / N;
			Vec x = Mesh_vec(x_left, x_right, N);
			Vec t = Mesh_vec(t0, t_final, M);
			double alpha = delta_t / (delta_x * delta_x);

			Matrix result(M+1, N+1);

			Matrix u_old(N-1, 1);
			Matrix u_new(N-1, 1);
	
			// Initialize final matrix
			result(0,0) = g_left(t0); 
			result(0,N) = g_right(t0);

			for(int i = 0; i < u_old.Size1(); i++) 
			{// Initialize u when t=0, i.e u^0 and the final matrix.

				result(0,i+1) = u_old(i,0) = f_begin(x[i+1]);
			}
		
			Matrix A(N-1, N-1);
			Matrix B(N-1, N-1);
			for(int i = 0; i < N-1; i++)
			{// Initialize Matrix A
				A(i,i) = 1 + alpha;
				B(i,i) = 1 - alpha;
				if(i < N-2)
				{
					A(i, i+1) = -alpha/2;
					B(i, i+1) = alpha/2;
				}
				if(i > 0)
				{
					A(i, i-1) = -alpha/2;
					B(i, i-1) = alpha/2;
				}
			}

			for(int m = 0; m <= M-1; m++, u_old = u_new)
			{// Start to calculate Matrix 

				Matrix b(N-1,1);
				b(0,0) = alpha / 2 * (g_left(t[m]) + g_left(t[m+1]));
				b(N-2, 0) = alpha / 2 * (g_right(t[m]) + g_right(t[m+1]));

				if(optype == "American")
				{ // If it is an American Option. We only use SOR_entry_by_entry because LU cannot update the line.

					Matrix x0(N-1,1);
					for(int k = 0; k < N-1; k++) {x0(k,0) = early_ex_premium(m,k);}
				
					double omega = 1.2;
					double tol = 1e-8;			
					b = B * u_old + b;
					u_new = SOR_entry_by_entry_American(A, b, x0, tol, omega);
				}
				else if(optype != "American")
				{ // If it is not American Option, including European, DownAndOut for now. 
				  // You need to specify the method to solve this linear system.

					if(solve_method == "SOR")
					{
						Matrix x0(N-1,1);
						for(int k = 0; k < N-1; k++) {x0(k,0) = early_ex_premium(m,k);}
				
						double omega = 1.2;
						double tol = 1e-6;			
						b = B * u_old + b;
						int temp;
						boost::tie(u_new, temp) = sor_iter_consecutive_appro(A, b, u_old, 1e-6, 1.2);
					}
					else if(solve_method == "LU")
					{
						u_new = linear_solve_cholesky_tridiag_spd(A, B * u_old + b);
					}
					else
					{
						std::cout << "We cannot price using the method you require." << std::endl;
					}
				}


				result(m+1, 0) = g_left(t[m+1]);
				result(m+1, N) = g_right(t[m+1]);
				for(int k = 1; k <= N-1; k++) { result(m+1,k) = u_new(k-1,0); }
			}

			return result;
		}

	}
}