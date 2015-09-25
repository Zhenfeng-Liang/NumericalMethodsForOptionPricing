// This file was created to have a AverageBinomialTree class derived from Binomial Tree
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY


#ifndef AVERAGEBINOMIALTREE_CPP
#define AVERAGEBINOMIALTREE_CPP

#include "AverageBinomialTree.hpp"

namespace Derivatives
{
	namespace TS = BinomialTreeSpace;

	template<typename DerivativeType>
	AverageBinomialTree<DerivativeType>::AverageBinomialTree() : Tree()
	{
	}

	template<typename DerivativeType>
	AverageBinomialTree<DerivativeType>::AverageBinomialTree(DerivativeType& new_euro_option, int N) : Tree(new_euro_option, N)
	{
		// For N steps
		Tree_Price_time_0 = BinomialTreeSpace::BinomialPrice(&new_euro_option, N);		
		Tree_Price_time_1 = BinomialTreeSpace::BinomialPriceFirstPeriod(&new_euro_option, N);	
		Tree_Price_time_2 = BinomialTreeSpace::BinomialPriceSecondPeriod(&new_euro_option, N);
		Asset_Price_time_1 = BinomialTreeSpace::BinomialSpotFirstPeriod(&new_euro_option, N);
		Asset_Price_time_2 = BinomialTreeSpace::BinomialSpotSecondPeriod(&new_euro_option, N);	

		// For N+1 steps
		Tree_Price_time_0_N_plus_1 = BinomialTreeSpace::BinomialPrice(&new_euro_option, N+1);		
		Tree_Price_time_1_N_plus_1 = BinomialTreeSpace::BinomialPriceFirstPeriod(&new_euro_option, N+1);	
		Tree_Price_time_2_N_plus_1 = BinomialTreeSpace::BinomialPriceSecondPeriod(&new_euro_option, N+1);
		Asset_Price_time_1_N_plus_1 = BinomialTreeSpace::BinomialSpotFirstPeriod(&new_euro_option, N+1);
		Asset_Price_time_2_N_plus_1 = BinomialTreeSpace::BinomialSpotSecondPeriod(&new_euro_option, N+1);	
	}

	template<typename DerivativeType>
	AverageBinomialTree<DerivativeType>::AverageBinomialTree(const AverageBinomialTree<DerivativeType>& source) : Tree(source)
	{
	}

	template<typename DerivativeType>
	AverageBinomialTree<DerivativeType>::~AverageBinomialTree()
	{
	}

	// Assignment
	template<typename DerivativeType>
	AverageBinomialTree<DerivativeType>& AverageBinomialTree<DerivativeType>::operator = (const AverageBinomialTree<DerivativeType>& source)
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
	std::string AverageBinomialTree<DerivativeType>::Who()
	{
		return "AverageBinomial";
	}

	template<typename DerivativeType>
	double AverageBinomialTree<DerivativeType>::V_Tree() const
	{
		double temp1 = Tree_Price_time_0;
		double temp2 = Tree_Price_time_0_N_plus_1;
		return (temp1 + temp2) / 2;
	}

	template<typename DerivativeType>
	double AverageBinomialTree<DerivativeType>::Delta_Tree() const
	{
		double temp1 = BinomialTreeSpace::BinomialDelta(Asset_Price_time_1, Tree_Price_time_1);
		
		double temp2 = BinomialTreeSpace::BinomialDelta(Asset_Price_time_1_N_plus_1, Tree_Price_time_1_N_plus_1);
		return (temp1 + temp2) / 2;
	}

	template<typename DerivativeType>
	double AverageBinomialTree<DerivativeType>::Gamma_Tree() const
	{
		double temp1 = BinomialTreeSpace::BinomialGamma(Asset_Price_time_1, Asset_Price_time_2, Tree_Price_time_2);
		
		double temp2 = BinomialTreeSpace::BinomialGamma(Asset_Price_time_1_N_plus_1, Asset_Price_time_2_N_plus_1, 
			Tree_Price_time_2_N_plus_1);
		return (temp1 + temp2) / 2;
	}

	template<typename DerivativeType>
	double AverageBinomialTree<DerivativeType>::Theta_Tree() const
	{
		double temp1 = BinomialTreeSpace::BinomialTheta(Tree_Price_time_0, Tree_Price_time_2, 
			WhoBeingPriced().Maturity(), Time_Steps());
		
		double temp2 = BinomialTreeSpace::BinomialTheta(Tree_Price_time_0_N_plus_1, Tree_Price_time_2_N_plus_1, 
			WhoBeingPriced().Maturity(), Time_Steps()+1);
		return (temp1 + temp2) / 2;
	}
}

#endif