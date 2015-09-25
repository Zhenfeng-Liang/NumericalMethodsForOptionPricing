// This file was created to be a parent class of MonteCarlo path dependent method, non-path dependent, using pointer to
// the option parent class.
//
// Zhenfeng Liang
//
// 10/31/2014 in New York ,NY


//#ifndef MONTECARLO_CPP
//#define MONTECARLO_CPP

#include "MonteCarlo.hpp"
//#include "../../Option/Options.hpp"
namespace Derivatives
{
	MonteCarlo::MonteCarlo()
	{
		std::cout << " You didn't pass anything to price.\n";
		m_op_ptr = nullptr;
	}

	MonteCarlo::MonteCarlo(boost::shared_ptr<Option> new_op_ptr):m_op_ptr(new_op_ptr)
	{
		s_store = value_store = delta_store = vega_store = 0;
	}

	MonteCarlo::MonteCarlo(const MonteCarlo& new_mc):m_op_ptr(new_mc.m_op_ptr)
	{
		s_store = new_mc.s_store;
		value_store = new_mc.value_store;
		delta_store = new_mc.delta_store;
		vega_store = new_mc.vega_store;
	}

	MonteCarlo::~MonteCarlo()
	{
	}

	// Assignment
	MonteCarlo& MonteCarlo::operator = (const MonteCarlo& source)
	{
		if (this == &source) 
		{
			std::cout << "These two MCs are the same" << std::endl;
			return *this;
		}
		m_op_ptr = source.m_op_ptr;
//		m_N = source.m_N;
		
		s_store = source.s_store;
		value_store = source.value_store;
		delta_store = source.delta_store;
		vega_store = source.vega_store;
		return *this;
	}

	boost::shared_ptr<Option> MonteCarlo::WhoBeingPriced() const
	{
		return m_op_ptr;
	}
}
