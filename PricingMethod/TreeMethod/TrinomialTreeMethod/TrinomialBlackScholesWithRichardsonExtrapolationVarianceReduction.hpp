// This file was created to have a Trinomial Black Scholes With Richardson Extrapolation with Variance 
// Reduction class derived from Trinomial Black Scholes Tree
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_HPP
#define TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_HPP

#include <sstream>
#include "TrinomialBlackScholesWithRichardsonExtrapolation.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction : 
		public TrinomialBlackScholesWithRichardsonExtrapolation<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction();
		TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction(DerivativeType& m_euro_option, int N);
		TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction
			(const TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source);
		virtual ~TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction();

		// Assignment
		TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& operator = 
			(const TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value of average binomial tree!!!
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef TRINOMIALBLACKSCHOLESWITHRICHARDSONEXTRAPOLATIONVARIANCEREDUCTION_CPP
#include "TrinomialBlackScholesWithRichardsonExtrapolationVarianceReduction.cpp"
#endif

#endif