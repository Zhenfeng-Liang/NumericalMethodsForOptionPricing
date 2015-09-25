// This file was created to have a MonteCarlo Non Path Dependent class
//
// Zhenfeng Liang
//
// 10/31/2014 in New York ,NY

#ifndef MONTECARLONONPATHDEPENDENTVARIANCEREDUCTION_HPP
#define MONTECARLONONPATHDEPENDENTVARIANCEREDUCTION_HPP

#include <sstream>
#include "MonteCarlo.hpp"
#include "MonteCarloGlobal.hpp"
#include <vector>

namespace Derivatives
{
	class MonteCarloNonPathDepedentVarianceReduction : public MonteCarlo
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	private:
		int m_NSIM;
		std::string m_rv_generator;
		std::string m_variance_reduction_technique;
	public:
		MonteCarloNonPathDepedentVarianceReduction() : MonteCarlo() {}

		MonteCarloNonPathDepedentVarianceReduction(boost::shared_ptr<Option> new_op_ptr, int NSIM, std::string rv_generator, std::string variance_reduction_technique)	
			: MonteCarlo(new_op_ptr), m_NSIM(NSIM), m_rv_generator(rv_generator), m_variance_reduction_technique(variance_reduction_technique)
		{
			std::vector<double> result;
			if (variance_reduction_technique == "Control variate technique")
			{ 
				result = MonteCarloSpace::MonteCarloNonPathDepedent_Control_Variate_init_(new_op_ptr, NSIM, rv_generator);
			}
			else if (variance_reduction_technique == "Antithetic variables")
			{
				result = MonteCarloSpace::MonteCarloNonPathDepedent_Antithetic_Variables_init_(new_op_ptr, NSIM, rv_generator);
			}
			else if (variance_reduction_technique == "Moment matching")
			{
				result = MonteCarloSpace::MonteCarloNonPathDepedent_Moment_Matching_init_(new_op_ptr, NSIM, rv_generator);
			}
			else if(variance_reduction_technique == "Simultaneous moment matching and control variate")
			{
				result = MonteCarloSpace::MonteCarloNonPathDepedent_Control_Variate_Moment_Matching_init_(new_op_ptr, NSIM, rv_generator);
			}
			simulation_times = result[0];
			value_store = result[1];
		}
	
		MonteCarloNonPathDepedentVarianceReduction(const MonteCarloNonPathDepedentVarianceReduction& source)
			: MonteCarlo(source), m_NSIM(source.m_NSIM), m_rv_generator(source.m_rv_generator), m_variance_reduction_technique(source.m_variance_reduction_technique){}

		virtual ~MonteCarloNonPathDepedentVarianceReduction(){}

		// Assignment
		MonteCarloNonPathDepedentVarianceReduction& operator = (const MonteCarloNonPathDepedentVarianceReduction& source)
		{
			if (this == &source) { std::cout << "These two binomial trees are the same" << std::endl; return *this; }
			MonteCarlo::operator = (source);
			m_NSIM = source.m_NSIM;
			m_rv_generator = source.m_rv_generator;
			m_variance_reduction_technique = source.m_variance_reduction_technique;
			return *this;
		}
		
		int simulation_times;

		// Return the basic info of the Option
		virtual std::string Who(){ return "I am a Monte Carlo Non Path Dependent with Variance Reduction Method.";}

		virtual double V_MC() const { return value_store;}

		virtual double Delta_MC() const { std::cout << "Be careful, you are returning delta_MC of MonteCarloNonPathDepedentVarianceReduction which you did not implement\n"; return 0;}
		
		virtual double Vega_MC() const { std::cout << "Be careful, you are returning vega_MC of MonteCarloNonPathDepedentVarianceReduction which you did not implement\n"; return 0;}

		virtual double V_Error() const { return std::abs(V_MC() - WhoBeingPriced()->V_EXACT());}
	};
}

#endif