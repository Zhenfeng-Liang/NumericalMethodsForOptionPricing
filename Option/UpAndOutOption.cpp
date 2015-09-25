// This file was created to implement Up and Out option's code
//
// Zhenfeng Liang
//
// 12/18/2014 in New York ,NY

#include "UpAndOutOption.hpp"
#include <iostream>

namespace Derivatives
{

	UpAndOutOption::UpAndOutOption():Option()
	{
		m_B = 999999999999;			// Default to never out
		m_a = (InterestRate() - Dividend()) / (Volatility() * Volatility()) - 0.5;
	}

	UpAndOutOption::UpAndOutOption(const UpAndOutOption& daoop):Option(daoop), m_B(daoop.m_B), m_a(daoop.m_a)
	{
	}

	UpAndOutOption::UpAndOutOption(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type)
		:Option(S, T, K, sig, r, q, dividend_type), m_B(B)
	{
		m_a = (InterestRate() - Dividend()) / (Volatility() * Volatility()) - 0.5;
	}
	
	UpAndOutOption::UpAndOutOption(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
		double div_start_t, double div_t_interval):Option(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval), m_B(B)
	{
		m_a = (InterestRate() - Dividend()) / (Volatility() * Volatility()) - 0.5;
	}

	UpAndOutOption::UpAndOutOption(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
		double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec)
		:Option(S, T, K, sig, r, q, dividend_type, div_start_t, div_t_interval, div_type_vec, div_value_vec), m_B(B)
	{
		m_a = (InterestRate() - Dividend()) / (Volatility() * Volatility()) - 0.5;
	}

	UpAndOutOption::~UpAndOutOption()
	{
	}

	UpAndOutOption& UpAndOutOption::operator = (const UpAndOutOption& daoop)
	{
		if (this == &daoop) 
		{
			std::cout << "These two Down And Out Options are the same" << std::endl;
			return *this;
		}
		Option::operator = (daoop);	
		m_B = daoop.m_B;
		m_a = daoop.m_a;
		return *this;
	}

	double UpAndOutOption::Barrier() const
	{
		return m_B;
	}

	double UpAndOutOption::GetA() const
	{
		return m_a;
	}

	std::string UpAndOutOption::OptionType() const
	{
		return "UpAndOut";
	}
}
