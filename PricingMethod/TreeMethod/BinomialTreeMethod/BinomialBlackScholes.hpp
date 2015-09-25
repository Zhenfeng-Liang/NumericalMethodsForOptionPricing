// This file was created to have a BinomialBlackScholes class
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY



#ifndef BINOMIALBLACKSCHOLES_HPP
#define BINOMIALBLACKSCHOLES_HPP

#include <sstream>
#include "../Tree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class BinomialBlackScholes : public Tree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		BinomialBlackScholes();
		BinomialBlackScholes(DerivativeType& m_euro_option, int N);
		BinomialBlackScholes(const BinomialBlackScholes<DerivativeType>& source);
		virtual ~BinomialBlackScholes();

		// Assignment
		BinomialBlackScholes<DerivativeType>& operator = (const BinomialBlackScholes<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef BINOMIALBLACKSCHOLES_CPP
#include "BinomialBlackScholes.cpp"
#endif

#endif