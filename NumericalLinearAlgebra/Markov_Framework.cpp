// This file was about finding the tangency portfolio, maxmize portfolio return
// and minimize the portfolio variance.
//
// Zhenfeng Liang
//
// 5:23 PM 9/24/2014, in Elmhurst, NY

#include "Markov_Framework.hpp"

boost::tuple<Matrix, double, double, double> Tan_port(const Matrix& cov, const Matrix& vector_miu, double r_f)
{
	int n = vector_miu.Size1();
//	Matrix w_tan(n,1);
	double expected_return = 0;
	double sd = 0;
	double sharp_ratio = 0;
//	struct TANGENCY_PORT tan_p = {temp_m, 0, 0, 0};
	
	Matrix miu_bar = vector_miu - r_f;
	Matrix x = linear_solve_cholesky(cov, miu_bar);

	Matrix One_coloum(1,n);
	for(int i = 0; i < n; i++)
	{
		One_coloum(0,i) = 1;
	}

	Matrix temp = One_coloum * x; // Temp matrix has only one element
	
	Matrix w_tan = x / temp(0,0);
	expected_return = (w_tan.Trans() * vector_miu)(0,0);
	sd = sqrt(((w_tan.Trans() * cov) * w_tan)(0,0));
	sharp_ratio = (expected_return - r_f) / sd;

	return boost::make_tuple(w_tan, expected_return, sd, sharp_ratio);
}

boost::tuple<Matrix, double, double, double> Min_var_port(const Matrix& cov, const Matrix& vector_miu, double r_f, double r_req)
{
	int n = cov.Size1();
//	Matrix w_min(n,1);

//	struct MIN_VAR_PORT mvp = {temp_m, 0, 0, 0};

	Matrix miu_bar = vector_miu - r_f;

	Matrix w_tan; 
	double expected_return;
	double sd;
	double sharp_ratio_tan_port;
	boost::tie(w_tan, expected_return, sd, sharp_ratio_tan_port) = Tan_port(cov, vector_miu, r_f);

//	struct TANGENCY_PORT tan_p = Tan_port(cov, vector_miu, r_f);
//	Matrix w_T = W_Tangency(cov, vector_miu, r_f);

	double w_min_cash = 1 - (r_req - r_f)/((miu_bar.Trans() * w_tan)(0,0));
	Matrix w_min = w_tan * (1 - w_min_cash);
	double sd_min = sqrt(((w_min.Trans() * cov) * w_min)(0,0));
	double sharp_ratio = (r_req - r_f) / sd_min;

	return boost::make_tuple(w_min, w_min_cash, sd_min, sharp_ratio);
}

boost::tuple<Matrix, double, double, double> Max_return_port(const Matrix& cov, const Matrix& vector_miu, double r_f, double sig_req)
{
	int n = cov.Size1();
	Matrix w_max(n,1);

//	struct MAX_RET_PORT mvp = {temp_m, 0, 0};

	Matrix miu_bar = vector_miu - r_f;

	Matrix x = linear_solve_cholesky(cov, miu_bar);

	double temp = (miu_bar.Trans() * x)(0,0);
	w_max = x * (sig_req / sqrt(temp));

	Matrix One_coloum(1,n);
	for(int i = 0; i < n; i++)
	{
		One_coloum(0,i) = 1;
	}

	double w_max_cash = 1 - (One_coloum * w_max)(0,0);
	double miu_max = r_f + (miu_bar.Trans() * w_max)(0,0);
	double sharp_ratio = (miu_max - r_f) / sig_req;

	return boost::make_tuple(w_max, w_max_cash, miu_max, sharp_ratio);
}