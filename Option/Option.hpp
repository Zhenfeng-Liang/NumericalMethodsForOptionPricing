// This file was created to implement option's code
//
// Zhenfeng Liang
//
// 9/30/2014 in New York ,NY


#ifndef OPTION_HPP
#define OPTION_HPP

#include <sstream>
#include <vector>

namespace Derivatives
{
	class Option
	{
	private:
		double m_T;		// Expiry date
		double m_K;		// Strike price
		double m_sig;	// Volatility
		double m_r;		// Interest rate
		double m_S;		// Stock price
		double m_q;		// Dividend yield, if the option discrete, but not mixed, q is proportion or absolute value, if it
						// is mixed payed, let q = 0

		std::string m_dividend_type;	// "Continuous", "Discrete proportional", "Discrete fixed", "Discrete mixed"
		
		double m_div_start_t;			// Time when the first time dividend payment
		double m_div_t_interval;		// Time difference to pay another dividend

		// These two variables are defined for mixed payed dividend
		std::vector<std::string> m_div_type_vec;		// Vector used to store dividend type each time
		std::vector<double> m_div_value_vec;	// Dividend value each time, might be proportion, e.g, 0.01, or absolute value, e.g 50

	public:
		Option();

		// This constructor is designed for the continuous pay dividend
		Option(double S, double T, double K, double sig, double r, double q, std::string dividend_type);

		// This constructor is for the dividend discrete payed, not mixed
		Option(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval);

		// This constructor is for the dividend discrete mixed
		Option(double S, double T, double K, double sig, double r, double q, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);

		Option(const Option& op);
		virtual ~Option();

		// Assignment
		Option& operator = (const Option& op);

		// Variable used to store the value once it is computed. Initialize it to 0.
		// Declare them to be mutable so as to authorize the const function change them.
		mutable double v_store; 
		mutable double delta_store;
		mutable double gamma_store;
		mutable double theta_store;
		mutable double vega_store;

		// Return the basic info of the Option
		std::string ToString();

		// Access and change the option basic property
		double Maturity() const;
		void Maturity(double new_T);
		
		double StrikePrice() const;
		void StrikePrice(double new_K);

		double Volatility() const;
		void Volatility(double new_vol);

		double InterestRate() const;
		void InterestRate(double new_r);

		double SpotPrice() const;
		void SpotPrice(double new_S);

		double Dividend() const;
		void Dividend(double new_q);

		std::string Dividend_type() const;
		double Dividend_start_time() const;
		double Dividend_time_interval() const;

		std::vector<std::string> Dividend_type_vec() const;
		std::vector<double> Dividend_value_vec() const;

		virtual double Barrier() const;

		// PVMF
		virtual std::string OptionType() const = 0;
		virtual std::string CallPutType() const = 0;

		virtual double V_EXACT() const = 0;
		virtual double V_EXACT(double S) const = 0;
		virtual double V_EXACT(double S, double T) const = 0;

		virtual double Delta_EXACT() const = 0;
		virtual double Gamma_EXACT() const = 0;
		virtual double Theta_EXACT() const = 0;
		virtual double Vega_EXACT() const = 0;
	};
}

#endif