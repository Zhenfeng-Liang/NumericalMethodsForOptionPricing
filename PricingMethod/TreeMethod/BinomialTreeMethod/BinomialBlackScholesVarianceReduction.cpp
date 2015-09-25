// This file was created to have a BinomialBlackScholes class
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY

#ifndef BINOMIALBLACKSCHOLESVARIANCEREDUCTION_CPP
#define BINOMIALBLACKSCHOLESVARIANCEREDUCTION_CPP

#include "BinomialBlackScholesVarianceReduction.hpp"

namespace Derivatives
{
	namespace TS = BinomialTreeSpace;

	template<typename DerivativeType>
	BinomialBlackScholesVarianceReduction<DerivativeType>::BinomialBlackScholesVarianceReduction() : BinomialBlackScholes()
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesVarianceReduction<DerivativeType>::BinomialBlackScholesVarianceReduction
		(DerivativeType& new_euro_option, int N) : BinomialBlackScholes(new_euro_option, N)
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesVarianceReduction<DerivativeType>::BinomialBlackScholesVarianceReduction
		(const BinomialBlackScholesVarianceReduction<DerivativeType>& source) : BinomialBlackScholes(source)
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesVarianceReduction<DerivativeType>::~BinomialBlackScholesVarianceReduction()
	{
	}

	// Assignment
	template<typename DerivativeType>
	BinomialBlackScholesVarianceReduction<DerivativeType>& BinomialBlackScholesVarianceReduction<DerivativeType>::operator
		= (const BinomialBlackScholesVarianceReduction<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Binomial Black Scholes with variance reduction are the same" << std::endl;
			return *this;
		}
		
		BinomialBlackScholes::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string BinomialBlackScholesVarianceReduction<DerivativeType>::Who()
	{
		return "BinomialBlackScholesVarianceReduction";
	}

	template<typename DerivativeType>
	double BinomialBlackScholesVarianceReduction<DerivativeType>::V_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_price = BinomialBlackScholes::V_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		return bbs_price - error;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesVarianceReduction<DerivativeType>::Delta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_delta = BinomialBlackScholes::Delta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}

		return bbs_delta - error;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesVarianceReduction<DerivativeType>::Gamma_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_gamma = BinomialBlackScholes::Gamma_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}

		return bbs_gamma - error;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesVarianceReduction<DerivativeType>::Theta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double bbs_theta = BinomialBlackScholes::Theta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholes<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}

		return bbs_theta - error;
	}
}

#endif