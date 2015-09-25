// This file was created to have a BinomialTreeVarianceReduction class
//
// This class is only for American Option.
//
// Zhenfeng Liang
// 
// 10/12/2014 in New York ,NY



#ifndef AVERAGEBINOMIALTREEVARIANCEREDUCTION_HPP
#define AVERAGEBINOMIALTREEVARIANCEREDUCTION_HPP

#include <sstream>
#include "AverageBinomialTree.hpp"

namespace Derivatives
{
	template<typename DerivativeType>
	class AverageBinomialTreeVarianceReduction : public AverageBinomialTree<DerivativeType>
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	public:
		AverageBinomialTreeVarianceReduction();
		AverageBinomialTreeVarianceReduction(DerivativeType& m_euro_option, int N);
		AverageBinomialTreeVarianceReduction(const AverageBinomialTreeVarianceReduction<DerivativeType>& source);
		virtual ~AverageBinomialTreeVarianceReduction();

		// Assignment
		AverageBinomialTreeVarianceReduction<DerivativeType>& operator
			= (const AverageBinomialTreeVarianceReduction<DerivativeType>& source);
		
		// Return the basic info of the Option
		virtual std::string Who();

		//// PVMF return the tree simulation value of average binomial tree!!!
		virtual double V_Tree() const;
		virtual double Delta_Tree() const;
		virtual double Gamma_Tree() const;
		virtual double Theta_Tree() const;
	};
}

#ifndef AVERAGEBINOMIALTREEVARIANCEREDUCTION_CPP
#include "AverageBinomialTreeVarianceReduction.cpp"
#endif

#endif