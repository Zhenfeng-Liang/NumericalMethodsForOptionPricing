// This file was created to be a parent class of tree method. Binomial tree,  Binomial average, BBS, BBSR
//
// Zhenfeng Liang
//
// 10/7/2014 in New York ,NY

#ifndef TREE_HPP
#define TREE_HPP

#include <sstream>
#include "../../Option/Options.hpp"
#include "BinomialTreeMethod/BinomialTreeGlobal.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class Tree
	{// This class accept DerivativeType as a private member, we can change it to a template class later

	private:
		DerivativeType& m_option;
		int m_N;		// Time steps of the tree
	public:
		Tree();
		Tree(DerivativeType& m_euro_option, int N);
		Tree(const Tree<DerivativeType>& new_tree);
		virtual ~Tree();

		// Assignment
		Tree<DerivativeType>& operator = (const Tree& source);
		
		double Tree_Price_time_0;				// Price at the initial point
		std::vector<double> Tree_Price_time_1;  // At the time 1,the first two price
		std::vector<double> Tree_Price_time_2;  // At the time 2, the first three price
		std::vector<double> Asset_Price_time_1;	// At the time 1,the first two underlying price
		std::vector<double> Asset_Price_time_2;	// At the time 2, the first three underlying price

		// The derivatives that the tree is pricing
		DerivativeType& WhoBeingPriced() const;
		
		// Return the time steps of the tree
		int Time_Steps() const;

		// Return the basic info of the tree
		virtual std::string Who() = 0;

		// PVMF return the tree simulation value including Binomial Tree, Average Binomial Tree, Binomial Black Scholes, Binomial Black
		// Scholes with Richardson Extrapolation. All you need to do is create these derived class's object and call the functions below respectively.
		virtual double V_Tree() const = 0;
		virtual double Delta_Tree() const = 0;
		virtual double Gamma_Tree() const = 0;
		virtual double Theta_Tree() const = 0;
		
		// Return error about the tree simulation, same as the simulation result functions. But these are not PVMF, since for all the derived class,
		// the method to calculate these errors should be the same. BUT THE IMPORTANT THING FOR THE PROGRAMMER IS TO ENCAPSULATE ALL THE SIMULATION
		// RESULT FUNCTIONS INTO THE SAME FUNCTIONS NAME!!! NOTICE!!!
		virtual double V_Error() const;
		virtual double V_Linear_Error() const;
		virtual double V_Quadratic_Error() const;
		virtual double Delta_Error() const;
		virtual double Gamma_Error() const;
		virtual double Theta_Error() const;
	};
}

#ifndef TREE_CPP
#include "Tree.cpp"
#endif


#endif