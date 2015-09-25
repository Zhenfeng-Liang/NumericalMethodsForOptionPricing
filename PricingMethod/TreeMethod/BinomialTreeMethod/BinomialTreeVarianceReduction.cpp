// This file was created to have a BinomialTreeVarianceReduction class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef BINOMIALTREEVARIANCEREDUCTION_CPP
#define BINOMIALTREEVARIANCEREDUCTION_CPP

#include "BinomialTreeVarianceReduction.hpp"
#include <iostream>

namespace Derivatives
{
	namespace TS = BinomialTreeSpace;

	template<typename DerivativeType>
	BinomialTreeVarianceReduction<DerivativeType>::BinomialTreeVarianceReduction() : BinomialTree()
	{
	}
	
	template<typename DerivativeType>
	BinomialTreeVarianceReduction<DerivativeType>::BinomialTreeVarianceReduction(DerivativeType& new_euro_option, int N)
		: BinomialTree(new_euro_option, N)
	{
	}

	template<typename DerivativeType>
	BinomialTreeVarianceReduction<DerivativeType>::BinomialTreeVarianceReduction
		(const BinomialTreeVarianceReduction<DerivativeType>& source) : BinomialTree(source)
	{
	}

	template<typename DerivativeType>
	BinomialTreeVarianceReduction<DerivativeType>::~BinomialTreeVarianceReduction()
	{
	}

	// Assignment
	template<typename DerivativeType>
	BinomialTreeVarianceReduction<DerivativeType>& BinomialTreeVarianceReduction<DerivativeType>
		::operator = (const BinomialTreeVarianceReduction<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two binomial trees with variance reduction are the same" << std::endl;
			return *this;
		}
		
		BinomialTree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string BinomialTreeVarianceReduction<DerivativeType>::Who()
	{
		return "BinomialTreeVarianceReduction";
	}

	template<typename DerivativeType>
	double BinomialTreeVarianceReduction<DerivativeType>::V_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		//double tree_price = TS::BinomialPrice(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
		//	op.Dividend(), N, op.CallPutType(), op.OptionType());

		double tree_price = BinomialTree::V_Tree();
		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		return tree_price - error;
	}

	template<typename DerivativeType>
	double BinomialTreeVarianceReduction<DerivativeType>::Delta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();		
		//double tree_delta = TS::BinomialDelta(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
		//	op.Dividend(), N, op.CallPutType(), op.OptionType());

		double tree_delta = BinomialTree::Delta_Tree();
		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}

		return tree_delta - error;
	}

	template<typename DerivativeType>
	double BinomialTreeVarianceReduction<DerivativeType>::Gamma_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();		
		//double tree_gamma = TS::BinomialGamma(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
		//	op.Dividend(), N, op.CallPutType(), op.OptionType());

		double tree_gamma = BinomialTree::Gamma_Tree();
		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}

		return tree_gamma - error;
	}

	template<typename DerivativeType>
	double BinomialTreeVarianceReduction<DerivativeType>::Theta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();		
		//double tree_theta = TS::BinomialTheta(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
		//	op.Dividend(), N, op.CallPutType(), op.OptionType());

		double tree_theta = BinomialTree::Theta_Tree();
		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			BinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}

		return tree_theta - error;
	}
}

#endif