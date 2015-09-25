// This file was created to have a TrinomialTreeVarianceReduction class
//
// This class is only for American Option.
//
// Zhenfeng Liang
// 
// 10/12/2014 in New York ,NY
//

#ifndef TRINOMIALTREEVARIANCEREDUCTION_HPP
#define TRINOMIALTREEVARIANCEREDUCTION_HPP

#include <sstream>
#include "TrinomialTree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class TrinomialTreeVarianceReduction : public TrinomialTree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		TrinomialTreeVarianceReduction();
		TrinomialTreeVarianceReduction(DerivativeType& m_euro_option, int N);
		TrinomialTreeVarianceReduction(const TrinomialTreeVarianceReduction<DerivativeType>& source);
		virtual ~TrinomialTreeVarianceReduction();

		// Assignment
		TrinomialTreeVarianceReduction<DerivativeType>& operator = (const TrinomialTreeVarianceReduction<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef TRINOMIALTREEVARIANCEREDUCTION_CPP
#include "TrinomialTreeVarianceReduction.cpp"
#endif 

#endif