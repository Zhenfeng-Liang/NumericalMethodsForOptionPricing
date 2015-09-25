// This file was created to have a MonteCarlo Path Dependent class
//
// Zhenfeng Liang
//
// 11/4/2014 in New York ,NY

#ifndef MONTECARLOPATHDEPENDENT_HPP
#define MONTECARLOPATHDEPENDENT_HPP

#include <sstream>
#include "MonteCarlo.hpp"
#include "MonteCarloGlobal.hpp"
#include <vector>

namespace Derivatives
{
	class MonteCarloPathDepedent : public MonteCarlo
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	private:
		int m_NT;
		int m_NSIM;
	public:
		MonteCarloPathDepedent() : MonteCarlo(), m_NT(10), m_NSIM(10000){}

		MonteCarloPathDepedent(boost::shared_ptr<Option> new_op_ptr, int NT, int NSIM) : MonteCarlo(new_op_ptr), m_NT(NT), m_NSIM(NSIM)
		{
	//		boost::shared_ptr<DownAndOutOption> new_dao_ptr;
	//		new_dao_ptr = new_op_ptr;
			std::vector<double> result = MonteCarloSpace::MonteCarloPathDepedent_init_(new_op_ptr, NT, NSIM); 
			value_store = result[0];
		}
		
		MonteCarloPathDepedent(const MonteCarloPathDepedent& source) : MonteCarlo(source), m_NT(source.m_NT), m_NSIM(source.m_NSIM){}
		
		virtual ~MonteCarloPathDepedent(){}

		// Assignment
		MonteCarloPathDepedent& operator = (const MonteCarloPathDepedent& source)
		{
			if (this == &source) { std::cout << "These two binomial trees are the same" << std::endl; return *this; }
			MonteCarlo::operator = (source);
			m_NT = source.m_NT;
			m_NSIM = source.m_NSIM;
			return *this;
		}

		// Initialization
//		void _init_(const DerivativeType& op, int NT, int NSIM);

		// Return the basic info of the Option
		virtual std::string Who(){ return "I am a Monte Carlo Path Dependent Method."; }

		virtual double V_MC() const { return value_store; }

		virtual double Delta_MC() const { std::cout << "No delta_mc for path dependent option.\n"; return 0; }

		virtual double Vega_MC() const { std::cout << "No vega_mc for path dependent option.\n"; return 0; }

		virtual double V_Error() const { return std::abs(V_MC() - WhoBeingPriced()->V_EXACT()); }
	};
}

#endif