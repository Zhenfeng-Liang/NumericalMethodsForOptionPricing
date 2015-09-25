// This file was designed to implement global function that the Monte Carlo class call
//
// Zhenfeng Liang
//
// 10/31/2014


#ifndef MONTECARLOGLOBAL_HPP
#define MONTECARLOGLOBAL_HPP

#include <vector>
#include <string>
#include "boost/shared_ptr.hpp"

//#include "../../Option/Option.hpp"
class Option;
class DownAndOutOption;

namespace Derivatives
{
	namespace MonteCarloSpace
	{
		// Generate  N independent samples from the uniform distribution
		std::vector<double> LinearCongruentialGenerator(int N);

		// Given a vector of probability, return a vector of x
		std::vector<double> ApproximatingInverseNormal(std::vector<double> u);

		std::vector<double> Acceptance_Rejection(std::vector<double> u);

		std::vector<double> Box_Muller(std::vector<double> u);

		
		std::vector<double> MonteCarloNonPathDepedent_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator);
		
		std::vector<double> MonteCarloPathDepedent_init_(boost::shared_ptr<Option> new_op_ptr, int NT, int NSIM);

		std::vector<double> MonteCarloNonPathDepedent_Control_Variate_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator);

		std::vector<double> MonteCarloNonPathDepedent_Antithetic_Variables_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator);

		std::vector<double> MonteCarloNonPathDepedent_Moment_Matching_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator);

		std::vector<double> MonteCarloNonPathDepedent_Control_Variate_Moment_Matching_init_(boost::shared_ptr<Option> new_op_ptr, int N, std::string rv_generator);

//		std::vector<double> MonteCarloNonPathDepedent_Basket_Option_init_(boost::shared_ptr<Option> new_op_ptr1, boost::shared_ptr<Option> new_op_ptr2, double corr, int N, std::string rv_generator);
	
//		std::vector<double> MonteCarloPathDepedent_Basket_Option_init_(boost::shared_ptr<Option> new_op_ptr1, boost::shared_ptr<Option> new_op_ptr2, double corr, int m, int n, std::string rv_generator);

		std::vector<double> MonteCarloNonPathDepedent_Basket_Option_init_(double r, double T, double K, double q, double corr, double S1, double sig1, double S2, double sig2, int N, std::string callputtype, std::string rv_generator);

		std::vector<double> MonteCarloPathDepedent_Basket_Option_init_(double r, double T, double K, double q, double corr, double S1, double sig1, double S2, double sig2, int m, int n, std::string callputtype, std::string rv_generator);
	}
}

#endif
