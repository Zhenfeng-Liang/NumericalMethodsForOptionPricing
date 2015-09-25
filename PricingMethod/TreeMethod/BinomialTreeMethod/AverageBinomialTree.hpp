// This file was created to have a AverageBinomialTree class derived from Binomial Tree
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY


#ifndef AVERAGEBINOMIALTREE_HPP
#define AVERAGEBINOMIALTREE_HPP

#include <sstream>
#include "../Tree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class AverageBinomialTree : public Tree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	private:
		double Tree_Price_time_0_N_plus_1;				// Price at the initial point
		std::vector<double> Tree_Price_time_1_N_plus_1;  // At the time 1,the first two price
		std::vector<double> Tree_Price_time_2_N_plus_1;  // At the time 2, the first three price
		std::vector<double> Asset_Price_time_1_N_plus_1;	// At the time 1,the first two underlying price
		std::vector<double> Asset_Price_time_2_N_plus_1;	// At the time 2, the first three underlying price
	public:
		AverageBinomialTree();
		AverageBinomialTree(DerivativeType& m_euro_option, int N);
		AverageBinomialTree(const AverageBinomialTree<DerivativeType>& source);
		virtual ~AverageBinomialTree();

		// Assignment
		AverageBinomialTree<DerivativeType>& operator = (const AverageBinomialTree<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value of average binomial tree!!!
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef AVERAGEBINOMIALTREE_CPP
#include "AverageBinomialTree.cpp"
#endif

#endif