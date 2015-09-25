// This file was created to have a Trinomial Black Scholes With Richardson Extrapolation class derived from 
// Trinomial Black Scholes Tree
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY


#ifndef TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATION_HPP
#define TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATION_HPP

#include <sstream>
#include "TrinomialBlackScholes.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class TrinomialBlackScholesWithRichardsonExtrapolation : public Tree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	private:
		double Tree_Price_time_0_N_over_2;					// Price at the initial point
		std::vector<double> Tree_Price_time_1_N_over_2;		// At the time 1,the first two price
		std::vector<double> Tree_Price_time_2_N_over_2;		// At the time 2, the first three price
		std::vector<double> Asset_Price_time_1_N_over_2;	// At the time 1,the first two underlying price
		std::vector<double> Asset_Price_time_2_N_over_2;	// At the time 2, the first three underlying price
	public:
		TrinomialBlackScholesWithRichardsonExtrapolation();
		TrinomialBlackScholesWithRichardsonExtrapolation(DerivativeType& m_euro_option, int N);
		TrinomialBlackScholesWithRichardsonExtrapolation(const TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& source);
		virtual ~TrinomialBlackScholesWithRichardsonExtrapolation();

		// Assignment
		TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& operator = 
			(const TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value of average binomial tree!!!
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATION_CPP
#include "TrinomialBlackScholesWithRichardsonExtrapolation.cpp"
#endif

#endif