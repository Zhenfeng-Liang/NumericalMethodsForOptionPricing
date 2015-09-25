// This file was created to implement option's code
//
// Zhenfeng Liang
//
// 9/30/2014 in New York ,NY

#include "EuropeanPut.hpp"
#include <iostream>

namespace Derivatives
{
	namespace EOS = EuropeanOptionSpace;

	EuropeanPut::EuropeanPut():EuropeanOption()
	{
	}

	EuropeanPut::EuropeanPut(const EuropeanPut& europut):EuropeanOption(europut)
	{
	}

	EuropeanPut::EuropeanPut(double S, double T, double K, double sig, double r, double q, std::string dividend_type)
		:EuropeanOption(S, T, K, sig, r, q, dividend_type)
	{
	}
	
	EuropeanPut::EuropeanPut(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval):EuropeanOption(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval)
	{
	}

	EuropeanPut::EuropeanPut(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:EuropeanOption(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec)
	{
	}
	EuropeanPut::~EuropeanPut()
	{
	}

	EuropeanPut& EuropeanPut::operator = (const EuropeanPut& europut)
	{
		if (this == &europut) 
		{
			std::cout << "These two options are the same" << std::endl;
			return *this;
		}
		EuropeanOption::operator = (europut);	
		return *this;
	}

	std::string EuropeanPut::CallPutType() const
	{
		return "Put";
	}

	double EuropeanPut::V_EXACT() const
	{
		if(v_store != 0)
			return v_store;
		
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}

		v_store = EOS::PutPrice(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());

		return v_store;
	}

	double EuropeanPut::V_EXACT(double S) const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}

		return EOS::PutPrice(S, Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
	}

	double EuropeanPut::V_EXACT(double S, double T) const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}
		return EOS::PutPrice(S, T, StrikePrice(), Volatility(), InterestRate(), Dividend());
	}

	double EuropeanPut::Delta_EXACT() const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}
		if(delta_store != 0)
			return delta_store;

		delta_store = EOS::PutDelta(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());

		return delta_store;
	}

	double EuropeanPut::Gamma_EXACT() const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}

		if(gamma_store != 0)
			return gamma_store;

		gamma_store = EOS::Gamma(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());

		return gamma_store;
	}

	double EuropeanPut::Theta_EXACT() const
	{
		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}

		if(theta_store != 0)
			return theta_store;

		theta_store = EOS::PutTheta(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
		return theta_store;
	}

	double EuropeanPut::Vega_EXACT() const
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
