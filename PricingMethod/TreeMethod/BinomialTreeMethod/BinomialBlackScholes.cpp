// This file was created to have a BinomialTree class
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,N


#ifndef BINOMIALBLACKSCHOLES_CPP
#define BINOMIALBLACKSCHOLES_CPP

#include "BinomialBlackScholes.hpp"

namespace Derivatives
{
	namespace TS = BinomialTreeSpace;

	template<typename DerivativeType>
	BinomialBlackScholes<DerivativeType>::BinomialBlackScholes() : Tree()
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholes<DerivativeType>::BinomialBlackScholes(DerivativeType& new_euro_option, int N) : Tree(new_euro_option, N)
	{
		Tree_Price_time_0 = BinomialTreeSpace::BinomialBlackScholesPrice(&new_euro_option, N);		
		Tree_Price_time_1 = BinomialTreeSpace::BinomialBlackScholesPriceFirstPeriod(&new_euro_option, N);	
		Tree_Price_time_2 = BinomialTreeSpace::BinomialBlackScholesPriceSecondPeriod(&new_euro_option, N);
		Asset_Price_time_1 = BinomialTreeSpace::BinomialSpotFirstPeriod(&new_euro_option, N);
		Asset_Price_time_2 = BinomialTreeSpace::BinomialSpotSecondPeriod(&new_euro_option, N);	
	}

	template<typename DerivativeType>
	BinomialBlackScholes<DerivativeType>::BinomialBlackScholes(const BinomialBlackScholes<DerivativeType>& source) : Tree(source)
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholes<DerivativeType>::~BinomialBlackScholes()
	{
	}

	// Assignment
	template<typename DerivativeType>
	BinomialBlackScholes<DerivativeType>& BinomialBlackScholes<DerivativeType>::operator = (const BinomialBlackScholes<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Binomial Black Scholes trees are the same" << std::endl;
			return *this;
		}
		
		Tree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string BinomialBlackScholes<DerivativeType>::Who()
	{
		return "BinomialBlackScholes";
	}

	template<typename DerivativeType>
	double BinomialBlackScholes<DerivativeType>::V_Tree() const
	{
		return Tree_Price_time_0;
	}

	template<typename DerivativeType>
	double BinomialBlackScholes<DerivativeType>::Delta_Tree() const
	{
		return BinomialTreeSpace::BinomialBlackScholesDelta(Asset_Price_time_1, Tree_Price_time_1);
	}

	template<typename DerivativeType>
	double BinomialBlackScholes<DerivativeType>::Gamma_Tree() const
	{
		return BinomialTreeSpace::BinomialBlackScholesGamma(Asset_Price_time_1, Asset_Price_time_2, Tree_Price_time_2);
	}

	template<typename DerivativeType>
	double BinomialBlackScholes<DerivativeType>::Theta_Tree() const
	{
		return BinomialTreeSpace::BinomialBlackScholesTheta(Tree_Price_time_0, Tree_Price_time_2, WhoBeingPriced().Maturity(), Time_Steps());
	}
}

#endif