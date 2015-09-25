// This file was created to implement Up And Out Put option's code, inheritated from 
// Up and Out Option which is from Option
//
// Zhenfeng Liang
//
// 12/18/2014 in New York ,NY

#ifndef UPANDOUTPUT_HPP
#define UPANDOUTPUT_HPP

#include "UpAndOutOption.hpp"
#include "OptionGlobal.hpp"

namespace Derivatives
{
	class UpAndOutPut : public UpAndOutOption
	{
	public:
		UpAndOutPut();
		UpAndOutPut(const UpAndOutPut& daocall);
		UpAndOutPut(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type);
		UpAndOutPut(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
			double div_start_t, double div_t_interval);

		UpAndOutPut(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);
		virtual ~UpAndOutPut();

		UpAndOutPut& operator = (const UpAndOutPut& daocall);		
		
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