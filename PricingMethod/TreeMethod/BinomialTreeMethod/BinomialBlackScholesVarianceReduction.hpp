// This file was created to have a BinomialBlackScholes with variance reduction class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef BINOMIALBLACKSCHOLESVARIANCEREDUCTION_HPP
#define BINOMIALBLACKSCHOLESVARIANCEREDUCTION_HPP

#include <sstream>
#include "BinomialBlackScholes.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class BinomialBlackScholesVarianceReduction : public BinomialBlackScholes<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		BinomialBlackScholesVarianceReduction();
		BinomialBlackScholesVarianceReduction(DerivativeType& m_euro_option, int N);
		BinomialBlackScholesVarianceReduction(const BinomialBlackScholesVarianceReduction<DerivativeType>& source);
		virtual ~BinomialBlackScholesVarianceReduction();

		// Assignment
		BinomialBlackScholesVarianceReduction<DerivativeType>& operator
			= (const BinomialBlackScholesVarianceReduction<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef BINOMIALBLACKSCHOLESVARIANCEREDUCTION_CPP
#include "BinomialBlackScholesVarianceReduction.cpp"
#endif

#endif