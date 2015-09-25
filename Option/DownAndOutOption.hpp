// This file was created to implement DownAndOutOption's code
//
// Zhenfeng Liang
//
// 11/4/2014 in New York ,NY

#ifndef DOWNANDOUTOPTION_HPP
#define DOWNANDOUTOPTION_HPP

#include "Option.hpp"

namespace Derivatives
{
	class DownAndOutOption : public Option
	{
	private:
		double m_B;		// Barrier
		double m_a;		// Parameter used to calculate the exact value
	public:
		DownAndOutOption();
		DownAndOutOption(const DownAndOutOption& daoop);
		DownAndOutOption(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type);
		DownAndOutOption(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
			double div_start_t, double div_t_interval);
		DownAndOutOption(double S, double T, double K, double sig, double r, double q, double B, std::string dividend_type, 
			double div_start_t, double div_t_interval, std::vector<std::string> div_type_vec, std::vector<double> div_value_vec);
		virtual ~DownAndOutOption();

		DownAndOutOption& operator = (const DownAndOutOption& daoop);

		virtual double Barrier() const;		// Note: cannot add the set function here, since m_a is decided by B, but m_a is calculated 
											// the constructor, once you finished constructed, you cannot change the m_a
		double GetA() const;

		virtual std::string OptionType() const;
	};
}

#endif