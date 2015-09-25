// This file was created to have a BinomialTreeVarianceReduction class
//
// This class is only for American Option.
//
// Zhenfeng Liang
// 
// 10/12/2014 in New York ,NY

#ifndef AVERAGEBINOMIALTREEVARIANCEREDUCTION_CPP
#define AVERAGEBINOMIALTREEVARIANCEREDUCTION_CPP

#include "AverageBinomialTreeVarianceReduction.hpp"

namespace Derivatives
{
	namespace TS = BinomialTreeSpace;

	template<typename DerivativeType>
	AverageBinomialTreeVarianceReduction<DerivativeType>::AverageBinomialTreeVarianceReduction() : AverageBinomialTree()
	{
	}

	template<typename DerivativeType>
	AverageBinomialTreeVarianceReduction<DerivativeType>::AverageBinomialTreeVarianceReduction
		(DerivativeType& new_euro_option, int N) : AverageBinomialTree(new_euro_option, N)
	{
	}

	template<typename DerivativeType>
	AverageBinomialTreeVarianceReduction<DerivativeType>::AverageBinomialTreeVarianceReduction
		(const AverageBinomialTreeVarianceReduction<DerivativeType>& source) : AverageBinomialTree(source)
	{
	}

	template<typename DerivativeType>
	AverageBinomialTreeVarianceReduction<DerivativeType>::~AverageBinomialTreeVarianceReduction()
	{
	}

	// Assignment
	template<typename DerivativeType>
	AverageBinomialTreeVarianceReduction<DerivativeType>& AverageBinomialTreeVarianceReduction<DerivativeType>::operator
		= (const AverageBinomialTreeVarianceReduction<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two average binomial trees with variance reduction are the same" << std::endl;
			return *this;
		}
		
		AverageBinomialTree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string AverageBinomialTreeVarianceReduction<DerivativeType>::Who()
	{
		return "AverageBinomialVarianceReduction";
	}

	template<typename DerivativeType>
	double AverageBinomialTreeVarianceReduction<DerivativeType>::V_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();

		double average_price = AverageBinomialTree::V_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
				op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.V_Tree() - temp.V_EXACT();
		}
		return average_price - error;
	}

	template<typename DerivativeType>
	double AverageBinomialTreeVarianceReduction<DerivativeType>::Delta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();

		double average_delta = AverageBinomialTree::Delta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Delta_Tree() - temp.Delta_EXACT();
		}

		return average_delta - error;		
	}

	template<typename DerivativeType>
	double AverageBinomialTreeVarianceReduction<DerivativeType>::Gamma_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		
		double average_gamma = AverageBinomialTree::Gamma_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Gamma_Tree() - temp.Gamma_EXACT();
		}

		return average_gamma - error;
	}

	template<typename DerivativeType>
	double AverageBinomialTreeVarianceReduction<DerivativeType>::Theta_Tree() const
	{
		DerivativeType op;
		op = WhoBeingPriced();
		
		double average_theta = AverageBinomialTree::Theta_Tree();

		double error;
		if(op.CallPutType() == "Call")
		{
			EuropeanCall temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanCall> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}
		else if(op.CallPutType() == "Put")
		{
			EuropeanPut temp(op.SpotPrice(), op.Maturity(), op.StrikePrice(), op.Volatility(), op.InterestRate(), 
			op.Dividend(), op.Dividend_type());
			AverageBinomialTree<EuropeanPut> bt(temp, Time_Steps());
			error = bt.Theta_Tree() - temp.Theta_EXACT();
		}

		return average_theta - error;

	}
}

#endif