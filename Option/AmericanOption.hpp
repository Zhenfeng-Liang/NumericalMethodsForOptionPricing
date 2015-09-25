// This file was created to implement American option's code inhericated from the Option's class
//
// Zhenfeng Liang
//
// 10/8/2014 in New York ,NY

#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP

#include "Option.hpp"

namespace Derivatives
{
	class AmericanOption : public Option
	{
	public:
		AmericanOption();
		AmericanOption(const AmericanOption& euroop);
		AmericanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type);
		AmericanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval);
		AmericanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);
		virtual ~AmericanOption();

		AmericanOption& operator = (const AmericanOption& euroop);

		virtual std::string OptionType() const;
	};
}

#endif