// This file was created to implement European Basket Call option's code
//
// Zhenfeng Liang
//
// 11/13/2014 in New York ,NY

#ifndef EUROPEANBASKETCALL_HPP
#define EUROPEANBASKETCALL_HPP

#include <string>

namespace Derivatives
{
	class EuropeanBasketCall
	{
	private:
		double m_r;
		double m_T;
		double m_K;
		double m_q;

		double m_corr;
		double m_S0_1;
		double m_sig1;
		double m_S0_2;
		double m_sig2;
	public:
		EuropeanBasketCall();
		EuropeanBasketCall(const EuropeanBasketCall& op);
		EuropeanBasketCall(double r, double T, double K, double q, double corr, double S1, double sig1, double S2, double sig2);

		virtual ~EuropeanBasketCall();

		EuropeanBasketCall& operator = (const EuropeanBasketCall& op);		
		
		// Return the type of european option, "Call" or "Put"
		std::string CallPutType() const;

		// Calculate the MC price, given the option, or given the spot price or given the spot price and maturity
		double V_MC_Non_Path_Depedent(int N) const;
		double V_MC_Path_Depedent(int m, int n) const;
	};
}

#endif