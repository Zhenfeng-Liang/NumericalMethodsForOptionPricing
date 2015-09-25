// This file was created to have a BinomialTree class
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY



#ifndef BINOMIALTREE_HPP
#define BINOMIALTREE_HPP

#include <sstream>
#include "../Tree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class BinomialTree : public Tree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		BinomialTree();
		BinomialTree(DerivativeType& m_euro_option, int N);
		BinomialTree(const BinomialTree<DerivativeType>& source);
		virtual ~BinomialTree();

		// Assignment
		BinomialTree<DerivativeType>& operator = (const BinomialTree<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef BINOMIALTREE_CPP
#include "BinomialTree.cpp"
#endif 

#endif