// This file was designed to implement global function that the option class call
//
// Zhenfeng Liang
//
// 9/30/2014


#ifndef OPTIONGLOBAL_HPP
#define OPTIONGLOBAL_HPP

#include <boost/math/distributions/normal.hpp>
#include <vector>
#include <string>

namespace Derivatives
{
	double N(double x);
	double n(double x);

	namespace EuropeanOptionSpace
	{
		double CallPrice(double S, double T, double K, double sig, double r, double q);
		double PutPrice(double S, double T, double K, double sig, double r, double q);

		double CallDelta(double S, double T, double K, double sig, double r, double q);
		double PutDelta(double S, double T, double K, double sig, double r, double q);
		
		double Gamma(double S, double T, double K, double sig, double r, double q);
		
		double CallTheta(double S, double T, double K, double sig, double r, double q);
		double PutTheta(double S, double T, double K, double sig, double r, double q);

		double Vega(double S, double T, double K, double sig, double r, double q);
	}
}

#endif
