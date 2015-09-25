// This file was created to have a BinomialTreeVarianceReduction class
//
// This class is only for American Option.
//
// Zhenfeng Liang
// 
// 10/12/2014 in New York ,NY
//

#ifndef BINOMIALTREEVARIANCEREDUCTION_HPP
#define BINOMIALTREEVARIANCEREDUCTION_HPP

#include <sstream>
#include "BinomialTree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class BinomialTreeVarianceReduction : public BinomialTree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		BinomialTreeVarianceReduction();
		BinomialTreeVarianceReduction(DerivativeType& m_euro_option, int N);
		BinomialTreeVarianceReduction(const BinomialTreeVarianceReduction<DerivativeType>& source);
		virtual ~BinomialTreeVarianceReduction();

		// Assignment
		BinomialTreeVarianceReduction<DerivativeType>& operator = (const BinomialTreeVarianceReduction<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef BINOMIALTREEVARIANCEREDUCTION_CPP
#include "BinomialTreeVarianceReduction.cpp"
#endif 

#endif