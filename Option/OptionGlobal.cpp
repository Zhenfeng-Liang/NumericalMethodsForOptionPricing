// This file was designed to implement global function that the option class call
//
// Zhenfeng Liang
//
// 9/30/2014

#include <boost/math/distributions/normal.hpp>
#include <algorithm>
#include "OptionGlobal.hpp"

namespace Derivatives
{
	double N(double x)
	{ // Return the cdf of normal distribution using boost library

		boost::math::normal_distribution<> myNormal(0.0, 1.0); 
		return cdf(myNormal, x);
	}

	double n(double x)
	{ //Return the pdf of normal distribution using boost library

		boost::math::normal_distribution<> myNormal(0.0, 1.0); 
		return pdf(myNormal, x);
	}
}

namespace Derivatives
{
	namespace EuropeanOptionSpace
	{
		double CallPrice(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T )/ tmp;
			double d2 = d1 - tmp;
			return (S * exp(- q * T) * N(d1)) - (K * exp(-r * T)* N(d2));
		}

		double PutPrice(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T ) / tmp;
			double d2 = d1 - tmp;
			return (K * exp(-r * T)* N(-d2)) - (S * exp(- q *T) * N(-d1));
		}

		double CallDelta(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T )/ tmp;
			return exp(- q * T) * N(d1);
		}

		double PutDelta(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T )/ tmp;
			return -exp(- q * T) * N(-d1);
		}

		double Gamma(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T )/ tmp;
			return n(d1) * exp(- q * T)/(S * tmp);
		}

		double CallTheta(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T )/ tmp;
			double d2 = d1 - tmp;
			return ((-S) * sig * exp(- q * T) * n(d1)/(2 * sqrt(T))) + (q * S * exp(- q * T) * N(d1)) - (r * K * exp((-r)*T) * N(d2));
		}
	
		double PutTheta(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T )/ tmp;
			double d2 = d1 - tmp;
			return ((-S) * sig * exp(- q * T) * n(d1)/(2 * sqrt(T))) - (q * S * exp(- q * T) * N(-d1)) + (r * K * exp((-r)*T) * N(-d2));
		}
	
		double Vega(double S, double T, double K, double sig, double r, double q)
		{
			double tmp = sig * sqrt(T);
			double d1 = ( log(S/K) + (r - q + (sig*sig)*0.5 ) * T )/ tmp;
			return S * sqrt(T) * exp(- q * T) * n(d1);
		}
	}
}
