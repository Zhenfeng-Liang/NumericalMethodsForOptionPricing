// This file was created to implement Down And Out Call option's code, inheritated from Down and Out Option which is from Option
//
// Zhenfeng Liang
//
// 11/4/2014 in New York ,NY

#include "DownAndOutCall.hpp"
#include <iostream>

namespace Derivatives
{
	namespace EOS = EuropeanOptionSpace;

	DownAndOutCall::DownAndOutCall():DownAndOutOption()
	{
	}

	DownAndOutCall::DownAndOutCall(const DownAndOutCall& daocall):DownAndOutOption(daocall)
	{
	}

	DownAndOutCall::DownAndOutCall(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type)
		:DownAndOutOption(S, T, K, sig, r, q, B, dividend_type)
	{
	}
	
	DownAndOutCall::DownAndOutCall(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
		double div_start_t, double div_t_interval):DownAndOutOption(S, T, K, sig, r, q, B, dividend_type, div_start_t, div_t_interval)
	{
	}

	DownAndOutCall::DownAndOutCall(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:DownAndOutOption(S, T, K, sig, r, q, B, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec)
	{
	}

	DownAndOutCall::~DownAndOutCall()
	{
	}

	DownAndOutCall& DownAndOutCall::operator = (const DownAndOutCall& daocall)
	{
		if (this == &daocall) 
		{
			std::cout << "These two down and out call options are the same" << std::endl;
			return *this;
		}
		DownAndOutOption::operator = (daocall);	
		return *this;
	}

	std::string DownAndOutCall::CallPutType() const
	{
		return "Call";
	}

	double DownAndOutCall::Barrier() const
	{
		return DownAndOutOption::Barrier();
	}

	double DownAndOutCall::V_EXACT() const
	{
		if(v_store != 0)
			return v_store;

		if(Dividend_type() != "Continuous")
		{
			std::cout << "No exact value for non-continus payed dividend." << std::endl;
			return 0;
		}
		double temp1 = EOS::CallPrice(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
		double temp2 = std::pow<double>(Barrier() / SpotPrice(), 2 * GetA());
		double temp3 = EOS::CallPrice(Barrier() * Barrier() / SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
		v_store = temp1 - temp2 * temp3;
		return v_store;
	}

	double DownAndOutCall::V_EXACT(double S) const
	{
		std::cout << "You cannot use this function to change the S, please reconstruct another object to calculate this thing." << std::endl;
		return 0;
	}

	double DownAndOutCall::V_EXACT(double S, double T) const
	{
		std::cout << "You cannot use this function to change the S, please reconstruct another object to calculate this thing." << std::endl;
		return 0;
	}

	double DownAndOutCall::Delta_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact delta." << std::endl;
		return 0;
	}

	double DownAndOutCall::Gamma_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact gamma." << std::endl;
		return 0;
	}

	double DownAndOutCall::Theta_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact theta." << std::endl;
		return 0;
	}

	double DownAndOutCall::Vega_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact vega." << std::endl;
		return 0;
	}
}
