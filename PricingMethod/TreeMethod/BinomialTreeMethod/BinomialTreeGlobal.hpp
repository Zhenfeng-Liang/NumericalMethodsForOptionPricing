// This file was designed to implement global function that the tree class call
//
// Zhenfeng Liang
//
// 10/8/2014


#ifndef BinomialTreeGlobal_HPP
#define BinomialTreeGlobal_HPP

#include "../../../Option/Options.hpp"
#include <vector>
#include <string>

namespace Derivatives
{
	namespace BinomialTreeSpace
	{
		// These two functions are used to generated the spot price for the 1st and 2nd 
		// periods in the binomial tree methods
		std::vector<double> BinomialSpotFirstPeriod(Option *op, int N);
		std::vector<double> BinomialSpotSecondPeriod(Option *op, int N);

		// This is the complete version of Binomial Tree which takes all the arguments as parameters so that the other
		// function about binomial tree can use it directly. Option type mean whether it is an European Option or American Option.
		// begin_step means the period which I should discount all the tree branches values to. E.g, begin_step = 0 means to 
		// discount the value to the present period. For which I should take the first value of the return vector, Binomial_Tree[0].
		// begin_step = 1 mean to discount it to the first period. For which I should take the first two values of the return 
		// vector. Binomial_Tree[0] and Binomial_Tree[1]
		// Arguments:
		//			div_type_vec[]: Take "Fixed"/"Proportional"
		//			div_value_vec[]: Take value of the proportion or the absolute value
		
		std::vector<double> Binomial_Tree(Option *op, int N, int begin_step);

		// These functions encapsulate the complete version above to a more compressive ones which can be called by the class
		// member functions directly.
		double BinomialPrice(Option *op, int N);
		std::vector<double> BinomialPriceFirstPeriod(Option *op, int N);
		std::vector<double> BinomialPriceSecondPeriod(Option *op, int N);

		double BinomialDelta(std::vector<double> S1, std::vector<double> V1);
		double BinomialGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2);
		double BinomialTheta(double V0, std::vector<double> V2, double T, int N);			
		
		
		// This function is similar to the Binomial_Tree function. It is also a complete version of Binomial_Black_Scholes
		// function which is used to be encapsulated by the following global functions.
		std::vector<double> Binomial_Black_Scholes(Option *op, int N, int begin_step);
		
		double BinomialBlackScholesPrice(Option *op, int N);
		std::vector<double> BinomialBlackScholesPriceFirstPeriod(Option *op, int N);
		std::vector<double> BinomialBlackScholesPriceSecondPeriod(Option *op, int N);
		double BinomialBlackScholesDelta(std::vector<double> S1, std::vector<double> V1);
		double BinomialBlackScholesGamma(std::vector<double> S1, std::vector<double> S2, std::vector<double> V2);
		double BinomialBlackScholesTheta(double V0, std::vector<double> V2, double T, int N);
	

		/************************************ Binomial Tree global functions stop here ******************************************/
		/*********************** From here, we begin to declare the Trinomial Tree global functions *****************************/

/*
		// These two functions are used to generated the spot price for the 1st and 2nd 
		// periods in the trinomial tree methods
		std::vector<double> TrinomialSpotFirstPeriod(double S, double T, double sig, int N);
		std::vector<double> TrinomialSpotSecondPeriod(double S, double T, double sig, int N);

		// This function is similar to the Binomial_Tree function. It is also a complete version of trinomial_tree
		// function which is used to be encapsulated by the following global functions.
		std::vector<double> Trinomial_Tree(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType, int begin_step);
		
		// These functions encapsulate the complete version above to a more compressive ones which can be called by the class
		// member functions directly.
		double TrinomialPrice(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		std::vector<double> TrinomialPriceFirstPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		std::vector<double> TrinomialPriceSecondPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		double TrinomialDelta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		double TrinomialGamma(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		double TrinomialTheta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);					
	
	

		// This function is similar to the Trinomial_Tree function. It is also a complete version of Trinomial_Black_Scholes
		// function which is used to be encapsulated by the following global functions.
		std::vector<double> Trinomial_Black_Scholes(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType, int begin_step);
		
		// These functions encapsulate the complete version above to a more compressive ones which can be called by the class
		// member functions directly.		
		double TrinomialBlackScholesPrice(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		std::vector<double> TrinomialBlackScholesPriceFirstPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		std::vector<double> TrinomialBlackScholesPriceSecondPeriod(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		double TrinomialBlackScholesDelta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		double TrinomialBlackScholesGamma(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
		double TrinomialBlackScholesTheta(double S, double T, double K, double sig, double r, double q, int N, std::string CallPutType, std::string OptionType);
*/	
	}
}

#endif
