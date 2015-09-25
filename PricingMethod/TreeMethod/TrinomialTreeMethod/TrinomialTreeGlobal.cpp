// This file was designed to implement global function that the trinomial tree class call
//
// Zhenfeng Liang
//
// 12/16/2014



#include "TrinomialTreeGlobal.hpp"
#include <iostream>


namespace Derivatives
{
	namespace TrinomialTreeSpace
	{
		std::vector<double> TrinomialSpotFirstPeriod(Option *op, int N)
		{
			double S = op->SpotPrice();
			double T = op->Maturity();
			double sig = op->Volatility();
			
			double Delta_t = T/N;
			double u = exp(sig * sqrt(3 * Delta_t));
			double d = 1/u;
			std::vector<double> s1(3);
			s1[0] = S * u; s1[1] = S; s1[2] = S * d;
			return s1;
		}

		std::vector<double> TrinomialSpotSecondPeriod(Option *op, int N)
		{
			double S = op->SpotPrice();
			double T = op->Maturity();
			double sig = op->Volatility();

			double Delta_t = T/N;
			double u = exp(sig * sqrt(3 * Delta_t));
			double d = 1/u;
			std::vector<double> s2(5);
			s2[0] = S * u * u; s2[1] = S * u; s2[2] = S; s2[3] = S * d; s2[4] = S * d * d;
			return s2;
		}


		std::vector<double> Trinomial_Tree(Option *op, int N, int begin_step)
		{
			double S = op->SpotPrice();
			double T = op->Maturity();
			double K = op->StrikePrice();
			double sig = op->Volatility();
			double r = op->InterestRate();
			double q = op->Dividend();
			std::string CallPutType = op->CallPutType();
			std::string OptionType = op->OptionType();

			std::vector<double> V(2*N + 1);
			double Delta_t = T/N;
			double u = exp(sig * sqrt(3 * Delta_t));
			double d = 1/u;
			double p_rn_u = 1.0/6.0 + (r - q - sig * sig / 2) * sqrt(Delta_t / (12 * sig * sig));
			double p_rn_m = 2.0/3.0;
			double p_rn_d = 1.0/6.0 - (r - q - sig * sig / 2) * sqrt(Delta_t / (12 * sig * sig));
			double p_rn_u_tiu = exp(- r * Delta_t) * p_rn_u;
			double p_rn_m_tiu = exp(- r * Delta_t) * p_rn_m;
			double p_rn_d_tiu = exp(- r * Delta_t) * p_rn_d;

			for(int i = 0; i <= 2 * N; i++)
			{
				double temp = S * pow(u, N - i);
				if(CallPutType == "Call")
					V[i] = std::max((temp - K), 0.0);
				else if(CallPutType == "Put")
					V[i] = std::max((K - temp), 0.0);
				else
					std::cout << "No respective Trinomial tree can be called." << std::endl;

				if(OptionType == "DownAndOut" && (temp < op->Barrier()))
					V[i] = 0;
			}

			if(OptionType == "American")
			{
				for(int j = N - 1; j >= begin_step; j--)
					for(int i = 0; i <= 2 * j; i++)
					{
						double disc_price = p_rn_u_tiu * V[i] + p_rn_m_tiu * V[i+1] + p_rn_d_tiu * V[i+2];
						double excirse_value;
						if(CallPutType == "Call")
						{
							excirse_value = S * pow(u, j - i) - K;
						}
						else if(CallPutType == "Put")
						{
							excirse_value = K - S * pow(u, j - i);
						}
						else
						{
							std::cout << "Cannot find suitable option type." << std::endl;
						}
						V[i] = std::max(disc_price, excirse_value);
					}
			}
			else if (OptionType == "European")
			{
				for(int j = N - 1; j >= begin_step; j--)
					for(int i = 0; i <= 2 * j; i++)
						V[i] = p_rn_u_tiu * V[i] + p_rn_m_tiu * V[i+1] + p_rn_d_tiu * V[i+2];
			}
			else if(OptionType == "DownAndOut")
			{
				double B = op->Barrier();
				for(int j = N - 1; j >= begin_step; j--)
					for(int i = 0; i <= 2 * j; i++)
					{
						double S_node = S * pow(u, j - i);
						
						if(S_node < B)
							V[i] = 0;
						else
							V[i] = p_rn_u_tiu * V[i] + p_rn_m_tiu * V[i+1] + p_rn_d_tiu * V[i+2];
					}
			}

			return V;
		}
	

		double TrinomialPrice(Option *op, int N)
		{	
			return Trinomial_Tree(op, N, 0)[0];
		}

		std::vector<double> TrinomialPriceFirstPeriod(Option *op, int N)
		{	
			std::vector<double> temp = Trinomial_Tree(op, N, 1);
			std::vector<double> v1(3);
			v1[0] = temp[0]; v1[1] = temp[1]; v1[2] = temp[2];
			return v1;
		}

		std::vector<double> TrinomialPriceSecondPeriod(Option *op, int N)
		{
			std::vector<double> temp = Trinomial_Tree(op, N, 2);
			std::vector<double> v2(5);
			v2[0] = temp[0]; v2[1] = temp[1]; v2[2] = temp[2];v2[3] = temp[3];v2[4] = temp[4];
			return v2;
		}


		double TrinomialDelta(std::vector<double> S1, std::vector<double> V1)
		{
			return (V1[0] - V1[2])/(S1[0] - S1[2]);
		}

		double TrinomialGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2)
		{
			double temp1 = (V2[0] - V2[2])/(S2[0] - S2[2]);
			double temp2 = (V2[2] - V2[4])/(S2[2] - S2[4]);

			return (temp1 - temp2)/(S1[0] - S1[2]);
		}

		double TrinomialTheta(double V0, std::vector<double> V1, double T, int N)
		{
			double Delta_t = T/N;

			return (V1[1] - V0)/(Delta_t);
		}

		/*************************/
		std::vector<double> Trinomial_Black_Scholes(Option *op, int N, int begin_step)
		{
			double S = op->SpotPrice();
			double T = op->Maturity();
			double K = op->StrikePrice();
			double sig = op->Volatility();
			double r = op->InterestRate();
			double q = op->Dividend();
			std::string CallPutType = op->CallPutType();
			std::string OptionType = op->OptionType();

			std::vector<double> V(2*N + 1);
			double Delta_t = T/N;
			double u = exp(sig * sqrt(3 * Delta_t));
			double d = 1/u;
			double p_rn_u = 1.0/6.0 + (r - q - sig * sig / 2) * sqrt(Delta_t / (12 * sig * sig));
			double p_rn_m = 2.0/3.0;
			double p_rn_d = 1.0/6.0 - (r - q - sig * sig / 2) * sqrt(Delta_t / (12 * sig * sig));
			double p_rn_u_tiu = exp(- r * Delta_t) * p_rn_u;
			double p_rn_m_tiu = exp(- r * Delta_t) * p_rn_m;
			double p_rn_d_tiu = exp(- r * Delta_t) * p_rn_d;

			for(int i = 0; i <= 2 * N - 2; i++)
			{
				double temp = S * pow(u, N - 1 - i);
				if(CallPutType == "Call")
				{
					V[i] = EuropeanOptionSpace::CallPrice(temp, Delta_t, K, sig, r, q);
					if(OptionType == "American") V[i] = std::max(V[i], temp - K);
				}
				else if(CallPutType == "Put")
				{
					V[i] = EuropeanOptionSpace::PutPrice(temp, Delta_t, K, sig, r, q);
					if(OptionType == "American") V[i] = std::max(V[i], K - temp);
				}
				else
					std::cout << "No respective Trinomial Black Scholes tree can be called." << std::endl;
			}

			if(OptionType == "American")
			{
				for(int j = N - 2; j >= begin_step; j--)
					for(int i = 0; i <= 2 * j; i++)
					{
						double disc_price = p_rn_u_tiu * V[i] + p_rn_m_tiu * V[i+1] + p_rn_d_tiu * V[i+2];
						double excirse_value;
						if(CallPutType == "Call")
						{
							excirse_value = S * pow(u, j - i) - K;
						}
						else if(CallPutType == "Put")
						{
							excirse_value = K - S * pow(u, j - i);
						}
						else
						{
							std::cout << "Cannot find suitable option type." << std::endl;
						}
						V[i] = std::max(disc_price, excirse_value);
					}
			}
			else if (OptionType == "European")
			{
				for(int j = N - 2; j >= begin_step; j--)
					for(int i = 0; i <= 2 * j; i++)
						V[i] = p_rn_u_tiu * V[i] + p_rn_m_tiu * V[i+1] + p_rn_d_tiu * V[i+2];
			}
		
			return V;
		}

		double TrinomialBlackScholesPrice(Option *op, int N) 
		{
			return Trinomial_Black_Scholes(op, N, 0)[0];
		}

		std::vector<double> TrinomialBlackScholesPriceFirstPeriod(Option *op, int N)
		{
			std::vector<double> temp = Trinomial_Black_Scholes(op, N, 1);
			std::vector<double> v1(3);
			v1[0] = temp[0]; v1[1] = temp[1]; v1[2] = temp[2];
			return v1;
		}

		std::vector<double> TrinomialBlackScholesPriceSecondPeriod(Option *op, int N)
		{
			std::vector<double> temp = Trinomial_Black_Scholes(op, N, 2);
			std::vector<double> v2(5);
			v2[0] = temp[0]; v2[1] = temp[1]; v2[2] = temp[2]; v2[3] = temp[3]; v2[4] = temp[4];
			return v2;
		}

		double TrinomialBlackScholesDelta(std::vector<double> S1, std::vector<double> V1)
		{
			return (V1[0] - V1[2])/(S1[0] - S1[2]);
		}

		double TrinomialBlackScholesGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2)
		{
			double temp1 = (V2[0] - V2[2])/(S2[0] - S2[2]);
			double temp2 = (V2[2] - V2[4])/(S2[2] - S2[4]);

			return (temp1 - temp2)/(S1[0] - S1[2]);
		}

		double TrinomialBlackScholesTheta(double V0, std::vector<double> V1, double T, int N)
		{
			double Delta_t = T/N;
			return (V1[1] - V0)/(Delta_t);
		}
		
	}
}

