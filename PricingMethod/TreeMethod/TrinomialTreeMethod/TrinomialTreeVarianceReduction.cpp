// This file was created to have a TrinomialTreeVarianceReduction class
//
// This class is only for American Option.
//
// Zhenfeng Liang
// 
// 10/12/2014 in New York ,NY
//


#ifndef TRINOMIALTREEVARIANCEREDUCTION_CPP
#define TRINOMIALTREEVARIANCEREDUCTION_CPP

#include "TrinomialTreeVarianceReduction.hpp"
#include "TrinomialTreeGlobal.hpp"

#include <iostream>

namespace Derivatives
{
	namespace TTS = TrinomialTreeSpace;

	template<typename DerivativeType>
	TrinomialTreeVarianceReduction<DerivativeType>::TrinomialTreeVarianceReduction() : TrinomialTree()
	{
	}
	
	template<typename DerivativeType>
	TrinomialTreeVarianceReduction<DerivativeType>::TrinomialTreeVarianceReduction(DerivativeType& new_euro_option, int N)
		: TrinomialTree(new_euro_option, N)
	{
	}

	template<typename DerivativeType>
	TrinomialTreeVarianceReduction<DerivativeType>::TrinomialTreeVarianceReduction
		(const TrinomialTreeVarianceReduction<DerivativeType>& source) : TrinomialTree(source)
	{
	}

	template<typename DerivativeType>
	TrinomialTreeVarianceReduction<DerivativeType>::~TrinomialTreeVarianceReduction()
	{
	}

	// Assignment
	template<typename DerivativeType>
	TrinomialTreeVarianceReduction<DerivativeType>& TrinomialTreeVarianceReduction<DerivativeType>
		::operator = (const TrinomialTreeVarianceReduction<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two trinomial trees with variance reduction are the same" << std::endl;
			return *this;
		}
		
		TrinomialTree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string TrinomialTreeVarianceReduction<DerivativeType>::Who()
	{
		return "TrinomialTreeVarianceReduction.";
	}

	template<typename DerivativeType>
	double TrinomialTreeVarianceReduction<DerivativeType>::V_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		double tree_price = TrinomialTree::V_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		return tree_price - error;
	}

	template<typename DerivativeType>
	double TrinomialTreeVarianceReduction<DerivativeType>::Delta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();		
		double tree_delta = TrinomialTree::Delta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}

		return tree_delta - error;
	}

	template<typename DerivativeType>
	double TrinomialTreeVarianceReduction<DerivativeType>::Gamma_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();		
		double tree_gamma = TrinomialTree::Gamma_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}

		return tree_gamma - error;
	}

	template<typename DerivativeType>
	double TrinomialTreeVarianceReduction<DerivativeType>::Theta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();		
		double tree_theta = TrinomialTree::Theta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			TrinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}

		return tree_theta - error;
	}
}

#endif