// This file was created to have a TrinomialBlackScholes class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY


#ifndef TRINOMIALBLACKSCHOLES_CPP
#define TRINOMIALBLACKSCHOLES_CPP

#include "TrinomialBlackScholes.hpp"
#include "TrinomialTreeGlobal.hpp"

namespace Derivatives
{
	namespace TTS = TrinomialTreeSpace;

	template<typename DerivativeType>
	TrinomialBlackScholes<DerivativeType>::TrinomialBlackScholes() : Tree()
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholes<DerivativeType>::TrinomialBlackScholes(DerivativeType& new_euro_option, int N)
		: Tree(new_euro_option, N)
	{
		Tree_Price_time_0 = TTS::TrinomialBlackScholesPrice(&new_euro_option, N);		
		Tree_Price_time_1 = TTS::TrinomialBlackScholesPriceFirstPeriod(&new_euro_option, N);	
		Tree_Price_time_2 = TTS::TrinomialBlackScholesPriceSecondPeriod(&new_euro_option, N);
		Asset_Price_time_1 = TTS::TrinomialSpotFirstPeriod(&new_euro_option, N);
		Asset_Price_time_2 = TTS::TrinomialSpotSecondPeriod(&new_euro_option, N);	
	}

	template<typename DerivativeType>
	TrinomialBlackScholes<DerivativeType>::TrinomialBlackScholes(const TrinomialBlackScholes<DerivativeType>& source) : Tree(source)
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholes<DerivativeType>::~TrinomialBlackScholes()
	{
	}

	// Assignment
	template<typename DerivativeType>
	TrinomialBlackScholes<DerivativeType>& TrinomialBlackScholes<DerivativeType>::operator = (const TrinomialBlackScholes<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Trinomial Black Scholes trees are the same" << std::endl;
			return *this;
		}
		
		Tree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string TrinomialBlackScholes<DerivativeType>::Who()
	{
		return "TrinomialBlackScholes";
	}

	/****************************************************************************************************************/
	template<typename DerivativeType>
	double TrinomialBlackScholes<DerivativeType>::V_Tree() const
	{
		return Tree_Price_time_0;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholes<DerivativeType>::Delta_Tree() const
	{
		return TTS::TrinomialBlackScholesDelta(Asset_Price_time_1, Tree_Price_time_1);
	}

	template<typename DerivativeType>
	double TrinomialBlackScholes<DerivativeType>::Gamma_Tree() const
	{
		return TTS::TrinomialBlackScholesGamma(Asset_Price_time_1, Asset_Price_time_2, Tree_Price_time_2);
	}

	template<typename DerivativeType>
	double TrinomialBlackScholes<DerivativeType>::Theta_Tree() const
	{
		return TTS::TrinomialBlackScholesTheta(Tree_Price_time_0, Tree_Price_time_1, WhoBeingPriced().Maturity(), Time_Steps());
	}
}

#endif