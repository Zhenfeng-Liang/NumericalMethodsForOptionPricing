// This file was created to be a parent class of MonteCarlo path dependent method, non-path dependent, using pointer to
// the option parent class.
//
// Zhenfeng Liang
//
// 10/31/2014 in New York ,NY

#ifndef MonteCarlo_HPP
#define MonteCarlo_HPP

//#include <sstream>
#include "../../Option/Option.hpp"
//#include "MonteCarloGlobal.hpp"
#include <iosfwd>
#include "boost/shared_ptr.hpp"

//class Option;

namespace Derivatives
{
	class MonteCarlo
	{// This class accept DerivativeType as a private member, we can change it to a template class later
	private:
		boost::shared_ptr<Option> m_op_ptr;

	public:
		MonteCarlo();
		MonteCarlo(boost::shared_ptr<Option> op_ptr);
		MonteCarlo(const MonteCarlo& new_mc);
		virtual ~MonteCarlo();

		// Assignment
		MonteCarlo& operator = (const MonteCarlo& source);
		
		// Store the methods attribute
		double s_store;
		double value_store;
		double delta_store;
		double vega_store;

		// The derivatives that the MC is pricing
		boost::shared_ptr<Option> WhoBeingPriced() const;
		
		// Return the attribute of the MC
//		int N() const;

		// Return the basic info of the MC
		virtual std::string Who() = 0;

		virtual double V_MC() const = 0;
		virtual double Delta_MC() const = 0;
		virtual double Vega_MC() const = 0;
		
	};
}

#endif