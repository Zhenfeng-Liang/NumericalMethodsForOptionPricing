// This file was created to have a Trinomial Black Scholes With Richardson Extrapolation with Variance 
// Reduction class derived from Trinomial Black Scholes Tree
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_CPP
#define TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_CPP

#include "TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction() : TrinomialBlackScholesWithRichardsonExtrapolation()
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction(DerivativeType& new_euro_option, int N)
		: TrinomialBlackScholesWithRichardsonExtrapolation(new_euro_option, N)
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction
		(const TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source)
		: TrinomialBlackScholesWithRichardsonExtrapolation(source)
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>
		::~TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction()
	{
	}

	// Assignment
	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& 
		TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::operator =
		(const TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Trinomial Black Scholes with Richardson Extrapolation with Variance Reduction are the same" << std::endl;
			return *this;
		}
		
		TrinomialBlackScholesWithRichardsonExtrapolation::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Who()
	{
		return "TrinomialBlackScholesRichardsonExtrapolationVarianceReduction";
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::V_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();

		double bbsr_price = TrinomialBlackScholesWithRichardsonExtrapolation::V_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		return bbsr_price - error;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Delta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		
		double bbsr_delta = TrinomialBlackScholesWithRichardsonExtrapolation::Delta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}

		return bbsr_delta - error;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Gamma_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();

		double bbsr_gamma = TrinomialBlackScholesWithRichardsonExtrapolation::Gamma_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}

		return bbsr_gamma - error;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>::Theta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		
		double bbsr_theta = TrinomialBlackScholesWithRichardsonExtrapolation::Theta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialBlackScholesWithRichardsonExtrapolation<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}

		return bbsr_theta - error;
	}
}

#endif