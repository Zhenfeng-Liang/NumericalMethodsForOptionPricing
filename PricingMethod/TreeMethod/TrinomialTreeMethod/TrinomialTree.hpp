// This file was created to have a TrinomialTree class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef TRINOMIALTREE_HPP
#define TRINOMIALTREE_HPP

#include <sstream>
#include "../Tree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class TrinomialTree : public Tree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		TrinomialTree();
		TrinomialTree(DerivativeType& m_euro_option, int N);
		TrinomialTree(const TrinomialTree<DerivativeType>& source);
		virtual ~TrinomialTree();

		// Assignment
		TrinomialTree<DerivativeType>& operator = (const TrinomialTree<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef TRINOMIALTREE_CPP
#include "TrinomialTree.cpp"
#endif 

#endif