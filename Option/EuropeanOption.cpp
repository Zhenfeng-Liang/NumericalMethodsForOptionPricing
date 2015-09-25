// This file was created to implement European option's code
//
// Zhenfeng Liang
//
// 9/30/2014 in New York ,NY

#include "EuropeanOption.hpp"
#include <iostream>

using namespace std;

namespace Derivatives
{

	EuropeanOption::EuropeanOption():Option()
	{
	}

	EuropeanOption::EuropeanOption(const EuropeanOption& euroop):Option(euroop)
	{
	}

	EuropeanOption::EuropeanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type)
		:Option(S, T, K, sig, r, q, dividend_type)
	{
	}
	
	EuropeanOption::EuropeanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval):Option(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval)
	{
	}

	EuropeanOption::EuropeanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:Option(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec)
	{
	}

	EuropeanOption::~EuropeanOption()
	{
	}

	EuropeanOption& EuropeanOption::operator = (const EuropeanOption& euroop)
	{
		if (this == &euroop) 
		{
			std::cout << "These two European Options are the same" << endl;
			return *this;
		}
		Option::operator = (euroop);	
		return *this;
	}

	std::string EuropeanOption::OptionType() const
	{
		return "European";
	}
}
