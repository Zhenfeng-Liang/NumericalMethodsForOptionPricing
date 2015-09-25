// This file was created to implement American option's code inhericated from the Option's class
//
// Zhenfeng Liang
//
// 10/8/2014 in New York ,NY

#include "AmericanOption.hpp"
#include <iostream>

using namespace std;

namespace Derivatives
{

	AmericanOption::AmericanOption():Option()
	{
	}

	AmericanOption::AmericanOption(const AmericanOption& euroop):Option(euroop)
	{
	}

	AmericanOption::AmericanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type)
		:Option(S, T, K, sig, r, q, dividend_type)
	{
	}
	
	AmericanOption::AmericanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval):Option(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval)
	{
	}

	AmericanOption::AmericanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:Option(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec)
	{
	}
	
	AmericanOption::~AmericanOption()
	{
	}

	AmericanOption& AmericanOption::operator = (const AmericanOption& euroop)
	{
		if (this == &euroop) 
		{
			std::cout << "These two American Options are the same" << endl;
			return *this;
		}
		Option::operator = (euroop);	
		return *this;
	}

	std::string AmericanOption::OptionType() const
	{
		return "American";
	}
}
