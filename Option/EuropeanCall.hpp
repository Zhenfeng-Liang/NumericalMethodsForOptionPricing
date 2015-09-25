// This file was created to implement European Call option's code, inheritated from EuropeanOption which is from Option
//
// Zhenfeng Liang
//
// 10/8/2014 in New York ,NY

#ifndef EUROPEANCALL_HPP
#define EUROPEANCALL_HPP

#include "EuropeanOption.hpp"
#include "OptionGlobal.hpp"

namespace Derivatives
{
	class EuropeanCall : public EuropeanOption
	{
	public:
		EuropeanCall();
		EuropeanCall(const EuropeanCall& europut);
		EuropeanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type);
		EuropeanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval);

		EuropeanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);
		virtual ~EuropeanCall();

		EuropeanCall& operator = (const EuropeanCall& europut);		
		
		// Return the type of european option, "Call" or "Put"
		virtual std::string CallPutType() const;

		// Calculate the BS price, given the option, or given the spot price or given the spot price and maturity
		virtual double V_EXACT() const;
		virtual double V_EXACT(double S) const;
		virtual double V_EXACT(double S, double T) const;

		virtual double Delta_EXACT() const;
		virtual double Gamma_EXACT() const;
		virtual double Theta_EXACT() const;
		virtual double Vega_EXACT() const;
	};
}

#endif