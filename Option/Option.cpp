// This file was created to implement option's code
//
// Zhenfeng Liang
//
// 9/30/2014 in New York ,NY

#include "Option.hpp"
#include <iostream>

using namespace std;

namespace Derivatives
{

	Option::Option():m_T(1.0), m_K(30),m_sig(0.3),m_r(0.03),m_S(40),m_q(0.02),
		v_store(0),delta_store(0),gamma_store(0),theta_store(0), vega_store(0)
	{
	}

	Option::Option(double S, double T, double K, double sig, double r, double q, std::string dividend_type):m_S(S),m_T(T),m_K(K),
		m_sig(sig),m_r(r),m_q(q), m_dividend_type(dividend_type),v_store(0),delta_store(0),gamma_store(0),theta_store(0), vega_store(0)
	{
	}

	Option::Option(double S, double T, double K, double sig, double r, double q, std::string dividend_type, double div_start_t, 
		double div_t_interval):m_S(S),m_T(T),m_K(K), m_sig(sig),m_r(r),m_q(q), m_dividend_type(dividend_type), 
		m_div_start_t(div_start_t), m_div_t_interval(div_t_interval),v_store(0), delta_store(0),gamma_store(0),theta_store(0), vega_store(0)
	{
	}

	Option::Option(double S, double T, double K, double sig, double r, double q, std::string dividend_type, double div_start_t, 
		double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec):m_S(S),m_T(T),m_K(K), 
		m_sig(sig),m_r(r), m_q(q), m_dividend_type(dividend_type), m_div_start_t(div_start_t), m_div_t_interval(div_t_interval), 
		m_div_type_vec(div_type_vec), m_div_value_vec(div_value_vec),v_store(0), delta_store(0),gamma_store(0),theta_store(0), vega_store(0)
	{
	}

	Option::Option(const Option& op):m_S(op.m_S),m_T(op.m_T),m_K(op.m_K),m_sig(op.m_sig),m_r(op.m_r),m_q(op.m_q),
		 v_store(op.v_store),delta_store(op.delta_store),gamma_store(op.gamma_store),theta_store(op.theta_store), vega_store(op.vega_store)
	{
		m_dividend_type = op.m_dividend_type;
		m_div_start_t = op.m_div_start_t;
		m_div_t_interval = op.m_div_t_interval;
		m_div_type_vec = op.m_div_type_vec;
		m_div_value_vec = op.m_div_value_vec;
	}
	
	Option::~Option()
	{
	}

	double Option::Maturity() const
	{
		return m_T;
	}

	void Option::Maturity(double new_T)
	{
		m_T = new_T;
	}

	double Option::StrikePrice() const
	{
		return m_K;
	}

	void Option::StrikePrice(double new_K)
	{
		m_K = new_K;
	}

	double Option::Volatility() const
	{
		return m_sig;
	}

	void Option::Volatility(double new_sig)
	{
		m_sig = new_sig;
	}

	double Option::InterestRate() const
	{
		return m_r;
	}

	void Option::InterestRate(double new_r)
	{
		m_r = new_r;
	}

	double Option::SpotPrice() const
	{
		return m_S;
	}

	void Option::SpotPrice(double new_S)
	{
		m_S = new_S;
	}

	double Option::Dividend() const
	{
		return m_q;
	}

	void Option::Dividend(double new_q)
	{
		m_q = new_q;
	}


	std::string Option::Dividend_type() const
	{
		return m_dividend_type;
	}

	double Option::Dividend_start_time() const
	{
		return m_div_start_t;
	}

	double Option::Dividend_time_interval() const
	{
		return m_div_t_interval;
	}

	std::vector<std::string> Option::Dividend_type_vec() const
	{
		return m_div_type_vec;
	}
	std::vector<double> Option::Dividend_value_vec() const
	{
		return m_div_value_vec;
	}

	Option& Option::operator = (const Option& op)
	{
		if (this == &op) 
		{
			std::cout << "These two options are the same" << endl;
			return *this;
		}

		m_T = op.m_T;
		m_K = op.m_K;
		m_sig = op.m_sig;
		m_r = op.m_r;
		m_S = op.m_S;
		m_q = op.m_q;
		v_store = op.v_store;
		delta_store = op.delta_store;
		gamma_store = op.gamma_store;
		theta_store = op.theta_store;

		m_dividend_type = op.m_dividend_type;
		m_div_start_t = op.m_div_start_t;
		m_div_t_interval = op.m_div_t_interval;
		m_div_type_vec = op.m_div_type_vec;
		m_div_value_vec = op.m_div_value_vec;

		return *this;
	}

	std::string Option::ToString()
	{
		std::stringstream ss;	
		ss<< "T = " << m_T << " K = " << m_K << " sig = " << m_sig << " r = " << m_r << " S = " << m_S << " q = " << m_q ;	
		return ss.str();
	}

	double Option::Barrier() const
	{
		std::cout << "Be careful, you are calling the Option base class Barrier function which is not correct.\n";
		return 99999999;
	}
}
