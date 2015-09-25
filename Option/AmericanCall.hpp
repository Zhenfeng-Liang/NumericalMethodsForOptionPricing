// This file was created to implement American Call option's code, inheritated from AmericanOption which is from Option
//
// Zhenfeng Liang
//
// 12/17/2014 in New York ,NY


#ifndef AMERICANCALL_HPP
#define AMERICANCALL_HPP

#include "AmericanOption.hpp"
#include "OptionGlobal.hpp"

namespace Derivatives
{
	class AmericanCall : public AmericanOption
	{
	public:
		AmericanCall();
		AmericanCall(const AmericanCall& europut);
		AmericanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type);
		AmericanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval);

		AmericanCall(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);
		virtual ~AmericanCall();

		AmericanCall& operator = (const AmericanCall& europut);		
			
		// Initialization
		void _init_(AmericanCall amput, int N) const;

		// Return the type of european option, "Call" or "Put"
		virtual std::string CallPutType() const;

		// Calculate the BS price, given the option, or given the spot price or given the spot price and maturity
		// We are using the average of binomial tree values for the exact value and exact greeks for American options.
		// for N = 10000, and N = 10001
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