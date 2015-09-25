// This file was created to have a Binomial Black Scholes With Richardson Extrapolation with Variance 
// Reduction class derived from Binomial Black Scholes Tree
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY



#ifndef BINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_HPP
#define BINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_HPP

#include <sstream>
#include "BinomialBlackScholesWithRichardsonExtrapolation.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction : 
		public BinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction();
		BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction(DerivativeType& m_euro_option, int N);
		BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction
			(const BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source);
		virtual ~BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction();

		// Assignment
		BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& operator = 
			(const BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value of average binomial tree!!!
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef BINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_CPP
#include "BinomialBlackScholesWithRichardsonExtrapolationVarianceReduction.cpp"
#endif

#endif