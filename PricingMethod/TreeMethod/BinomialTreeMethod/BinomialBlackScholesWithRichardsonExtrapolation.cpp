// This file was created to have a Binomial Black Scholes With Richardson Extrapolation class derived from 
// Binomial Black Scholes Tree
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY

#ifndef BINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATION_CPP
#define BINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATION_CPP

#include "BinomialBlackScholesWithRichardsonExtrapolation.hpp"

namespace Derivatives
{
	namespace TS = BinomialTreeSpace;
	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::BinomialBlackScholesWithRichardsonExtrapolation() : Tree()
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::BinomialBlackScholesWithRichardsonExtrapolation
		(DerivativeType& new_euro_option, int N) : Tree(new_euro_option, N)
	{
		// For N steps
		Tree_Price_time_0 = BinomialTreeSpace::BinomialBlackScholesPrice(&new_euro_option, N);		
		Tree_Price_time_1 = BinomialTreeSpace::BinomialBlackScholesPriceFirstPeriod(&new_euro_option, N);	
		Tree_Price_time_2 = BinomialTreeSpace::BinomialBlackScholesPriceSecondPeriod(&new_euro_option, N);
		Asset_Price_time_1 = BinomialTreeSpace::BinomialSpotFirstPeriod(&new_euro_option, N);
		Asset_Price_time_2 = BinomialTreeSpace::BinomialSpotSecondPeriod(&new_euro_option, N);	

		// For N/2 steps
		Tree_Price_time_0_N_over_2 = BinomialTreeSpace::BinomialBlackScholesPrice(&new_euro_option, N/2);		
		Tree_Price_time_1_N_over_2 = BinomialTreeSpace::BinomialBlackScholesPriceFirstPeriod(&new_euro_option, N/2);	
		Tree_Price_time_2_N_over_2 = BinomialTreeSpace::BinomialBlackScholesPriceSecondPeriod(&new_euro_option, N/2);
		Asset_Price_time_1_N_over_2 = BinomialTreeSpace::BinomialSpotFirstPeriod(&new_euro_option, N/2);
		Asset_Price_time_2_N_over_2 = BinomialTreeSpace::BinomialSpotSecondPeriod(&new_euro_option, N/2);	
	}

	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::BinomialBlackScholesWithRichardsonExtrapolation
		(const BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& source) : Tree(source)
	{
	}

	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::~BinomialBlackScholesWithRichardsonExtrapolation()
	{
	}

	// Assignment
	template<typename DerivativeType>
	BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::operator =
		(const BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Binomial Black Scholes with Richardson Extrapolation are the same" << std::endl;
			return *this;
		}
		
		Tree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Who()
	{
		return "BinomialBlackScholesRichardExtrapolate";
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::V_Tree() const
	{
		double price_N = Tree_Price_time_0;
		double price_N_over_2 = Tree_Price_time_0_N_over_2;

		return 2 * price_N - price_N_over_2;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Delta_Tree() const
	{
		double delta_N = BinomialTreeSpace::BinomialBlackScholesDelta(Asset_Price_time_1, Tree_Price_time_1);	
		double delta_N_over_2 = BinomialTreeSpace::BinomialBlackScholesDelta(Asset_Price_time_1_N_over_2, Tree_Price_time_1_N_over_2);

		return 2 * delta_N - delta_N_over_2;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Gamma_Tree() const
	{
		double gamma_N = BinomialTreeSpace::BinomialBlackScholesGamma(Asset_Price_time_1, Asset_Price_time_2, Tree_Price_time_2);
		double gamma_N_over_2 = BinomialTreeSpace::BinomialBlackScholesGamma(Asset_Price_time_1_N_over_2, 
			Asset_Price_time_2_N_over_2, Tree_Price_time_2_N_over_2);

		return 2 * gamma_N - gamma_N_over_2;
	}

	template<typename DerivativeType>
	double BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Theta_Tree() const
	{
		double theta_N =  BinomialTreeSpace::BinomialBlackScholesTheta(Tree_Price_time_0, Tree_Price_time_2, 
			WhoBeingPriced().Maturity(), Time_Steps());

		double theta_N_over_2 = BinomialTreeSpace::BinomialBlackScholesTheta(Tree_Price_time_0_N_over_2, Tree_Price_time_2_N_over_2, 
			WhoBeingPriced().Maturity(), Time_Steps()/2);

		return 2 * theta_N - theta_N_over_2;
	}
}

#endif