// This file was created to be a parent class of tree method. Binomial tree,  Binomial average, BBS, BBSR
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY


#ifndef TREE_CPP
#define TREE_CPP

#include "Tree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	Tree<DerivativeType>::Tree()
	{
		DerivativeType euop(41, 1, 40, 0.3, 0.03, 0.01, "Continuous");
		m_option = euop;
	}

	template<typename DerivativeType>
	Tree<DerivativeType>::Tree(DerivativeType& new_euro_option, int N):m_option(new_euro_option), m_N(N)
	{
	}

	template<typename DerivativeType>
	Tree<DerivativeType>::Tree(const Tree<DerivativeType>& new_tree):m_option(new_tree.m_option), m_N(new_tree.m_N)
	{
	}

	template<typename DerivativeType>
	Tree<DerivativeType>::~Tree()
	{
	}

	// Assignment
	template<typename DerivativeType>
	Tree<DerivativeType>& Tree<DerivativeType>::operator = (const Tree<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two trees are the same" << std::endl;
			return *this;
		}
		m_option = source.m_option;
		m_N = source.m_N;

		return *this;
	}

	template<typename DerivativeType>
	DerivativeType& Tree<DerivativeType>::WhoBeingPriced() const
	{
		return m_option;
	}

	template<typename DerivativeType>
	int Tree<DerivativeType>::Time_Steps() const
	{
		return m_N;
	}

	template<typename DerivativeType>
	double Tree<DerivativeType>::V_Error() const
	{
		return std::abs(V_Tree() - WhoBeingPriced().V_EXACT());
	}

	template<typename DerivativeType>
	double Tree<DerivativeType>::V_Linear_Error() const
	{
		return m_N * std::abs(V_Tree() - WhoBeingPriced().V_EXACT());
	}

	template<typename DerivativeType>
	double Tree<DerivativeType>::V_Quadratic_Error() const
	{
		return m_N * m_N * std::abs(V_Tree() - WhoBeingPriced().V_EXACT());
	}

	template<typename DerivativeType>
	double Tree<DerivativeType>::Delta_Error() const
	{
		return std::abs(Delta_Tree() - WhoBeingPriced().Delta_EXACT());
	}	

	template<typename DerivativeType>
	double Tree<DerivativeType>::Gamma_Error() const
	{
		return std::abs(Gamma_Tree() - WhoBeingPriced().Gamma_EXACT());
	}	

	template<typename DerivativeType>
	double Tree<DerivativeType>::Theta_Error() const
	{
		return std::abs(Theta_Tree() - WhoBeingPriced().Theta_EXACT());
	}
}

#endif