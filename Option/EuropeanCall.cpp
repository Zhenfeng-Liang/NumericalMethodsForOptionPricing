// This file was created to implement European Call option's code, inheritated from EuropeanOption which is from Option
//
// Zhenfeng Liang
//
// 10/8/2014 in New York ,NY

#include "EuropeanCall.hpp"
#include <iostream>

namespace Derivatives
{
	namespace EOS = EuropeanOptionSpace;

	EuropeanCall::EuropeanCall():EuropeanOption()
	{
	}

	EuropeanCall::EuropeanCall(const EuropeanCall& europut):EuropeanOption(europut)
	{
	}

	EuropeanCall::EuropeanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type)
		:EuropeanOption(S, T, K, sig, r, q, dividend_type)
	{
	}
	
	EuropeanCall::EuropeanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval):EuropeanOption(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval)
	{
	}

	EuropeanCall::EuropeanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:EuropeanOption(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec)
	{
	}

	EuropeanCall::~EuropeanCall()
	{
	}

	EuropeanCall& EuropeanCall::operator = (const EuropeanCall& europut)
	{
		if (this == &europut) 
		{
			std::cout << "These two options are the same" << std::endl;
			return *this;
		}
		EuropeanOption::operator = (europut);	
		return *this;
	}

	std::string EuropeanCall::CallPutType() const
	{
		return "Call";
	}

	double EuropeanCall::V_EXACT() const
	{
		if(v_store != 0)
			return v_store;

		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}

		v_store = EOS::CallPrice(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
		return v_store;
	}

	double EuropeanCall::V_EXACT(double S) const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}

		return EOS::CallPrice(S, Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
	}

	double EuropeanCall::V_EXACT(double S, double T) const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}

		return EOS::CallPrice(S, T, StrikePrice(), Volatility(), InterestRate(), Dividend());
	}

	double EuropeanCall::Delta_EXACT() const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}
		if(delta_store != 0)
			return delta_store;

		delta_store = (EOS::CallDelta(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend()));
		return delta_store;
	}

	double EuropeanCall::Gamma_EXACT() const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}
		if(gamma_store != 0)
			return gamma_store;

		gamma_store = (EOS::Gamma(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend()));
		return gamma_store;
	}

	double EuropeanCall::Theta_EXACT() const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}
		if(theta_store != 0)
			return theta_store;

		theta_store = (EOS::CallTheta(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend()));
		return theta_store;
	}

	double EuropeanCall::Vega_EXACT() const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}
		if(vega_store != 0)
			return vega_store;

		vega_store = (EOS::Vega(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend()));
		return vega_store;
	}
}
