// This file was created to have a BinomialTree class
//
// Zhenfeng Liang
//
// 10/7/2014 in New York


#ifndef BINOMIALTREE_CPP
#define BINOMIALTREE_CPP

#include "BinomialTree.hpp"
#include "BinomialTreeGlobal.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	BinomialTree<DerivativeType>::BinomialTree() : Tree<DerivativeType>()
	{
	}
	
	template<typename DerivativeType>
	BinomialTree<DerivativeType>::BinomialTree(DerivativeType& new_euro_option, int N) : Tree<DerivativeType>(new_euro_option, N)
	{// Initialize the tree. V0, V1, V2, S1, S2

		Tree_Price_time_0 = BinomialTreeSpace::BinomialPrice(&new_euro_option, N);		
		Tree_Price_time_1 = BinomialTreeSpace::BinomialPriceFirstPeriod(&new_euro_option, N);	
		Tree_Price_time_2 = BinomialTreeSpace::BinomialPriceSecondPeriod(&new_euro_option, N);
		Asset_Price_time_1 = BinomialTreeSpace::BinomialSpotFirstPeriod(&new_euro_option, N);
		Asset_Price_time_2 = BinomialTreeSpace::BinomialSpotSecondPeriod(&new_euro_option, N);	
	}

	template<typename DerivativeType>
	BinomialTree<DerivativeType>::BinomialTree(const BinomialTree<DerivativeType>& source) : Tree<DerivativeType>(source)
	{
	}

	template<typename DerivativeType>
	BinomialTree<DerivativeType>::~BinomialTree()
	{
	}

	// Assignment
	template<typename DerivativeType>
	BinomialTree<DerivativeType>& BinomialTree<DerivativeType>::operator = (const BinomialTree<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two binomial trees are the same" << std::endl;
			return *this;
		}
		
		Tree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string BinomialTree<DerivativeType>::Who()
	{
		return "BinomialTree";
	}

	template<typename DerivativeType>
	double BinomialTree<DerivativeType>::V_Tree() const
	{
		return Tree_Price_time_0;
	}

	template<typename DerivativeType>
	double BinomialTree<DerivativeType>::Delta_Tree() const
	{
		return BinomialTreeSpace::BinomialDelta(Asset_Price_time_1, Tree_Price_time_1);
	}

	template<typename DerivativeType>
	double BinomialTree<DerivativeType>::Gamma_Tree() const
	{
		return BinomialTreeSpace::BinomialGamma(Asset_Price_time_1, Asset_Price_time_2, Tree_Price_time_2);
	}

	template<typename DerivativeType>
	double BinomialTree<DerivativeType>::Theta_Tree() const
	{
		return BinomialTreeSpace::BinomialTheta(Tree_Price_time_0, Tree_Price_time_2, WhoBeingPriced().Maturity(), Time_Steps());
	}

}

#endif