// This file was created to implement European option's code
//
// Zhenfeng Liang
//
// 9/30/2014 in New York ,NY

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include "Option.hpp"

namespace Derivatives
{
	class EuropeanOption : public Option
	{
	public:
		EuropeanOption();
		EuropeanOption(const EuropeanOption& euroop);
		EuropeanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type);
		EuropeanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval);
		EuropeanOption(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);
		virtual ~EuropeanOption();

		EuropeanOption& operator = (const EuropeanOption& euroop);

		virtual std::string OptionType() const;
	};
}

#endif