// This file was created to have a TrinomialBlackScholes with variance reduction class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef TRINOMIALBLACKSCHOLESVARIANCEREDUCTION_CPP
#define TRINOMIALBLACKSCHOLESVARIANCEREDUCTION_CPP

#include "TrinomialBlackScholesVarianceReduction.hpp"

namespace Derivatives
{
	namespace TTS = TrinomialTreeSpace;

	template<typename DerivativeType>
	TrinomialBlackScholesVarianceReduction<DerivativeType>::TrinomialBlackScholesVarianceReduction() : TrinomialBlackScholes()
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesVarianceReduction<DerivativeType>::TrinomialBlackScholesVarianceReduction
		(DerivativeType& new_euro_option, int N) : TrinomialBlackScholes(new_euro_option, N)
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesVarianceReduction<DerivativeType>::TrinomialBlackScholesVarianceReduction
		(const TrinomialBlackScholesVarianceReduction<DerivativeType>& source) : TrinomialBlackScholes(source)
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesVarianceReduction<DerivativeType>::~TrinomialBlackScholesVarianceReduction()
	{
	}

	// Assignment
	template<typename DerivativeType>
	TrinomialBlackScholesVarianceReduction<DerivativeType>& TrinomialBlackScholesVarianceReduction<DerivativeType>::operator
		= (const TrinomialBlackScholesVarianceReduction<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Trinomial Black Scholes with Variance Reduction are the same" << std::endl;
			return *this;
		}
		
		TrinomialBlackScholes::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string TrinomialBlackScholesVarianceReduction<DerivativeType>::Who()
	{
		return "TrinomialBlackScholesVarianceReduction";
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesVarianceReduction<DerivativeType>::V_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_price = TrinomialBlackScholes::V_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		return bbs_price - error;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesVarianceReduction<DerivativeType>::Delta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_delta = TrinomialBlackScholes::Delta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}

		return bbs_delta - error;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesVarianceReduction<DerivativeType>::Gamma_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_gamma = TrinomialBlackScholes::Gamma_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}

		return bbs_gamma - error;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesVarianceReduction<DerivativeType>::Theta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_theta = TrinomialBlackScholes::Theta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}

		return bbs_theta - error;
	}
}

#endif