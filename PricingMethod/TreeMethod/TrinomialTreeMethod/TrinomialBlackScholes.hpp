// This file was created to have a TrinomialBlackScholes class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY



#ifndef TRINOMIALBLACKSCHOLES_HPP
#define TRINOMIALBLACKSCHOLES_HPP

#include <sstream>
#include "../Tree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class TrinomialBlackScholes : public Tree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		TrinomialBlackScholes();
		TrinomialBlackScholes(DerivativeType& m_euro_option, int N);
		TrinomialBlackScholes(const TrinomialBlackScholes<DerivativeType>& source);
		virtual ~TrinomialBlackScholes();

		// Assignment
		TrinomialBlackScholes<DerivativeType>& operator = (const TrinomialBlackScholes<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef TRINOMIALBLACKSCHOLES_CPP
#include "TrinomialBlackScholes.cpp"
#endif

#endif