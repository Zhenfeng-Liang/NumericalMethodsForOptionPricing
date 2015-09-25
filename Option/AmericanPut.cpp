// This file was created to implement American Put option's code, inheritated from AmericanOption which is from Option
//
// Zhenfeng Liang
//
// 10/11/2014 in New York ,NY


#include "AmericanPut.hpp"
#include "../PricingMethod/TreeMethod/BinomialTreeMethod/BinomialTreeGlobal.hpp"
#include <iostream>

namespace Derivatives
{
	namespace TS = BinomialTreeSpace;

	AmericanPut::AmericanPut():AmericanOption()
	{
	}

	AmericanPut::AmericanPut(const AmericanPut& europut):AmericanOption(europut)
	{
	}

	AmericanPut::AmericanPut(double S, double T, double K, double sig, double r, double q, std::string dividend_type)
		:AmericanOption(S, T, K, sig, r, q, dividend_type)
	{
	}
	
	AmericanPut::AmericanPut(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval):AmericanOption(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval)
	{
	}

	AmericanPut::AmericanPut(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:AmericanOption(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec)
	{
	}
	
	AmericanPut::~AmericanPut()
	{
	}

	AmericanPut& AmericanPut::operator = (const AmericanPut& europut)
	{
		if (this == &europut) 
		{
			std::cout << "These two American Call Options are the same" << std::endl;
			return *this;
		}
		AmericanOption::operator = (europut);	
		return *this;
	}

	void AmericanPut::_init_(AmericanPut amput, int N) const
	{

		std::vector<double> S1_N = TS::BinomialSpotFirstPeriod(&amput, N);
		std::vector<double> S2_N = TS::BinomialSpotSecondPeriod(&amput, N);	
		double V0_N = TS::BinomialPrice(&amput, N);
		std::vector<double> V1_N = TS::BinomialPriceFirstPeriod(&amput, N);
		std::vector<double> V2_N = TS::BinomialPriceSecondPeriod(&amput, N);

		double delta_N = TS::BinomialDelta(S1_N, V1_N);
		double gamma_N = TS::BinomialGamma(S1_N, S2_N, V2_N);
		double theta_N = TS::BinomialTheta(V0_N, V2_N, amput.Maturity(), N);	

		std::vector<double> S1_N_1 = TS::BinomialSpotFirstPeriod(&amput, N + 1);
		std::vector<double> S2_N_1 = TS::BinomialSpotSecondPeriod(&amput, N + 1);	
		double V0_N_1 = TS::BinomialPrice(&amput, N + 1);
		std::vector<double> V1_N_1 = TS::BinomialPriceFirstPeriod(&amput, N + 1);
		std::vector<double> V2_N_1 = TS::BinomialPriceSecondPeriod(&amput, N + 1);

		double delta_N_1 = TS::BinomialDelta(S1_N_1, V1_N_1);
		double gamma_N_1 = TS::BinomialGamma(S1_N_1, S2_N_1, V2_N_1);
		double theta_N_1 = TS::BinomialTheta(V0_N_1, V2_N_1, amput.Maturity(), N + 1);

		v_store = (V0_N + V0_N_1)/2;
		delta_store = (delta_N + delta_N_1)/2;
		gamma_store = (gamma_N + gamma_N_1)/2;
		theta_store = (theta_N + theta_N_1)/2;
	}

	std::string AmericanPut::CallPutType() const
	{
		return "Put";
	}

	double AmericanPut::V_EXACT() const
	{
		if(v_store != 0)
			return v_store;
		_init_(*this, 10000);

		return v_store;
	}

	double AmericanPut::V_EXACT(double S) const
	{
		std::cout << "Change S to output Exact Value is not available for American Call Option.\n";
		return 0;
	}

	double AmericanPut::V_EXACT(double S, double T) const
	{
		std::cout << "Change S and T to output Exact Value is not available for American Put Option.\n";
		return 0;
	}


	double AmericanPut::Delta_EXACT() const
	{
		if (delta_store != 0)
			return delta_store;
		_init_(*this, 10000);
		
		return delta_store;
	}

	double AmericanPut::Gamma_EXACT() const
	{
		if(gamma_store != 0)
			return gamma_store;
		_init_(*this, 10000);

		return gamma_store;
	}

	double AmericanPut::Theta_EXACT() const
	{
		if(theta_store != 0)
			return theta_store;
		_init_(*this, 10000);

		return theta_store;
	}

	double AmericanPut::Vega_EXACT() const
	{
		std::cout << "Be careful, you did not implement Vega_exact for American Put, so return 0.\n";
		return 0;
	}
}