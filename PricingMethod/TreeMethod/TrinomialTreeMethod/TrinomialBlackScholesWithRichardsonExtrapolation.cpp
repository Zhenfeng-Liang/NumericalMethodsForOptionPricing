// This file was created to have a Trinomial Black Scholes With Richardson Extrapolation class derived from 
// Trinomial Black Scholes Tree
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATION_CPP
#define TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATION_CPP

#include "TrinomialBlackScholesWithRichardsonExtrapolation.hpp"
#include "TrinomialTreeGlobal.hpp"

namespace Derivatives
{
	namespace TTS = TrinomialTreeSpace;
	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::TrinomialBlackScholesWithRichardsonExtrapolation() : Tree()
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::TrinomialBlackScholesWithRichardsonExtrapolation
		(DerivativeType& new_euro_option, int N) : Tree(new_euro_option, N)
	{
		// For N steps
		Tree_Price_time_0 = TTS::TrinomialBlackScholesPrice(&new_euro_option, N);		
		Tree_Price_time_1 = TTS::TrinomialBlackScholesPriceFirstPeriod(&new_euro_option, N);	
		Tree_Price_time_2 = TTS::TrinomialBlackScholesPriceSecondPeriod(&new_euro_option, N);
		Asset_Price_time_1 = TTS::TrinomialSpotFirstPeriod(&new_euro_option, N);
		Asset_Price_time_2 = TTS::TrinomialSpotSecondPeriod(&new_euro_option, N);	

		// For N/2 steps
		Tree_Price_time_0_N_over_2 = TTS::TrinomialBlackScholesPrice(&new_euro_option, N/2);		
		Tree_Price_time_1_N_over_2 = TTS::TrinomialBlackScholesPriceFirstPeriod(&new_euro_option, N/2);	
		Tree_Price_time_2_N_over_2 = TTS::TrinomialBlackScholesPriceSecondPeriod(&new_euro_option, N/2);
		Asset_Price_time_1_N_over_2 = TTS::TrinomialSpotFirstPeriod(&new_euro_option, N/2);
		Asset_Price_time_2_N_over_2 = TTS::TrinomialSpotSecondPeriod(&new_euro_option, N/2);	
	}

	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::TrinomialBlackScholesWithRichardsonExtrapolation
		(const TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& source) : Tree(source)
	{
	}

	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::~TrinomialBlackScholesWithRichardsonExtrapolation()
	{
	}

	// Assignment
	template<typename DerivativeType>
	TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::operator =
		(const TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two Trinomial Black Scholes with Richardson Extrapolation are the same" << std::endl;
			return *this;
		}
		
		Tree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Who()
	{
		return "TrinomialBlackScholesRichardsonExtrapolation";
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::V_Tree() const
	{
		double price_N = Tree_Price_time_0;
		double price_N_over_2 = Tree_Price_time_0_N_over_2;

		return 2 * price_N - price_N_over_2;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Delta_Tree() const
	{
		double delta_N = TTS::TrinomialBlackScholesDelta(Asset_Price_time_1, Tree_Price_time_1);
		double delta_N_over_2 = TTS::TrinomialBlackScholesDelta(Asset_Price_time_1_N_over_2, Tree_Price_time_1_N_over_2);
		return 2 * delta_N - delta_N_over_2;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Gamma_Tree() const
	{
		double gamma_N = TTS::TrinomialBlackScholesGamma(Asset_Price_time_1, Asset_Price_time_2, Tree_Price_time_2);
		double gamma_N_over_2 = TTS::TrinomialBlackScholesGamma(Asset_Price_time_1_N_over_2, 
			Asset_Price_time_2_N_over_2, Tree_Price_time_2_N_over_2);
		return 2 * gamma_N - gamma_N_over_2;
	}

	template<typename DerivativeType>
	double TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>::Theta_Tree() const
	{
		double theta_N =  TTS::TrinomialBlackScholesTheta(Tree_Price_time_0, Tree_Price_time_1, 
			WhoBeingPriced().Maturity(), Time_Steps());

		double theta_N_over_2 = TTS::TrinomialBlackScholesTheta(Tree_Price_time_0_N_over_2, Tree_Price_time_1_N_over_2, 
			WhoBeingPriced().Maturity(), Time_Steps()/2);

		return 2 * theta_N - theta_N_over_2;
	}
}

#endif