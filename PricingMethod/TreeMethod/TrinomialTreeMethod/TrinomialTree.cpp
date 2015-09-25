// This file was created to have a TrinomialTree class
//
// Zhenfeng Liang
//
// 10/12/2014 in New York ,NY

#ifndef TRINOMIALTREE_CPP
#define TRINOMIALTREE_CPP

#include "TrinomialTree.hpp"
#include "TrinomialTreeGlobal.hpp"

namespace Derivatives
{
	namespace TTS = TrinomialTreeSpace;

	template<typename DerivativeType>
	TrinomialTree<DerivativeType>::TrinomialTree() : Tree()
	{
	}
	
	template<typename DerivativeType>
	TrinomialTree<DerivativeType>::TrinomialTree(DerivativeType& new_euro_option, int N) : Tree(new_euro_option, N)
	{
		Tree_Price_time_0 = TTS::TrinomialPrice(&new_euro_option, N);		
		Tree_Price_time_1 = TTS::TrinomialPriceFirstPeriod(&new_euro_option, N);	
		Tree_Price_time_2 = TTS::TrinomialPriceSecondPeriod(&new_euro_option, N);
		Asset_Price_time_1 = TTS::TrinomialSpotFirstPeriod(&new_euro_option, N);
		Asset_Price_time_2 = TTS::TrinomialSpotSecondPeriod(&new_euro_option, N);	
	}

	template<typename DerivativeType>
	TrinomialTree<DerivativeType>::TrinomialTree(const TrinomialTree<DerivativeType>& source) : Tree(source)
	{
	}

	template<typename DerivativeType>
	TrinomialTree<DerivativeType>::~TrinomialTree()
	{
	}

	// Assignment
	template<typename DerivativeType>
	TrinomialTree<DerivativeType>& TrinomialTree<DerivativeType>::operator = (const TrinomialTree<DerivativeType>& source)
	{
		if (this == &source) 
		{
			std::cout << "These two trinomial trees are the same" << std::endl;
			return *this;
		}
		
		Tree::operator = (source);

		return *this;
	}

	template<typename DerivativeType>
	std::string TrinomialTree<DerivativeType>::Who()
	{
		return "TrinomialTree";
	}

	template<typename DerivativeType>
	double TrinomialTree<DerivativeType>::V_Tree() const
	{
		return Tree_Price_time_0;
	}

	template<typename DerivativeType>
	double TrinomialTree<DerivativeType>::Delta_Tree() const
	{
		return TTS::TrinomialDelta(Asset_Price_time_1, Tree_Price_time_1);
	}

	template<typename DerivativeType>
	double TrinomialTree<DerivativeType>::Gamma_Tree() const
	{
		return TTS::TrinomialGamma(Asset_Price_time_1, Asset_Price_time_2, Tree_Price_time_2);
	}

	template<typename DerivativeType>
	double TrinomialTree<DerivativeType>::Theta_Tree() const
	{
		return TTS::TrinomialTheta(Tree_Price_time_0, Tree_Price_time_1, WhoBeingPriced().Maturity(), Time_Steps());
	}
}

#endif