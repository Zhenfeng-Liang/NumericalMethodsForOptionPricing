// This file was created to have a TrinomialBlackScholes with variance reduction class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY


#ifndef TRINOMIALBLACKSCHOLESVARIANCEREDUCTION_HPP
#define TRINOMIALBLACKSCHOLESVARIANCEREDUCTION_HPP

#include <sstream>
#include "TrinomialBlackScholes.hpp"


namespace Derivatives
{
	template<typename DerivativeType>
	class TrinomialBlackScholesVarianceReduction : public TrinomialBlackScholes<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		TrinomialBlackScholesVarianceReduction();
		TrinomialBlackScholesVarianceReduction(DerivativeType& m_euro_option, int N);
		TrinomialBlackScholesVarianceReduction(const TrinomialBlackScholesVarianceReduction<DerivativeType>& source);
		virtual ~TrinomialBlackScholesVarianceReduction();

		// Assignment
		TrinomialBlackScholesVarianceReduction<DerivativeType>& operator
			= (const TrinomialBlackScholesVarianceReduction<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef TRINOMIALBLACKSCHOLESVARIANCEREDUCTION_CPP
#include "TrinomialBlackScholesVarianceReduction.cpp"
#endif

#endif