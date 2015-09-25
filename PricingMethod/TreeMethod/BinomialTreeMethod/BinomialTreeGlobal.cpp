// This file was designed to implement global function that the tree class call
//
// Zhenfeng Liang
//
// 10/8/2014


#include "BinomialTreeGlobal.hpp"
#include <iostream>


namespace Derivatives
{
	namespace BinomialTreeSpace
	{
		
		std::vector<double> BinomialSpotFirstPeriod(Option *op, int N)
		{
			// Initialize the parameter
			double S = op -> SpotPrice();
			double T = op -> Maturity();
			double sig = op -> Volatility();

			double Delta_t = T/N;
			double u = exp(sig * sqrt(Delta_t));
			double d = 1/u;
			std::vector<double> s1(2);
			s1[0] = S * u; s1[1] = S * d;
			return s1;
		}

		std::vector<double> BinomialSpotSecondPeriod(Option *op, int N)
		{
			// Initialize the parameter
			double S = op -> SpotPrice();
			double T = op -> Maturity();
			double sig = op -> Volatility();

			double Delta_t = T/N;
			double u = exp(sig * sqrt(Delta_t));
			double d = 1/u;
			std::vector<double> s2(3);
			s2[0] = S * u * u; s2[1] = S * d * u; s2[2] = S * d * d;
			return s2;
		}

		std::vector<double> Binomial_Tree(Option *op, int N, int begin_step)
		{
			// Initialize option parameter
			double S = op -> SpotPrice();
			double T = op->Maturity();
			double K = op->StrikePrice();
			double sig = op->Volatility();
			double r = op->InterestRate();
			double q = op->Dividend();
			std::string CallPutType = op->CallPutType(); 
			std::string OptionType = op->OptionType();
			std::string dividend_type = op->Dividend_type();
			double div_start_t = op->Dividend_start_time();
			double div_t_interval = op->Dividend_time_interval();
			std::vector<std::string> div_type_vec = op->Dividend_type_vec();
			std::vector<double> div_value_vec = op->Dividend_value_vec();

			int n;			// Times pay dividend
			double D;		// Fixed dividend payed each time
			double f;		// Proportion dividend

			double proportion_after_paying_proportional_div = 1.0;  // Store the Discrete mixed, all the proportional one
																	// = (1 - f1)*(1 - f2) *****(1 - fn)
			n = (T - div_start_t) / div_t_interval + 1;
			
			// Pre-process according to the ways of paying dividends.
			if(dividend_type == "Continuous")
			{
			}
			else if(dividend_type == "Discrete proportional") 
			{
				f = q;		// If the option pay dividend propertional, q represent the dividend proportion
				proportion_after_paying_proportional_div = std::pow(1 - f, n);
				K = K / proportion_after_paying_proportional_div;
				q = 0;		// Set the constinuous part 0
			}
			else if(dividend_type == "Discrete fixed")
			{
				D = q;
				double t = div_start_t;
				for(int count = 0; count < n; count++)
				{
					t += count * div_t_interval;
					S -= D * exp(-r * t);
				}
				q = 0;		// Set the constinuous part 0
			}
			else if(dividend_type == "Discrete mixed")
			{
				n = div_type_vec.size();
				
				double t = div_start_t;
				for(int count = 0; count < n; count++)
				{
					t += count * div_t_interval;

					if(div_type_vec[count] == "Proportional")
						proportion_after_paying_proportional_div *= (1 - div_value_vec[count]);		// Handle the proportional cases
					else if(div_type_vec[count] == "Fixed")
						S -= div_value_vec[count] * exp(- r * t);									// Fixed cases
					else
						std::cout << "Binomial tree cannot handle with this dividend payment: " << div_type_vec[count] << std::endl;

					K /= proportion_after_paying_proportional_div;
				}
				q = 0;	// Set the constinuous part 0
			}
			else
			{
				std::cout << "Binomial Tree cannot price asset with this kind of paying dividend: " << dividend_type << std::endl;
			}

			std::vector<double> V(N+1);
			double Delta_t = T/N;
			double u = exp(sig * sqrt(Delta_t));
			double d = 1/u;
			double p_rn_u = (exp((r - q) * Delta_t) - d)/(u - d);
			double p_rn_d = 1 - p_rn_u;
			double p_rn_u_tiu = exp(- r * Delta_t) * p_rn_u;
			double p_rn_d_tiu = exp(- r * Delta_t) * p_rn_d;

			for(int i = 0; i <= N; i++)
			{
				double temp = S * pow(u, N - i) * pow(d, i);
				if(CallPutType == "Call")
					V[i] = std::max((temp - K), 0.0);
				else if(CallPutType == "Put")
					V[i] = std::max((K - temp), 0.0);
				else
					std::cout << "No respective Binomial tree can be called." << std::endl;

				if(OptionType == "DownAndOut" && (temp < op->Barrier()))
					V[i] = 0;

				V[i] *= proportion_after_paying_proportional_div;	// Handle the proportional paying dividend stuff
			}

			if(OptionType == "American")
			{
				for(int j = N - 1; j >= begin_step; j--)
					for(int i = 0; i <= j; i++)
					{
						double disc_price = (p_rn_u_tiu * V[i] + p_rn_d_tiu * V[i+1]);
						double excirse_value;
						if(CallPutType == "Call")
						{
							excirse_value = S * pow(u, j - i) * pow(d, i) - K;
						}
						else if(CallPutType == "Put")
						{
							excirse_value = K - S * pow(u, j - i) * pow(d, i);
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
					for(int i = 0; i <= j; i++)
						V[i] = p_rn_u_tiu * V[i] + p_rn_d_tiu * V[i+1];
			}
			else if(OptionType == "DownAndOut")
			{
				double B = op->Barrier();
				for(int j = N - 1; j >= begin_step; j--)
					for(int i = 0; i <= j; i++)
					{
						double S_node = S * pow(u, j - i) * pow(d, i);
						
						if(S_node < B)
							V[i] = 0;
						else
							V[i] = p_rn_u_tiu * V[i] + p_rn_d_tiu * V[i+1];	
					}
			}
			return V;
		}

		double BinomialPrice(Option *op, int N)
		{	
			return Binomial_Tree(op, N, 0)[0];
		}

		std::vector<double> BinomialPriceFirstPeriod(Option *op, int N)
		{	
			std::vector<double> temp = Binomial_Tree(op, N, 1);
			std::vector<double> v1(2);
			v1[0] = temp[0]; v1[1] = temp[1];
			return v1;
		}

		std::vector<double> BinomialPriceSecondPeriod(Option *op, int N)
		{
			std::vector<double> temp = Binomial_Tree(op, N, 2);
			std::vector<double> v2(3);
			v2[0] = temp[0]; v2[1] = temp[1]; v2[2] = temp[2];
			return v2;
		}

		double BinomialDelta(std::vector<double> S1, std::vector<double> V1)
		{
			return (V1[0] - V1[1])/(S1[0] - S1[1]);
		}

		double BinomialGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2)
		{
			double temp1 = (V2[0] - V2[1])/(S2[0] - S2[1]);
			double temp2 = (V2[1] - V2[2])/(S2[1] - S2[2]);
			return 2 * (temp1 - temp2)/(S2[0] - S2[2]);
		}

		double BinomialTheta(double V0, std::vector<double> V2, double T, int N)
		{
			double Delta_t = T/N;
			return (V2[1] - V0)/(2*Delta_t);
		}



		/********************************Binomial Black Scholes From here, similar with the Binomial ones***********************/
		std::vector<double> Binomial_Black_Scholes(Option *op, int N, int begin_step)
		{
			double S = op->SpotPrice();
			double T = op->Maturity();
			double K = op->StrikePrice();
			double sig = op->Volatility();
			double r = op->InterestRate();
			double q = op->Dividend();
			std::string CallPutType = op->CallPutType();
			std::string OptionType = op->OptionType();
			
			std::vector<double> V(N+1);
			double Delta_t = T/N;
			double u = exp(sig * sqrt(Delta_t));
			double d = 1/u;
			double p_rn_u = (exp((r - q) * Delta_t) - d)/(u - d);
			double p_rn_d = 1 - p_rn_u;
			double p_rn_u_tiu = exp(- r * Delta_t) * p_rn_u;
			double p_rn_d_tiu = exp(- r * Delta_t) * p_rn_d;

			for(int i = 0; i <= N - 1; i++)
			{
				double temp = S * pow(u, N - i - 1) * pow(d, i);
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
					std::cout << "No respective Binomial tree can be called." << std::endl;
			}

			if(OptionType == "American")
			{
				for(int j = N - 2; j >= begin_step; j--)
					for(int i = 0; i <= j; i++)
					{
						double disc_price = (p_rn_u_tiu * V[i] + p_rn_d_tiu * V[i+1]);
						double excirse_value;
						if(CallPutType == "Call")
						{
							excirse_value = S * pow(u, j - i) * pow(d, i) - K;
						}
						else if(CallPutType == "Put")
						{
							excirse_value = K - S * pow(u, j - i) * pow(d, i);
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
					for(int i = 0; i <= j; i++)
						V[i] = p_rn_u_tiu * V[i] + p_rn_d_tiu * V[i+1];
			}

			return V;
		}

		double BinomialBlackScholesPrice(Option *op, int N) 
		{
			return Binomial_Black_Scholes(op, N, 0)[0];
		}

		std::vector<double> BinomialBlackScholesPriceFirstPeriod(Option *op, int N)
		{
			std::vector<double> temp = Binomial_Black_Scholes(op, N, 1);
			std::vector<double> v1(2);
			v1[0] = temp[0]; v1[1] = temp[1];
			return v1;
		}

		std::vector<double> BinomialBlackScholesPriceSecondPeriod(Option *op, int N)
		{
			std::vector<double> temp = Binomial_Black_Scholes(op, N, 2);
			std::vector<double> v2(3);
			v2[0] = temp[0]; v2[1] = temp[1]; v2[2] = temp[2];
			return v2;
		}

		double BinomialBlackScholesDelta(std::vector<double> S1, std::vector<double> V1)
		{
			return (V1[0] - V1[1])/(S1[0] - S1[1]);
		}

		double BinomialBlackScholesGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2)
		{
			double temp1 = (V2[0] - V2[1])/(S2[0] - S2[1]);
			double temp2 = (V2[1] - V2[2])/(S2[1] - S2[2]);

			return 2 * (temp1 - temp2)/(S2[0] - S2[2]);
		}

		double BinomialBlackScholesTheta(double V0, std::vector<double> V2, double T, int N)
		{
			double Delta_t = T/N;

			return (V2[1] - V0)/(2*Delta_t);
		}

		
		/************************************ Binomial Tree global functions stop here ******************************************/
		/*********************** From here, we begin to declare the Trinomial Tree global functions *****************************/
/*
		std::vector<double> TrinomialSpotFirstPeriod(double S, double T, double sig, int N)
		{
			double Delta_t = T/N;
			double u = exp(sig * sqrt(3 * Delta_t));
			double d = 1/u;
			std::vector<double> s1(3);
			s1[0] = S * u; s1[1] = S; s1[2] = S * d;
			return s1;
		}

		std::vector<double> TrinomialSpotSecondPeriod(double S, double T, double sig, int N)
		{
			double Delta_t = T/N;
			double u = exp(sig * sqrt(3 * Delta_t));
			double d = 1/u;
			std::vector<double> s2(5);
			s2[0] = S * u * u; s2[1] = S * u; s2[2] = S; s2[3] = S * d; s2[4] = S * d * d;
			return s2;
		}


		std::vector<double> Trinomial_Tree(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType, int begin_step)
		{
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

			return V;
		}
	

		double TrinomialPrice(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{	
			return Trinomial_Tree(S, T, K, sig, r, q, N, CallPutType, OptionType, 0)[0];
		}

		std::vector<double> TrinomialPriceFirstPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{	
			std::vector<double> temp = Trinomial_Tree(S, T, K, sig, r, q, N, CallPutType, OptionType, 1);
			std::vector<double> v1(3);
			v1[0] = temp[0]; v1[1] = temp[1]; v1[2] = temp[2];
			return v1;
		}

		std::vector<double> TrinomialPriceSecondPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> temp = Trinomial_Tree(S, T, K, sig, r, q, N, CallPutType, OptionType, 2);
			std::vector<double> v2(5);
			v2[0] = temp[0]; v2[1] = temp[1]; v2[2] = temp[2];v2[3] = temp[3];v2[4] = temp[4];
			return v2;
		}


		double TrinomialDelta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> V1 = TrinomialPriceFirstPeriod(S, T, K, sig, r, q, N, CallPutType, OptionType);
			std::vector<double> S1 = TrinomialSpotFirstPeriod(S, T, sig, N);
			return (V1[0] - V1[2])/(S1[0] - S1[2]);
		}

		double TrinomialGamma(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> V2 = TrinomialPriceSecondPeriod(S, T, K, sig, r, q, N, CallPutType, OptionType);

			std::vector<double> S1 = TrinomialSpotFirstPeriod(S, T, sig, N);
			std::vector<double> S2 = TrinomialSpotSecondPeriod(S, T, sig, N);

			double temp1 = (V2[0] - V2[2])/(S2[0] - S2[2]);
			double temp2 = (V2[2] - V2[4])/(S2[2] - S2[4]);

			return (temp1 - temp2)/(S1[0] - S1[2]);
		}

		double TrinomialTheta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> V1 = TrinomialPriceFirstPeriod(S, T, K, sig, r, q, N, CallPutType, OptionType);

			double Delta_t = T/N;

			return (V1[1] - TrinomialPrice(S, T, K, sig, r, q, N, CallPutType, OptionType))/(Delta_t);
		}
*/
		/*************************/
/*		std::vector<double> Trinomial_Black_Scholes(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType, int begin_step)
		{
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
					V[i] = EuropeanOptionSpace::CallPrice(temp, Delta_t, K, sig, r, q);
				else if(CallPutType == "Put")
					V[i] = EuropeanOptionSpace::PutPrice(temp, Delta_t, K, sig, r, q);
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

	


		double TrinomialBlackScholesPrice(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType) 
		{
			return Trinomial_Black_Scholes(S, T, K, sig, r, q, N, CallPutType, OptionType, 0)[0];
		}

		std::vector<double> TrinomialBlackScholesPriceFirstPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> temp = Trinomial_Black_Scholes(S, T, K, sig, r, q, N, CallPutType, OptionType, 1);
			std::vector<double> v1(3);
			v1[0] = temp[0]; v1[1] = temp[1]; v1[2] = temp[2];
			return v1;
		}

		std::vector<double> TrinomialBlackScholesPriceSecondPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> temp = Trinomial_Black_Scholes(S, T, K, sig, r, q, N, CallPutType, OptionType, 2);
			std::vector<double> v2(5);
			v2[0] = temp[0]; v2[1] = temp[1]; v2[2] = temp[2]; v2[3] = temp[3]; v2[4] = temp[4];
			return v2;
		}

		double TrinomialBlackScholesDelta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> V1 = TrinomialBlackScholesPriceFirstPeriod(S, T, K, sig, r, q, N, CallPutType, OptionType);
			std::vector<double> S1 = TrinomialSpotFirstPeriod(S, T, sig, N);
			return (V1[0] - V1[2])/(S1[0] - S1[2]);
		}

		double TrinomialBlackScholesGamma(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> V2 = TrinomialBlackScholesPriceSecondPeriod(S, T, K, sig, r, q, N, CallPutType, OptionType);

			std::vector<double> S1 = TrinomialSpotFirstPeriod(S, T, sig, N);
			std::vector<double> S2 = TrinomialSpotSecondPeriod(S, T, sig, N);

			double temp1 = (V2[0] - V2[2])/(S2[0] - S2[2]);
			double temp2 = (V2[2] - V2[4])/(S2[2] - S2[4]);

			return (temp1 - temp2)/(S1[0] - S1[2]);
		}

		double TrinomialBlackScholesTheta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType)
		{
			std::vector<double> V1 = TrinomialBlackScholesPriceFirstPeriod(S, T, K, sig, r, q, N, CallPutType, OptionType);

			double Delta_t = T/N;

			return (V1[1] - TrinomialBlackScholesPrice(S, T, K, sig, r, q, N, CallPutType, OptionType))/(Delta_t);
		}
		*/
	}
}

