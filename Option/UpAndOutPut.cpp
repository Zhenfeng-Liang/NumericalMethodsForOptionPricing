// This file was created to implement Up And Out Put option's code, inheritated from 
// Up and Out Option which is from Option
//
// Zhenfeng Liang
//
// 12/18/2014 in New York ,NY

#include "UpAndOutPut.hpp"
#include <iostream>

namespace Derivatives
{
	namespace EOS = EuropeanOptionSpace;

	UpAndOutPut::UpAndOutPut():UpAndOutOption()
	{
	}

	UpAndOutPut::UpAndOutPut(const UpAndOutPut& daocall):UpAndOutOption(daocall)
	{
	}

	UpAndOutPut::UpAndOutPut(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type)
		:UpAndOutOption(S, T, K, sig, r, q, B, dividend_type)
	{
	}
	
	UpAndOutPut::UpAndOutPut(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
		double div_start_t, double div_t_interval):UpAndOutOption(S, T, K, sig, r, q, B, dividend_type, div_start_t, div_t_interval)
	{
	}

	UpAndOutPut::UpAndOutPut(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:UpAndOutOption(S, T, K, sig, r, q, B, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec)
	{
	}

	UpAndOutPut::~UpAndOutPut()
	{
	}

	UpAndOutPut& UpAndOutPut::operator = (const UpAndOutPut& daocall)
	{
		if (this == &daocall) 
		{
			std::cout << "These two down and out call options are the same" << std::endl;
			return *this;
		}
		UpAndOutOption::operator = (daocall);	
		return *this;
	}

	std::string UpAndOutPut::CallPutType() const
	{
		return "Put";
	}

	double UpAndOutPut::Barrier() const
	{
		return UpAndOutOption::Barrier();
	}

	double UpAndOutPut::V_EXACT() const
	{
		std::cout << "You don't have V_exact for Up and Out Put Option.\n" << std::endl;
		//if(v_store != 0)
		//	return v_store;

		//if(Dividend_type() != "Continuous")
		//{
		//	std::cout << "No exact value for non-continus payed dividend." << std::endl;
		//	return 0;
		//}
		//double temp1 = EOS::CallPrice(SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
		//double temp2 = std::pow<double>(Barrier() / SpotPrice(), 2 * GetA());
		//double temp3 = EOS::CallPrice(Barrier() * Barrier() / SpotPrice(), Maturity(), StrikePrice(), Volatility(), InterestRate(), Dividend());
		//v_store = temp1 - temp2 * temp3;
		return v_store;
	}

	double UpAndOutPut::V_EXACT(double S) const
	{
		std::cout << "You cannot use this function to change the S, please reconstruct another object to calculate this thing." << std::endl;
		return 0;
	}

	double UpAndOutPut::V_EXACT(double S, double T) const
	{
		std::cout << "You cannot use this function to change the S, please reconstruct another object to calculate this thing." << std::endl;
		return 0;
	}

	double UpAndOutPut::Delta_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact delta." << std::endl;
		return 0;
	}

	double UpAndOutPut::Gamma_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact gamma." << std::endl;
		return 0;
	}

	double UpAndOutPut::Theta_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact theta." << std::endl;
		return 0;
	}

	double UpAndOutPut::Vega_EXACT() const
	{
		std::cout << "There is no way to calculate Down and Out Call exact vega." << std::endl;
		return 0;
	}
}
