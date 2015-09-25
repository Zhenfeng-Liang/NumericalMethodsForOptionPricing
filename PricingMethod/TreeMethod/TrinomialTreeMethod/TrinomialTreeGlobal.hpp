// This file was designed to implement global function that the trinomial tree class call
//
// Zhenfeng Liang
//
// 12/16/2014


#ifndef TrinomialTreeGlobal_HPP
#define TrinomialTreeGlobal_HPP

#include "../../../Option/Options.hpp"
#include <vector>
#include <string>

namespace Derivatives
{
	namespace TrinomialTreeSpace
	{
		// These two functions are used to generated the spot price for the 1st and 2nd 
		// periods in the trinomial tree methods
		std::vector<double> TrinomialSpotFirstPeriod(Option *op, int N);
		std::vector<double> TrinomialSpotSecondPeriod(Option *op, int N);

		// This function is similar to the Binomial_Tree function. It is also a complete version of trinomial_tree
		// function which is used to be encapsulated by the following global functions.
		std::vector<double> Trinomial_Tree(Option *op, int N, int begin_step);
		
		// These functions encapsulate the complete version above to a more compressive ones which can be called by the class
		// member functions directly.
		double TrinomialPrice(Option *op, int N);
		std::vector<double> TrinomialPriceFirstPeriod(Option *op, int N);
		std::vector<double> TrinomialPriceSecondPeriod(Option *op, int N);
		double TrinomialDelta(std::vector<double> S1, std::vector<double> V1);
		double TrinomialGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2);
		double TrinomialTheta(double V0, std::vector<double> V1, double T, int N);					
	
	

		// This function is similar to the Trinomial_Tree function. It is also a complete version of Trinomial_Black_Scholes
		// function which is used to be encapsulated by the following global functions.
		std::vector<double> Trinomial_Black_Scholes(Option *op, int N, int begin_step);
		
		// These functions encapsulate the complete version above to a more compressive ones which can be called by the class
		// member functions directly.		
		double TrinomialBlackScholesPrice(Option *op, int N);
		std::vector<double> TrinomialBlackScholesPriceFirstPeriod(Option *op, int N);
		std::vector<double> TrinomialBlackScholesPriceSecondPeriod(Option *op, int N);
		double TrinomialBlackScholesDelta(std::vector<double> S1, std::vector<double> V1);
		double TrinomialBlackScholesGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2);
		double TrinomialBlackScholesTheta(double V0, std::vector<double> V1, double T, int N);

	}
}

#endif
