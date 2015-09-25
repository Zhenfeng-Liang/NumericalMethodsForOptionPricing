// This file was created to implement Down And Out Call option's code, inheritated from Down and Out Option which is from Option
//
// Zhenfeng Liang
//
// 11/4/2014 in New York ,NY

#ifndef DOWNANDOUTCALL_HPP
#define DOWNANDOUTCALL_HPP

#include "DownAndOutOption.hpp"
#include "OptionGlobal.hpp"

namespace Derivatives
{
	class DownAndOutCall : public DownAndOutOption
	{
	public:
		DownAndOutCall();
		DownAndOutCall(const DownAndOutCall& daocall);
		DownAndOutCall(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type);
		DownAndOutCall(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
			double div_start_t, double div_t_interval);

		DownAndOutCall(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);
		virtual ~DownAndOutCall();

		DownAndOutCall& operator = (const DownAndOutCall& daocall);		
		
		// Return the type of european option, "Call" or "Put"
		virtual std::string CallPutType() const;
		
		virtual double Barrier() const;

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