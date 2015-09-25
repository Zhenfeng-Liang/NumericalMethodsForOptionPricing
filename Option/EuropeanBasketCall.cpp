// This file was created to implement European Basket Call option's code
//
// Zhenfeng Liang
//
// 11/13/2014 in New York ,NY

#include "EuropeanBasketCall.hpp"
#include "..\PricingMethod\MonteCarlo\MonteCarloGlobal.hpp"
#include <iostream>

namespace Derivatives
{
	EuropeanBasketCall::EuropeanBasketCall()
	{
	}

	EuropeanBasketCall::EuropeanBasketCall(const EuropeanBasketCall& op):m_r(op.m_r), m_T(op.m_T),m_K(op.m_K), m_q(op.m_q),
		m_corr(op.m_corr), m_S0_1(op.m_S0_1), m_sig1(op.m_sig1), m_S0_2(op.m_S0_2), m_sig2(op.m_sig2)
	{
	}

	EuropeanBasketCall::EuropeanBasketCall(double r, double T, double K, double q, double corr, double S1, double sig1, double S2, double sig2)
		:m_r(r), m_T(T),m_K(K), m_q(q),m_corr(corr), m_S0_1(S1), m_sig1(sig1), m_S0_2(S2), m_sig2(sig2)
	{
	}
	

	EuropeanBasketCall::~EuropeanBasketCall()
	{
	}

	EuropeanBasketCall& EuropeanBasketCall::operator = (const EuropeanBasketCall& op)
	{
		if (this == &op) 
		{
			std::cout << "These two options are the same" << std::endl;
			return *this;
		}
		m_r = op.m_r; m_T = op.m_T; m_K = op.m_K;  m_q = op.m_q;
		m_corr = op.m_corr;  m_S0_1 = op.m_S0_1; m_sig1 = op.m_sig1;  m_S0_2 = op.m_S0_2;  m_sig2 = op.m_sig2;
		return *this;
	}

	std::string EuropeanBasketCall::CallPutType() const
	{
		return "Call";
	}

	double EuropeanBasketCall::V_MC_Non_Path_Depedent(int N) const
	{
		std::vector<double> result = MonteCarloSpace::MonteCarloNonPathDepedent_Basket_Option_init_(m_r, m_T, m_K, m_q, m_corr, m_S0_1, m_sig1, m_S0_2, m_sig2, N, CallPutType(), "Box Muller Method");
		return result[1];
	}

	double EuropeanBasketCall::V_MC_Path_Depedent(int m, int n) const
	{
		std::vector<double> result = MonteCarloSpace::MonteCarloPathDepedent_Basket_Option_init_(m_r, m_T, m_K, m_q, m_corr, m_S0_1, m_sig1, m_S0_2, m_sig2, m, n, CallPutType(), "Box Muller Method");
		return result[1];
	}
}
