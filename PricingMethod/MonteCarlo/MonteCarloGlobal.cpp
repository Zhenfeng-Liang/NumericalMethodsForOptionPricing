// This file was designed to implement global function that the tree class call
//
// Zhenfeng Liang
//
// 10/8/2014


#include "MonteCarloGlobal.hpp"
#include "../../Option/Option.hpp"
#include "../../Option/DownAndOutOption.hpp"
#include <iostream>



namespace Derivatives
{
	namespace MonteCarloSpace
	{
		
		std::vector<double> LinearCongruentialGenerator(int N)
		{
			unsigned long long int x = 1;
			int a = 39373;
			int c = 0;
			int k = std::pow(2,31) - 1;
			std::vector<double> u(N);

			for (int i = 0; i < N; i++)
			{
				x = (a * x + c)%k;
				u[i] = double(x) / k;
			}
			return u;
		}

		std::vector<double> ApproximatingInverseNormal(std::vector<double> u)
		{ // Beasley-Springer-Moro algorithm for approximating the inverse normal
			
			int N = u.size();
			std::vector<double> x(N);

			double a0=2.50662823884;
			double a1=-18.61500062529;
			double a2=41.39119773534;
			double a3=-25.44106049637;

			double b0=-8.47351093090;
			double b1=23.08336743743;
			double b2=-21.06224101826;
			double b3=3.13082909833;

			double c0=0.3374754822726147;
			double c1=0.9761690190917186;
			double c2=0.1607979714918209;
			double c3=0.0276438810333863;
			double c4=0.0038405729373609;
			double c5=0.0003951896511919;
			double c6=0.0000321767881768;
			double c7=0.0000002888167364;
			double c8=0.0000003960315187;

			std::vector<double>::iterator ix = x.begin();
			std::vector<double>::iterator iu = u.begin();
			for (; ix != x.end(); ix++, iu++)
			{
				double y = *iu - 0.5;
				double r;
				if (std::abs(y) < 0.42)
				{
					r = y * y;
					double numerator1 = a3 * r + a2;
					double numerator2 = numerator1 * r + a1;
					double numerator3 = numerator2 * r + a0;

					double denominator1 = b3 * r + b2;
					double denominator2 = denominator1 * r + b1;
					double denominator3 = denominator2 * r + b0;
					double denominator4 = denominator3 * r + 1;

					*ix = y * numerator3 / denominator4;
				}
				else
				{
					double r = *iu;
					if (y > 0)
					{
						r = 1 - *iu;
					}
					r = log(- log(r));

					double temp1 = c7 + r * c8;
					double temp2 = c6 + r * temp1;
					double temp3 = c5 + r * temp2;
					double temp4 = c4 + r * temp3;
					double temp5 = c3 + r * temp4;
					double temp6 = c2 + r * temp5;
					double temp7 = c1 + r * temp6;
					double temp8 = c0 + r * temp7;

					*ix = temp8;

					if (y < 0)
					{
						*ix = - (*ix);
					}
				}
			}
			return x;
		}

/*
		std::vector<double> Acceptance_Rejection(std::vector<double> u)
		{
			int N = u.size();
			std::vector<double> result;

			for(int i = 0; i <= N - 3; i++)
			{
				double X = - log(u[i]);
				
				if(u[i+1] > exp(-0.5 * (X - 1) * (X - 1)))
					continue;
				else if (u[i+2] <= 0.5)
					X = -X;
				
				result.push_back(X);
			}

			return result;
		}

		std::vector<double> Box_Muller(std::vector<double> u)
		{
			int N = u.size();
			int u_begin_index = 0;
			std::vector<double> result;

			while(u_begin_index <= N -2)
			{
				double X = 2;
				double u1;
				double u2;
				bool u_out_of_use = false;

				while(X > 1)
				{
					u1 = u[u_begin_index];
					u2 = u[u_begin_index + 1];
					u1 = 2 * u1 - 1;
					u2 = 2 * u2 - 1;
					X = u1 * u1 + u2 * u2;
					
					u_begin_index++;

					if(u_begin_index == N - 1)
					{
						u_out_of_use = true;
						break;
					}
				}

				if(u_out_of_use)
					break;

				double Y = std::sqrt(-2 * log(X) / X);
				double z1 = u1 * Y; 
				double z2 = u2 * Y;

				result.push_back(z1);
				result.push_back(z2);
				u_begin_index++;
			}

			return result;
		}
*/	

		std::vector<double> Acceptance_Rejection(std::vector<double> u)
		{
			int N = u.size();
			std::vector<double> result;
			int generate_times = 0;

			for(int i = 0; i <= N - 3; generate_times++, i = generate_times * 3)
			{
				double X = - log(u[i]);
				
				if(u[i+1] > exp(-0.5 * (X - 1) * (X - 1)))
					continue;
				else if (u[i+2] <= 0.5)
					X = -X;
				
				result.push_back(X);
			}

			return result;
		}

		std::vector<double> Box_Muller(std::vector<double> u)
		{
			int N = u.size();
			int u_begin_index = 0;
			std::vector<double> result;

			while(u_begin_index <= N -2)
			{
				double X = 2;
				double u1;
				double u2;
				bool u_out_of_use = false;

				while(X > 1)
				{
					u1 = u[u_begin_index];
					u2 = u[u_begin_index + 1];
					u1 = 2 * u1 - 1;
					u2 = 2 * u2 - 1;
					X = u1 * u1 + u2 * u2;
	
					u_begin_index += 2;

					if(u_begin_index >= N - 1)
					{
						u_out_of_use = true;
						break;
					}
				}

				if(u_out_of_use)
					break;

				double Y = std::sqrt(-2 * log(X) / X);
				double z1 = u1 * Y; 
				double z2 = u2 * Y;

				result.push_back(z1);
				result.push_back(z2);
			}

			return result;
		}


		std::vector<double> MonteCarloNonPathDepedent_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator)
		{
			std::vector<double> result;

			double r = new_op_ptr->InterestRate();
			double q = new_op_ptr->Dividend();
			double sig = new_op_ptr->Volatility();
			double T = new_op_ptr->Maturity();
			double K = new_op_ptr->StrikePrice();
			double S0 = new_op_ptr->SpotPrice();
			std::string callputtype = new_op_ptr->CallPutType();
			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(N);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = z.size();
			double simulation_times = NSIM;
			
			result.push_back(simulation_times);

			double v_sum = 0;
			double delta_sum = 0;
			double vega_sum = 0;

			for (int i = 1; i <= NSIM; i++)
			{
				double S_i;
				S_i = S0 * exp((r - q - sig * sig / 2) * T + sig * std::sqrt(T) * z[i - 1]);

				bool S_i_largger_than_K;
				bool K_largger_than_S_i;
		
				S_i_largger_than_K = (S_i > K);
				K_largger_than_S_i = (K > S_i);

				if (callputtype == "Call")
				{
					v_sum += exp(- r * T) * std::max<double>(S_i - K, 0.0);
					delta_sum += S_i_largger_than_K * exp(- r * T) * S_i / S0;
					vega_sum += S_i_largger_than_K * exp(- r * T) * S_i * (- sig * T + std::sqrt(T) * z[i - 1]);
				}
				else if (callputtype == "Put")
				{
					v_sum += exp(- r * T) * std::max<double>(K - S_i, 0.0);
					delta_sum += (-1) * (K_largger_than_S_i * exp(- r * T) * S_i / S0);
					vega_sum += (-1) * (K_largger_than_S_i * exp(- r * T) * S_i * (- sig * T + std::sqrt(T) * z[i - 1]));	
				}
			}
	
			double value_store = v_sum / NSIM;
			double delta_store = delta_sum / NSIM;
			double vega_store = vega_sum / NSIM;	

			result.push_back(value_store);
			result.push_back(delta_store);
			result.push_back(vega_store);

			return result;
		}

		std::vector<double> MonteCarloPathDepedent_init_(boost::shared_ptr<Option> new_op_ptr, int NT, int NSIM)
		{
			std::vector<double> result;

			double r = new_op_ptr->InterestRate();
			double q = new_op_ptr->Dividend();
			double sig = new_op_ptr->Volatility();
			double T = new_op_ptr->Maturity();
			double K = new_op_ptr->StrikePrice();
			double S0 = new_op_ptr->SpotPrice();
			double B = new_op_ptr->Barrier();
			double delta_t = T / NT;

			std::cout << "B: " << B << std::endl;

			int N = NT * NSIM;
			std::string callputtype = new_op_ptr->CallPutType();
			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(N);
			std::vector<double> z = MonteCarloSpace::ApproximatingInverseNormal(u);

			double v_sum = 0;

			for(int i = 0; i < NSIM; i++)
			{
				double S_old = S0;
				double S_new;
				bool out_of_barrier = false;
			
				int start_index_taking_z = i * NT;

				for(int j = 0; j < NT; j++)
				{
					S_new = S_old * exp((r - q - sig * sig / 2) * delta_t + sig * std::sqrt(delta_t) * z[start_index_taking_z + j]);
				
					// Down and out option
					if(S_new <= B)
					{
						out_of_barrier = true;
						break;
					}
					S_old = S_new;
				}

				if(!out_of_barrier)
				{
					if (callputtype == "Call")
					{
						v_sum += exp(- r * T) * std::max<double>(S_new - K, 0.0);
					}
					else if (callputtype == "Put")
					{
						v_sum += exp(- r * T) * std::max<double>(K - S_new, 0.0);
					}
				}
			}
	
			double value_store = v_sum / NSIM;
			result.push_back(value_store);

			return result;
		}


		std::vector<double> MonteCarloNonPathDepedent_Control_Variate_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator)
		{
			std::vector<double> result;

			double r = new_op_ptr->InterestRate();
			double q = new_op_ptr->Dividend();
			double sig = new_op_ptr->Volatility();
			double T = new_op_ptr->Maturity();
			double K = new_op_ptr->StrikePrice();
			double S0 = new_op_ptr->SpotPrice();
			std::string callputtype = new_op_ptr->CallPutType();
			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(5 * N);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = N;
			double simulation_times = NSIM;
			std::cout << NSIM << std::endl;

			std::vector<double> S;
			std::vector<double> V;

			double S_sum = 0;
			double v_sum = 0;

			for (int i = 0; i < NSIM; i++)
			{
				double S_i;
				S_i = S0 * exp((r - q - sig * sig / 2) * T + sig * std::sqrt(T) * z[i]);

				S.push_back(S_i);
				S_sum += S_i;

				double v_i;
				if (callputtype == "Call")
				{
					v_i = exp(- r * T) * std::max<double>(S_i - K, 0.0);				
					v_sum += v_i;
					V.push_back(v_i);
				}
				else if (callputtype == "Put")
				{
					v_i = exp(- r * T) * std::max<double>(K - S_i, 0.0);
					v_sum += v_i;
					V.push_back(v_i);
				}
			}
	
			double S_hat = S_sum / NSIM;
			double value_hat = v_sum / NSIM;

			double b_hat;
			double b_hat_numerator = 0;
			double b_hat_denominator = 0;

			for(int i = 0; i < NSIM; i++)
			{
				double S_diff = S[i] - S_hat;
				b_hat_denominator += S_diff * S_diff;
				
				double V_diff = V[i] - value_hat;
				b_hat_numerator += S_diff * V_diff;
			}

			b_hat = b_hat_numerator / b_hat_denominator;

			double w_sum = 0;

			for(int i = 0; i < NSIM; i++)
			{
				double w_i;
				w_i = V[i] - b_hat * (S[i] - exp(r * T) * S0);
				w_sum += w_i;
			}

			double w_store = w_sum / NSIM;

			result.push_back(simulation_times);
			result.push_back(w_store);

			return result;
		}

		std::vector<double> MonteCarloNonPathDepedent_Antithetic_Variables_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator)
		{
			std::vector<double> result;

			double r = new_op_ptr->InterestRate();
			double q = new_op_ptr->Dividend();
			double sig = new_op_ptr->Volatility();
			double T = new_op_ptr->Maturity();
			double K = new_op_ptr->StrikePrice();
			double S0 = new_op_ptr->SpotPrice();
			std::string callputtype = new_op_ptr->CallPutType();
			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(3 * N);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = N;
			double simulation_times = NSIM;
			std::cout << NSIM << std::endl;

			double v_sum = 0;
			double delta_sum = 0;
			double vega_sum = 0;

			for (int i = 0; i < NSIM; i++)
			{
				double S_i_1;
				double S_i_2;
				S_i_1 = S0 * exp((r - q - sig * sig / 2) * T + sig * std::sqrt(T) * z[i]);
				S_i_2 = S0 * exp((r - q - sig * sig / 2) * T + sig * std::sqrt(T) * (- z[i]));

				if (callputtype == "Call")
				{
					v_sum += exp(- r * T) * std::max<double>(S_i_1 - K, 0.0);
					v_sum += exp(- r * T) * std::max<double>(S_i_2 - K, 0.0);
				}
				else if (callputtype == "Put")
				{
					v_sum += exp(- r * T) * std::max<double>(K - S_i_1, 0.0);	
					v_sum += exp(- r * T) * std::max<double>(K - S_i_2, 0.0);	
				}
			}
	
			double value_store = v_sum / (2 * NSIM);

			result.push_back(simulation_times);
			result.push_back(value_store);

			return result;
		}

		std::vector<double> MonteCarloNonPathDepedent_Moment_Matching_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator)
		{
			std::vector<double> result;

			double r = new_op_ptr->InterestRate();
			double q = new_op_ptr->Dividend();
			double sig = new_op_ptr->Volatility();
			double T = new_op_ptr->Maturity();
			double K = new_op_ptr->StrikePrice();
			double S0 = new_op_ptr->SpotPrice();
			std::string callputtype = new_op_ptr->CallPutType();
			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(3 * N);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = N;
			double simulation_times = NSIM;
			std::cout << NSIM << std::endl;

			std::vector<double> S;

			double S_sum = 0;

			for (int i = 0; i < NSIM; i++)
			{
				double S_i;
				S_i = S0 * exp((r - q - sig * sig / 2) * T + sig * std::sqrt(T) * z[i]);
				S.push_back(S_i);
				S_sum += S_i;
			}
	
			double S_hat = S_sum / NSIM;
			std::cout << "S hat: " << S_hat << std::endl;

			double v_sum = 0;
			for(int i = 0; i < NSIM; i++)
			{
				S[i] = S[i] * exp(r * T) * S0 / S_hat;

				if (callputtype == "Call")
				{
					v_sum += exp(- r * T) * std::max<double>(S[i] - K, 0.0);				
				}
				else if (callputtype == "Put")
				{
					v_sum += exp(- r * T) * std::max<double>(K - S[i], 0.0);
				}
			}

			double value_hat_MM = v_sum / NSIM;
			std::cout << "v_sum: " <<  v_sum << "  value_hat_MM " << value_hat_MM << std::endl;

			result.push_back(simulation_times);
			result.push_back(value_hat_MM);

			return result;
		}

		std::vector<double> MonteCarloNonPathDepedent_Control_Variate_Moment_Matching_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator)
		{
			std::vector<double> result;

			double r = new_op_ptr->InterestRate();
			double q = new_op_ptr->Dividend();
			double sig = new_op_ptr->Volatility();
			double T = new_op_ptr->Maturity();
			double K = new_op_ptr->StrikePrice();
			double S0 = new_op_ptr->SpotPrice();
			std::string callputtype = new_op_ptr->CallPutType();
			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(3 * N);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = N;
			double simulation_times = NSIM;
			std::cout << NSIM << std::endl;

			std::vector<double> S;

			double S_sum = 0;
			
			for (int i = 0; i < NSIM; i++)
			{
				double S_i;
				S_i = S0 * exp((r - q - sig * sig / 2) * T + sig * std::sqrt(T) * z[i]);

				S.push_back(S_i);
				S_sum += S_i;
			}
	
			double S_hat = S_sum / NSIM;

			std::vector<double> V_tiu;
			double v_tiu_sum = 0;
			for(int i = 0; i< NSIM; i++)
			{
				S[i] = S[i] * exp(r * T) * S0 / S_hat;

				double v_i;
				if (callputtype == "Call")
				{
					v_i = exp(- r * T) * std::max<double>(S[i] - K, 0.0);				
					v_tiu_sum += v_i;
					V_tiu.push_back(v_i);
				}
				else if (callputtype == "Put")
				{
					v_i = exp(- r * T) * std::max<double>(K - S[i], 0.0);
					v_tiu_sum += v_i;
					V_tiu.push_back(v_i);
				}		
			}

			double V_hat = v_tiu_sum / NSIM;

			double b_hat;
			double b_hat_numerator = 0;
			double b_hat_denominator = 0;

			for(int i = 0; i < NSIM; i++)
			{
				double S_diff = S[i] - exp(r * T) * S0;
				b_hat_denominator += S_diff * S_diff;
				
				double V_diff = V_tiu[i] - V_hat;
				b_hat_numerator += S_diff * V_diff;
			}

			b_hat = b_hat_numerator / b_hat_denominator;

			double w_sum = 0;

			for(int i = 0; i < NSIM; i++)
			{
				double w_i;
				w_i = V_tiu[i] - b_hat * (S[i] - exp(r * T) * S0);
				w_sum += w_i;
			}

			double w_store = w_sum / NSIM;

			result.push_back(simulation_times);
			result.push_back(w_store);

			return result;
		}

		std::vector<double> MonteCarloNonPathDepedent_Basket_Option_init_(double r, double T, double K, double q, double corr, double S1, double sig1, double S2, double sig2, int N, std::string callputtype, std::string rv_generator)
		{
			double S0_1 = S1;
			double q1 = q;

			double S0_2 = S2;
			double q2 = q;
			
			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(3 * N);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = N;
			double simulation_times = NSIM;

			double v_sum = 0;

			for (int i = 0; i <= (NSIM / 2 - 1); i++)
			{
				double S_i_1;
				S_i_1 = S0_1 * exp((r - q1 - sig1 * sig1 / 2) * T + sig1 * std::sqrt(T) * z[2*i]);

				double S_i_2;
				S_i_2 = S0_2 * exp((r - q2 - sig2 * sig2 / 2) * T + sig2 * std::sqrt(T) * (corr * z[2*i] + std::sqrt(1 - corr * corr) * z[2*i+1]));

				if (callputtype == "Call")
				{
					v_sum += exp(- r * T) * std::max<double>(S_i_1 + S_i_2 - K, 0.0);
				}
				else if (callputtype == "Put")
				{
					v_sum += exp(- r * T) * std::max<double>(K - S_i_1 - S_i_2, 0.0);
				}
			}
	
			double value_store = v_sum / (NSIM / 2);

			std::vector<double> result;
			result.push_back(simulation_times);
			result.push_back(value_store);

			return result;
		}
	
		std::vector<double> MonteCarloPathDepedent_Basket_Option_init_(double r, double T, double K, double q, double corr, double S1, double sig1, double S2, double sig2, int m, int n, std::string callputtype, std::string rv_generator)
		{

			double S0_1 = S1;
			double q1 = q;

			double S0_2 = S2;
			double q2 = q;

			double delta_t = T/m;

			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(3 * 2 * m * n);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = n;
			double simulation_times = NSIM;

			double v_sum = 0;

			for (int i = 0; i < NSIM; i++)
			{
				double S_i_1 = 0;
				double S_i_2 = 0;
				int count = i * m;
				
				double S1_old = S0_1;
				double S1_new;
				double S2_old = S0_2;
				double S2_new;
				
				for(int j = 0; j <= m-1; j++, S1_old = S1_new, S2_old = S2_new)
				{
					S1_new = S1_old * exp((r - q1 - sig1 * sig1 / 2) * delta_t + sig1 * std::sqrt(delta_t) * z[count + 2*j]);
					S2_new = S2_old * exp((r - q2 - sig2 * sig2 / 2) * delta_t + sig2 * std::sqrt(delta_t) * (corr * z[count + 2*j] + std::sqrt(1 - corr * corr) * z[count + 2*j+1]));
					if(S1_new + S2_new > S_i_1 + S_i_2)
					{
						S_i_1 = S1_new; S_i_2 = S2_new;
					}
				}

				if (callputtype == "Call")
				{
					v_sum += exp(- r * T) * std::max<double>(S_i_1 + S_i_2 - K, 0.0);
				}
				else if (callputtype == "Put")
				{
					v_sum += exp(- r * T) * std::max<double>(K - S_i_1 - S_i_2, 0.0);
				}
			}
	
			double value_store = v_sum / NSIM;

			std::vector<double> result;
			result.push_back(simulation_times);
			result.push_back(value_store);

			return result;
		}
/*
		std::vector<double> MonteCarloNonPathDepedent_Basket_Option_init_(boost::shared_ptr<Option> new_op_ptr1, boost::shared_ptr<Option> new_op_ptr2, double corr, int N, std::string rv_generator)
		{
			double r1 = new_op_ptr1->InterestRate();
			double q1 = new_op_ptr1->Dividend();
			double sig1 = new_op_ptr1->Volatility();
			double T1 = new_op_ptr1->Maturity();
			double K1 = new_op_ptr1->StrikePrice();
			double S0_1 = new_op_ptr1->SpotPrice();
			std::string callputtype1 = new_op_ptr1->CallPutType();

			double r2 = new_op_ptr2->InterestRate();
			double q2 = new_op_ptr2->Dividend();
			double sig2 = new_op_ptr2->Volatility();
			double T2 = new_op_ptr2->Maturity();
			double K2 = new_op_ptr2->StrikePrice();
			double S0_2 = new_op_ptr2->SpotPrice();
			std::string callputtype2 = new_op_ptr2->CallPutType();

			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(3 * N);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = N;
			double simulation_times = NSIM;

			double v_sum = 0;

			for (int i = 0; i <= (NSIM / 2 - 1); i++)
			{
				double S_i_1;
				S_i_1 = S0_1 * exp((r1 - q1 - sig1 * sig1 / 2) * T1 + sig1 * std::sqrt(T1) * z[2*i]);

				double S_i_2;
				S_i_2 = S0_2 * exp((r2 - q2 - sig2 * sig2 / 2) * T2 + sig2 * std::sqrt(T2) * (corr * z[2*i] + std::sqrt(1 - corr * corr) * z[2*i+1]));

				if (callputtype1 == "Call")
				{
					v_sum += exp(- r1 * T1) * std::max<double>(S_i_1 + S_i_2 - K1, 0.0);
				}
				else if (callputtype1 == "Put")
				{
					v_sum += exp(- r1 * T1) * std::max<double>(K1 - S_i_1 - S_i_2, 0.0);
				}
			}
	
			double value_store = v_sum / (NSIM / 2);

			std::vector<double> result;
			result.push_back(simulation_times);
			result.push_back(value_store);

			return result;
		}
		
		std::vector<double> MonteCarloPathDepedent_Basket_Option_init_(boost::shared_ptr<Option> new_op_ptr1, boost::shared_ptr<Option> new_op_ptr2, double corr, int m, int n, std::string rv_generator)
		{
			double r1 = new_op_ptr1->InterestRate();
			double q1 = new_op_ptr1->Dividend();
			double sig1 = new_op_ptr1->Volatility();
			double T1 = new_op_ptr1->Maturity();
			double K1 = new_op_ptr1->StrikePrice();
			double S0_1 = new_op_ptr1->SpotPrice();
			std::string callputtype1 = new_op_ptr1->CallPutType();

			double r2 = new_op_ptr2->InterestRate();
			double q2 = new_op_ptr2->Dividend();
			double sig2 = new_op_ptr2->Volatility();
			double T2 = new_op_ptr2->Maturity();
			double K2 = new_op_ptr2->StrikePrice();
			double S0_2 = new_op_ptr2->SpotPrice();
			std::string callputtype2 = new_op_ptr2->CallPutType();

			double delta_t = T1/m;

			std::vector<double> u = MonteCarloSpace::LinearCongruentialGenerator(3 * 2 * m * n);
			std::vector<double> z;

			if(rv_generator == "Inverse Transform Method")
				z = MonteCarloSpace::ApproximatingInverseNormal(u);
			else if (rv_generator == "Acceptance Rejection Method")
				z = MonteCarloSpace::Acceptance_Rejection(u);
			else if (rv_generator == "Box Muller Method")
				z = MonteCarloSpace::Box_Muller(u);

			int NSIM = n;
			double simulation_times = NSIM;

			double v_sum = 0;

			for (int i = 0; i < NSIM; i++)
			{
				double S_i_1 = 0;
				double S_i_2 = 0;
				int count = i * m;
				
				double S1_old = S0_1;
				double S1_new;
				double S2_old = S0_2;
				double S2_new;
				
				for(int j = 0; j <= m-1; j++, S1_old = S1_new, S2_old = S2_new)
				{
					S1_new = S1_old * exp((r1 - q1 - sig1 * sig1 / 2) * delta_t + sig1 * std::sqrt(delta_t) * z[count + 2*j]);
					S2_new = S2_old * exp((r2 - q2 - sig2 * sig2 / 2) * delta_t + sig2 * std::sqrt(delta_t) * (corr * z[count + 2*j] + std::sqrt(1 - corr * corr) * z[count + 2*j+1]));
					if(S1_new + S2_new > S_i_1 + S_i_2)
					{
						S_i_1 = S1_new; S_i_2 = S2_new;
					}
				}

				if (callputtype1 == "Call")
				{
					v_sum += exp(- r1 * T1) * std::max<double>(S_i_1 + S_i_2 - K1, 0.0);
				}
				else if (callputtype1 == "Put")
				{
					v_sum += exp(- r1 * T1) * std::max<double>(K1 - S_i_1 - S_i_2, 0.0);
				}
			}
	
			double value_store = v_sum / NSIM;

			std::vector<double> result;
			result.push_back(simulation_times);
			result.push_back(value_store);

			return result;
		}
*/
	}
}

