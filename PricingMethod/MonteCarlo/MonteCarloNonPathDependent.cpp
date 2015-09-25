// This file was created to have a MonteCarlo Non Path Dependent class
//
// Zhenfeng Liang
//
// 10/31/2014 in New York ,NY


#include "MonteCarloNonPathDependent.hpp"
#include "MonteCarloGlobal.hpp"
#include "../../Option/Options.hpp"
class MonteCarloNonPathDepedent;

namespace Derivatives
{
	MonteCarloNonPathDepedent::MonteCarloNonPathDependent() : MonteCarlo()
	{
	}
	
	MonteCarloNonPathDependent::MonteCarloNonPathDependent(boost::shared_ptr<Option> new_op_ptr, int NSIM, std::string rv_generator) 
		: MonteCarlo(new_op_ptr), m_NSIM(NSIM), m_rv_generator(rv_generator)
	{
		std::vector<double> result = MonteCarloSpace::MonteCarloNonPathDepedent_init_( new_op_ptr, NSIM, rv_generator); 
		simulation_times = result[0];
		value_store = result[1];
		delta_store = result[2];
		vega_store = result[3];
	}

	MonteCarloNonPathDependent::MonteCarloNonPathDependent(const MonteCarloNonPathDependent& source) 
		: MonteCarlo(source), m_NSIM(source.m_NSIM), m_rv_generator(source.m_rv_generator)
	{
	}

	MonteCarloNonPathDependent::~MonteCarloNonPathDependent()
	{
	}

	// Assignment
	MonteCarloNonPathDependent& MonteCarloNonPathDependent::operator = (const MonteCarloNonPathDependent& source)
	{
		if (this == &source) { std::cout << "These two binomial trees are the same" << std::endl; return *this; }
		MonteCarlo::operator = (source);
		m_NSIM = source.m_NSIM;
		m_rv_generator = source.m_rv_generator;
		return *this;
	}

	std::string MonteCarloNonPathDependent::Who()
	{
		return "I am a Monte Carlo Non Path Dependent Method.";
	}

	double MonteCarloNonPathDependent::V_MC() const 
	{
		return value_store; 
	}

	double MonteCarloNonPathDependent::Delta_MC() const 
	{
		return delta_store;
	}

	double MonteCarloNonPathDependent::Vega_MC() const 
	{ 
		return vega_store;
	}

	double MonteCarloNonPathDependent::V_Root_Error() const
	{ 
		return std::sqrt(m_NSIM) * std::abs(V_MC() - WhoBeingPriced()->V_EXACT()); 
	}

	double MonteCarloNonPathDependent::Delta_Root_Error() const 
	{ 
		return std::sqrt(m_NSIM) * std::abs(Delta_MC() - WhoBeingPriced()->Delta_EXACT()); 
	}
		
	double MonteCarloNonPathDependent::Vega_Root_Error() const
	{ 
		return std::sqrt(m_NSIM) * std::abs(Vega_MC() - WhoBeingPriced()->Vega_EXACT()); 
	}

	double MonteCarloNonPathDependent::V_Error() const 
	{ 
		return std::abs(V_MC() - WhoBeingPriced()->V_EXACT()); 
	}
}



