// This file was created to have a Binomial Black Scholes With Richardson Extrapolation with Variance 
// Reduction class derived from 
// Binomial Black Scholes Tree
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY



#ifndef BINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_CPP
#define BINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_CPP

#include "BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction.hpp"

namespace Derivatives
{
	namespace BTS = BinomialTreeSpace;
	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction() : BinomialBlackScholesWithRichardsonExtrapolation()
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction(DerivativeType& new_euro_option, int N)
		: BinomialBlackScholesWithRichardsonExtrapolation(new_euro_option, N)
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction
		(const BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source)
		: BinomialBlackScholesWithRichardsonExtrapolation(source)
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::~BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction()
	{
	}

	// Assignment
	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& 
		BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::operator =
		(const BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Binomial Black Scholes with Richardson Extrapolation with Variance Reduction are the same" << std::endl;
			return *this;
		}
		
		BinomialBlackScholesWithRichardsonExtrapolation::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Who()
	{
		return "BinomialBlackScholesRichardExtrapolateVarianceReduction";
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::V_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();

		double bbsre_price = BinomialBlackScholesWithRichardsonExtrapolation::V_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		return bbsre_price - error;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Delta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		
		double bbsre_delta = BinomialBlackScholesWithRichardsonExtrapolation::Delta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}

		return bbsre_delta - error;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Gamma_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		
		double bbsre_gamma = BinomialBlackScholesWithRichardsonExtrapolation::Gamma_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}

		return bbsre_gamma - error;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Theta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		
		double bbsre_theta = BinomialBlackScholesWithRichardsonExtrapolation::Theta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}

		return bbsre_theta - error;
	}
}

#endif