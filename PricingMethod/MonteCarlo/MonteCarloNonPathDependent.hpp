// This file was created to have a MonteCarlo Non Path Dependent class
//
// Zhenfeng Liang
//
// 10/31/2014 in New York ,NY

#ifndef MONTECARLONONPATHDEPENDENT_HPP
#define MONTECARLONONPATHDEPENDENT_HPP

#include <sstream>
#include "MonteCarlo.hpp"
#include "MonteCarloGlobal.hpp"
#include <vector>

namespace Derivatives
{
	class MonteCarloNonPathDepedent : public MonteCarlo
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	private:
		int m_NSIM;
		std::string m_rv_generator;
	public:
		MonteCarloNonPathDepedent() : MonteCarlo() {}

		MonteCarloNonPathDepedent(boost::shared_ptr<Option> new_op_ptr, int NSIM, std::string rv_generator)	
			: MonteCarlo(new_op_ptr), m_NSIM(NSIM), m_rv_generator(rv_generator)
		{
			std::vector<double> result = MonteCarloSpace::MonteCarloNonPathDepedent_init_( new_op_ptr, NSIM, rv_generator); 
			simulation_times = result[0];
			value_store = result[1];
			delta_store = result[2];
			vega_store = result[3];
		}
	
		MonteCarloNonPathDepedent(const MonteCarloNonPathDepedent& source)
			: MonteCarlo(source), m_NSIM(source.m_NSIM), m_rv_generator(source.m_rv_generator){}

		virtual ~MonteCarloNonPathDepedent(){}

		// Assignment
		MonteCarloNonPathDepedent& operator = (const MonteCarloNonPathDepedent& source)
		{
			if (this == &source) { std::cout << "These two binomial trees are the same" << std::endl; return *this; }
			MonteCarlo::operator = (source);
			m_NSIM = source.m_NSIM;
			m_rv_generator = source.m_rv_generator;
			return *this;
		}
		
		int simulation_times;

		// Return the basic info of the Option
		virtual std::string Who(){ return "I am a Monte Carlo Non Path Dependent Method.";}

		virtual double V_MC() const { return value_store;}

		virtual double Delta_MC() const {return delta_store;}
		
		virtual double Vega_MC() const { return vega_store;}

		virtual double V_Root_Error() const { return std::sqrt(m_NSIM) * std::abs(V_MC() - WhoBeingPriced()->V_EXACT());}

		virtual double Delta_Root_Error() const { return std::sqrt(m_NSIM) * std::abs(Delta_MC() - WhoBeingPriced()->Delta_EXACT()); }
		
		virtual double Vega_Root_Error() const { return std::sqrt(m_NSIM) * std::abs(Vega_MC() - WhoBeingPriced()->Vega_EXACT()); }

		virtual double V_Error() const { return std::abs(V_MC() - WhoBeingPriced()->V_EXACT());}
	};
}

#endif