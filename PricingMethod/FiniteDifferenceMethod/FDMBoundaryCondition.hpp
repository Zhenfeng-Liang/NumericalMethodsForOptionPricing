// This file was created to implement the FDM Boundary Condition.
//
// Zhenfeng Liang
//
// 12/17/2014, at Elmhurst, NY

#ifndef FDMBOUNDARYCONDITION_HPP
#define FDMBOUNDARYCONDITION_HPP

/************************************************************************************************************************/
/********************************************Boundary condition**********************************************************/

namespace EuroAmerPutBC
{
	double a;
	double b;
	double K;
	double x_left;
	double r;
	double q;
	double sig;

	void init(double _a, double _b, double _K, double _x_left, double _r, double _q, double _sig) {
		a = _a; b = _b; K = _K; x_left = _x_left; r = _r; q = _q; sig = _sig;
	}

	auto f_begin = [] (double x) {
		return (K * exp(a * x) * std::max(1-exp(x), 0.0));
	};

	auto european_g_left = [] (double tao) {  
		return K * exp(a * x_left + b * tao) * (exp(-2*r*tao/(sig*sig)) - exp(x_left - 2*q*tao/(sig*sig)) );
	};

	auto american_g_left = [] (double tao) {
		return K * exp(a * x_left + b * tao) * (1 - exp(x_left)); 
	};

	auto g_right = [] (double tao) {return 0;};
	
	auto u_exact = [] (double x, double tao) {return 0;};
}

namespace EuroAmerCallBC
{
	double a;
	double b;
	double K;
	double x_right;
	double r;
	double q;
	double sig;

	void init(double _a, double _b, double _K, double _x_right, double _r, double _q, double _sig) {
		a = _a; b = _b; K = _K; x_right = _x_right; r = _r; q = _q; sig = _sig;
	}

	auto f_begin = [] (double x) {
		return (K * exp(a * x) * std::max(exp(x)-1, 0.0));
	};

	auto g_left = [] (double tao) {
		return 0; 
	};

	auto european_g_right = [] (double tao) {
		return K * exp(a * x_right + b * tao) * ( exp(x_right - 2*q*tao/(sig*sig)) - exp(-2*r*tao/(sig*sig)) );
	};

	auto american_g_right = [] (double tao) {
		return K * exp(a * x_right + b * tao) * ( exp(x_right - 2*q*tao/(sig*sig)) - exp(-2*r*tao/(sig*sig)) );
	};

	auto u_exact = [] (double x, double tao) {return 0;};
}

namespace DAOCallBC
{
	double a;
	double b;
	double K;
	double x_right;
	double r;
	double q;
	double sig;

	void init(double _a, double _b, double _K, double _x_right, double _r, double _q, double _sig) {
		a = _a; b = _b; K = _K; x_right = _x_right; r = _r; q = _q; sig = _sig;
	}

	auto f_begin = [] (double x) { return (K * exp(a * x) * std::max(exp(x) - 1, 0.0)); };

	auto g_left = [] (double tao) { return 0; };

	auto g_right = [] (double tao) { 
		return K * exp(a * x_right + b * tao) * ( exp(x_right - 2*q*tao/(sig*sig)) - exp(-2*r*tao/(sig*sig)) );
	};
	
	auto u_exact = [] (double x, double tao) { return 0;};
}

namespace UAOPUTBC
{
	double a;
	double b;
	double K;
	double x_left;
	double r;
	double q;
	double sig;

	void init(double _a, double _b, double _K, double _x_left, double _r, double _q, double _sig) {
		a = _a; b = _b; K = _K; x_left = _x_left; r = _r; q = _q; sig = _sig;
	}

	auto f_begin = [] (double x) {
		return (K * exp(a * x) * std::max(1-exp(x), 0.0));
	};

	auto g_left = [] (double tao) {  
		return K * exp(a * x_left + b * tao) * (exp(-2*r*tao/(sig*sig)) - exp(x_left - 2*q*tao/(sig*sig)) );
	};

	auto g_right = [] (double tao) {return 0;};
	
	auto u_exact = [] (double x, double tao) {return 0;};
}

#endif




