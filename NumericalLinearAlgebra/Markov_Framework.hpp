// This file was about finding the tangency portfolio, maxmize portfolio return
// and minimize the portfolio variance.
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#ifndef MARKOV_FRAMEWORK_HPP
#define MARKOV_FRAMEWORK_HPP

#include "Matrix.hpp"
#include <boost/tuple/tuple.hpp>

// Output tuple(w_tan matrix, expected return, sd, sharp ratio)
boost::tuple<Matrix, double, double, double> Tan_port(const Matrix& cov, const Matrix& vector_miu, double r_f); 

//	Output tuple(Matrix w_min; w_min_cash;sd_min; sharp_ratio);
boost::tuple<Matrix, double, double, double> Min_var_port(const Matrix& cov, const Matrix& vector_miu, double r_f, double r_req);

//	Output tuple(Matrix w_max, w_max_cash, miu_max, sharp_ratio;
boost::tuple<Matrix, double, double, double> Max_return_port(const Matrix& cov, const Matrix& vector_miu, double r_f, double sig_req);


#endif