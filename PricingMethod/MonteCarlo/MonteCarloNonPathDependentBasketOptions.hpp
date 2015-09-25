// This file was created to have a MonteCarlo Non Path Dependent class
//
// Zhenfeng Liang
//
// 10/31/2014 in New York ,NY

#ifndef MONTECARLONONPATHDEPENDENTBASKETOPTION_HPP
#define MONTECARLONONPATHDEPENDENTBASKETOPTION_HPP

#include <sstream>
#include "MonteCarlo.hpp"
#include "MonteCarloGlobal.hpp"
#include <vector>

namespace Derivatives
{
	class MonteCarloNonPathDepedentBasketOption : public MonteCarlo
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	private:
		boost::shared_ptr<Option> m_op_ptr2;
		double m_corr;
		int m_NSIM;
		std::string m_rv_generator;
	public:
		MonteCarloNonPathDepedentBasketOption() : MonteCarlo() {}

		MonteCarloNonPathDepedentBasketOption(boost::shared_ptr<Option> new_op_ptr1, boost::shared_ptr<Option> new_op_ptr2, double new_corr, int NSIM, std::string rv_generator)	
			: MonteCarlo(new_op_ptr1), m_op_ptr2(new_op_ptr2), m_corr(new_corr), m_NSIM(NSIM), m_rv_generator(rv_generator)
		{
			std::vector<double> result;

			result = MonteCarloSpace::MonteCarloNonPathDepedent_Basket_Option_init_(new_op_ptr1, new_op_ptr2, new_corr, NSIM, rv_generator);
			simulation_times = result[0];
			value_store = result[1];
		}
	
		MonteCarloNonPathDepedentBasketOption(const MonteCarloNonPathDepedentBasketOption& source)
			: MonteCarlo(source), m_op_ptr2(source.m_op_ptr2), m_corr(source.m_corr), m_NSIM(source.m_NSIM), m_rv_generator(source.m_rv_generator){}

		virtual ~MonteCarloNonPathDepedentBasketOption(){}

		// Assignment
		MonteCarloNonPathDepedentBasketOption& operator = (const MonteCarloNonPathDepedentBasketOption& source)
		{
			if (this == &source) { std::cout << "These two binomial trees are the same" << std::endl; return *this; }
			MonteCarlo::operator = (source);
			m_op_ptr2 = source.m_op_ptr2;
			m_corr = source.m_corr;
			m_NSIM = source.m_NSIM;
			m_rv_generator = source.m_rv_generator;
			return *this;
		}
		
		int simulation_times;

		// Return the basic info of the Option
		virtual std::string Who(){ return "I am a Monte Carlo Non Path Dependent with Variance Reduction Method.";}

		virtual double V_MC() const { return value_store;}

		virtual double Delta_MC() const { std::cout << "Be careful, you are returning delta_MC of MonteCarloNonPathDepedent Basket Option which you did not implement\n"; return 0;}
		
		virtual double Vega_MC() const { std::cout << "Be careful, you are returning vega_MC of MonteCarloNonPathDepedent Basket Option which you did not implement\n"; return 0;}
	};
}

#endif