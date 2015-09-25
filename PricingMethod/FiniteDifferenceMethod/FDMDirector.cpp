// This file was created to direct to use FDMTOHeatPDE class to price option.
//
// Zhenfeng Liang 
//
// 12/7/2014

// NOTE!!!!!! CANNOT CALCULATE SEVERAL FDMS AT THE SAME TIME!!!!!SINCE WE ARE USING NAMESPACE TO STORE VARIABLES. BUT
// CONSIDER TO CHANGE TO THE FUNCTION POINTER AND USE THE STRUCT TO INITIALIZE THE BOUNDARY CONDITION.

#include "FDMDirector.hpp"
#include "BackwardEuler.hpp"
#include "ForwardEuler.hpp"
#include "Crank-Nicolson.hpp"

#include "FDMBoundaryCondition.hpp"

#include "../../Option/EuropeanPut.hpp"
#include "../../Option/EuropeanCall.hpp"

#include "..\..\NumericalLinearAlgebra\Matrix.hpp"
#include "..\..\NumericalLinearAlgebra\Read_Write_Csv.hpp"


/***************************************************************************************************************************/
/*************************************************FDMDirector's implementation*********************************************/

Matrix FDMDirector::early_ex_premium()
{// For American Option
	double K = _op_ptr->StrikePrice();
	Matrix result(_M, _N-1);

	if(_op_ptr->OptionType() == "American") 
	{
		for(int m = 1; m <= _M; m++)
		{ // M * N-1 Matrix
			for(int i = 1; i <= _N-1; i++)
			{
				double x = x_left + i * delta_x;
				double tao = m * delta_tao;
				if(_op_ptr->CallPutType() == "Put")
					result(m-1,i-1) = K * exp(a * x + b * tao) * std::max(1 - exp(x), 0.0);
				else if(_op_ptr->CallPutType() == "Call")
					result(m-1,i-1) = K * exp(a * x + b * tao) * std::max(exp(x) - 1, 0.0);
			}
		}
	}
	return result;
}

void FDMDirector::Euro_Amer_init_()
{// Initialize the FDM parameters if the options are American or European Option

	// Get the info about the option
	double S0 = _op_ptr->SpotPrice();
	double K = _op_ptr->StrikePrice();
	double r = _op_ptr->InterestRate();
	double q = _op_ptr->Dividend();
	double sig = _op_ptr->Volatility();
	double T = _op_ptr->Maturity();

	tao_final = T * sig * sig /2;
	delta_tao = tao_final / _M;

	x_left = log(S0/K) + (r - q - sig * sig / 2) * T - 3 * sig * std::sqrt(T);
	x_right = log(S0/K) + (r - q - sig * sig / 2) * T + 3 * sig * std::sqrt(T);
	
	x_compute = log(S0/K);

	double delta_x_temp = std::sqrt(delta_tao / _alpha_temp);
	_N = int(floor((x_right - x_left) / delta_x_temp));

	delta_x = (x_right - x_left) / _N;
	
	alpha = delta_tao /(delta_x * delta_x);

	a = (r - q) / (sig * sig) - 0.5;
	b = ((r - q) / (sig * sig) + 0.5) * ((r - q) / (sig * sig) + 0.5) + 2 * q / (sig * sig);

	if (_op_ptr->CallPutType() == "Put")
	{
		EuroAmerPutBC::init(a, b, K, x_left, r, q, sig);
		f_begin = EuroAmerPutBC::f_begin;
		g_right = EuroAmerPutBC::g_right;
		u_exact = EuroAmerPutBC::u_exact;
		if(_op_ptr->OptionType() == "European") { g_left = EuroAmerPutBC::european_g_left;}
		if(_op_ptr->OptionType() == "American") { g_left = EuroAmerPutBC::american_g_left;}
	}
	else if(_op_ptr->CallPutType() == "Call")
	{
		EuroAmerCallBC::init(a, b, K, x_right, r, q, sig);
		f_begin = EuroAmerCallBC::f_begin;
		g_left = EuroAmerCallBC::g_left;
		u_exact = EuroAmerCallBC::u_exact;
		if(_op_ptr->OptionType() == "European") { g_right = EuroAmerCallBC::european_g_right;}
		if(_op_ptr->OptionType() == "American") { g_right = EuroAmerCallBC::american_g_right;}
	}
}

void FDMDirector::DAO_init_()
{
	// Get the info about the option
	double S0 = _op_ptr->SpotPrice();
	double K = _op_ptr->StrikePrice();
	double r = _op_ptr->InterestRate();
	double q = _op_ptr->Dividend();
	double sig = _op_ptr->Volatility();
	double T = _op_ptr->Maturity();
	double B = _op_ptr->Barrier();

	x_compute = log(S0/K);
	x_left = log(B/K);

	tao_final = T * sig * sig /2;
	delta_tao = tao_final / _M;
	
	double delta_x_temp = std::sqrt(delta_tao / _alpha_temp);
	
	x_right = log(S0/K) + (r - q - sig * sig / 2) * T + 3 * sig * std::sqrt(T);
	_N = int( floor((x_right - x_left)/delta_x_temp) );

	delta_x = (x_right - x_left) / _N;

	alpha = delta_tao /(delta_x * delta_x);
	
	a = (r - q) / (sig * sig) - 0.5;
	b = ((r - q) / (sig * sig) + 0.5) * ((r - q) / (sig * sig) + 0.5) + 2 * q / (sig * sig);

	if (_op_ptr->CallPutType() == "Call")
	{
		DAOCallBC::init(a, b, K, x_right, r, q, sig);
		f_begin = DAOCallBC::f_begin;
		g_right = DAOCallBC::g_right;
		g_left = DAOCallBC::g_left;
		u_exact = DAOCallBC::u_exact;
	}
}

void FDMDirector::UAO_init_()
{
	// Get the info about the option
	double S0 = _op_ptr->SpotPrice();
	double K = _op_ptr->StrikePrice();
	double r = _op_ptr->InterestRate();
	double q = _op_ptr->Dividend();
	double sig = _op_ptr->Volatility();
	double T = _op_ptr->Maturity();
	double B = _op_ptr->Barrier();

	tao_final = T * sig * sig /2;
	delta_tao = tao_final / _M;

	x_left = log(S0/K) + (r - q - sig * sig / 2) * T - 3 * sig * std::sqrt(T);
	x_right = log(B/K);
	
	x_compute = log(S0/K);

	double delta_x_temp = std::sqrt(delta_tao / _alpha_temp);
	_N = int(floor((x_right - x_left) / delta_x_temp));

	delta_x = (x_right - x_left) / _N;
	
	alpha = delta_tao /(delta_x * delta_x);

	a = (r - q) / (sig * sig) - 0.5;
	b = ((r - q) / (sig * sig) + 0.5) * ((r - q) / (sig * sig) + 0.5) + 2 * q / (sig * sig);

	if (_op_ptr->CallPutType() == "Put")
	{
		UAOPUTBC::init(a, b, K, x_left, r, q, sig);
		f_begin = UAOPUTBC::f_begin;
		g_right = UAOPUTBC::g_right;
		g_left = UAOPUTBC::g_left;
		u_exact = UAOPUTBC::u_exact;
	}
}

void FDMDirector::DAO_init_on_the_grid()
{ // Initialize the FDM if the Option is down and out option

	// Get the info about the option
	double S0 = _op_ptr->SpotPrice();
	double K = _op_ptr->StrikePrice();
	double r = _op_ptr->InterestRate();
	double q = _op_ptr->Dividend();
	double sig = _op_ptr->Volatility();
	double T = _op_ptr->Maturity();
	double B = _op_ptr->Barrier();

	x_compute = log(S0/K);
	x_left = log(B/K);

	tao_final = T * sig * sig /2;
	delta_tao = tao_final / _M;
	
	double delta_x_temp = std::sqrt(delta_tao / _alpha_temp);
	
	N_left = int( floor((x_compute - x_left)/delta_x_temp) );

	delta_x = (x_compute - x_left) / N_left;

	alpha = delta_tao /(delta_x * delta_x);

	double x_right_temp = log(S0/K) + (r - q - sig * sig / 2) * T + 3 * sig * std::sqrt(T);

	N_right = int( ceil((x_right_temp - x_compute)/delta_x) );

	_N = N_left + N_right;

	x_right = x_compute + N_right * delta_x;

	a = (r - q) / (sig * sig) - 0.5;
	b = ((r - q) / (sig * sig) + 0.5) * ((r - q) / (sig * sig) + 0.5) + 2 * q / (sig * sig);

	if (_op_ptr->CallPutType() == "Call")
	{
		DAOCallBC::init(a, b, K, x_right, r, q, sig);
		f_begin = DAOCallBC::f_begin;
		g_right = DAOCallBC::g_right;
		g_left = DAOCallBC::g_left;
		u_exact = DAOCallBC::u_exact;
	}
}

double FDMDirector::cal_approx_not_on_the_grid(std::string solve_method)
{
	int i = int(floor((x_compute - x_left)/delta_x));
	Vec xarr = FDM::Mesh_vec(x_left, x_right, _N);
	double S_i = _op_ptr->StrikePrice() * exp(xarr[i]);
	double S_i_plus_1 = _op_ptr->StrikePrice() * exp(xarr[i+1]);

	Matrix u = u_approx(solve_method);
	double V_i = exp(-a * xarr[i] - b * tao_final) * u(_M,i);
	double V_i_plus_1 = exp(-a * xarr[i+1] - b * tao_final) * u(_M,i+1);

	double V_approxi_1 = (S_i_plus_1 - _op_ptr->SpotPrice()) * V_i + (_op_ptr->SpotPrice() - S_i) * V_i_plus_1;
	V_approxi_1 /= S_i_plus_1 - S_i;

	return V_approxi_1;
}

double FDMDirector::cal_approx_on_the_grid(std::string solve_method)
{
	Vec xarr = FDM::Mesh_vec(x_left, x_right, _N);
	Matrix u = u_approx(solve_method);
	double V_approx = exp(-a * x_compute - b * tao_final) * u(_M, N_left);

	return V_approx;
}

Vec FDMDirector::cal_greeks_not_on_the_grid(std::string solve_method)
{
	int i = int(floor((x_compute - x_left)/delta_x));
	Vec xarr = FDM::Mesh_vec(x_left, x_right, _N);

	double K = _op_ptr->StrikePrice();

	Matrix u = u_approx(solve_method);

	double S_i_minus_1 = K * exp(xarr[i-1]);
	double S_i = K * exp(xarr[i]);
	double S_i_plus_1 = K * exp(xarr[i+1]);
	double S_i_plus_2 = K * exp(xarr[i+2]);

	double V_i_minus_1 = exp(-a * xarr[i-1] - b * tao_final) * u(_M, i-1);
	double V_i = exp(-a * xarr[i] - b * tao_final) * u(_M, i);
	double V_i_plus_1 =  exp(-a * xarr[i+1] - b * tao_final) * u(_M, i+1);
	double V_i_plus_2 = exp(-a * xarr[i+2] - b * tao_final) * u(_M, i+2);

	double delta_appro = (V_i_plus_1 - V_i) / (S_i_plus_1 - S_i);
	double temp1 = (V_i_plus_2 - V_i_plus_1) / (S_i_plus_2 - S_i_plus_1) - (V_i - V_i_minus_1) / (S_i - S_i_minus_1);
	double temp2 = (S_i_plus_2 + S_i_plus_1) / 2 - (S_i + S_i_minus_1) / 2;
	double gamma_appro = temp1 / temp2;

	Vec greeks;
	greeks.push_back(delta_appro);
	greeks.push_back(gamma_appro);

	double sig = _op_ptr->Volatility();
	double delta_t = 2 * delta_tao / (sig * sig);
	double V_delta_t_i = exp(-a * xarr[i] - b * (tao_final - delta_tao)) * u(_M-1, i);
	double V_delta_t_i_plus_1 = exp(-a * xarr[i+1] - b * (tao_final - delta_tao)) * u(_M-1, i+1);

	double S0 = _op_ptr->SpotPrice();
	double V_approx_delta_t = ((S_i_plus_1 - S0) * V_delta_t_i + (S0 - S_i) * V_delta_t_i_plus_1) / (S_i_plus_1 - S_i);
	double V_approx_zero = ((S_i_plus_1 - S0) * V_i + (S0 - S_i) * V_i_plus_1) / (S_i_plus_1 - S_i);

	double theta_appro = (V_approx_delta_t - V_approx_zero) / delta_t;
	greeks.push_back(theta_appro);

	Matrix output(8,4);
	output(0,0) = i; 
	output(1,0) = u(_M, i); output(1,1) = u(_M, i+1);
	output(2,0) = S_i; output(2,1) = S_i_plus_1; output(2,2) = V_i; output(2,3) = V_i_plus_1;
	output(3,0) = V_approx_zero; //output(4,0) = abs(V_approx_zero - _op_ptr->V_EXACT());
	output(5,0) = delta_appro; output(6,0) = gamma_appro; output(7,0) = theta_appro;

	WriteMatrix(output, "TestQ11.csv");

	return greeks;
}

Vec FDMDirector:: cal_greeks_on_the_grid(std::string solve_method)
{
	double K = _op_ptr->StrikePrice();
	double S0 = _op_ptr->SpotPrice();

	Vec xarr = FDM::Mesh_vec(x_left, x_right, _N);
	
	double S_minus_1 = K * exp(xarr[N_left - 1]);
	double S_plus_1 = K * exp(xarr[N_left + 1]); 

	Matrix u = u_approx(solve_method);
	double V_minus_1 = exp(-a * xarr[N_left - 1] - b * tao_final) * u(_M, N_left - 1);
	double V0 = exp(-a * xarr[N_left] - b * tao_final) * u(_M, N_left);
	double V_plus_1 = exp(-a * xarr[N_left + 1] - b * tao_final) * u(_M, N_left + 1);

	// Calculate delta
	double delta_central = (V_plus_1 - V_minus_1) / (S_plus_1 - S_minus_1);

	// Calculate gamma
	double temp1 = (S0 - S_minus_1) * V_plus_1 - (S_plus_1 - S_minus_1) * V0 + (S_plus_1 - S0) * V_minus_1;
	double temp2 = (S0 -S_minus_1) * (S_plus_1 - S0) * ((S_plus_1 - S_minus_1)/2);
	double gamma_central = temp1 / temp2;

	// Calculate theta
	double sig = _op_ptr->Volatility();
	double delta_t = 2 * delta_tao / (sig * sig);
	double v_approx_delta_t = exp(-a * xarr[N_left] - b * (tao_final - delta_tao)) * u(_M - 1, N_left);
	double theta_forward = (V0 - v_approx_delta_t) / delta_t;

	Vec result;
	result.push_back(delta_central);
	result.push_back(gamma_central);
	result.push_back(theta_forward);

	return result;
}

FDMDirector::FDMDirector(std::shared_ptr<Option> op_ptr, int M, double alpha_temp, std::string fdm_method)
	: _op_ptr(op_ptr), _M(M), _alpha_temp(alpha_temp), _fdm_method(fdm_method)
{
	if(_op_ptr->OptionType() == "European" || _op_ptr->OptionType() == "American")
		Euro_Amer_init_();
	else if(_op_ptr->OptionType() == "DownAndOut")
		DAO_init_();
	else if(_op_ptr->OptionType() == "UpAndOut")
		UAO_init_();
			
	if(fdm_method == "Backward") {
		fdmpde_ptr = FDMHeatPDEPtr(new BackwardEuler(_M, _N, 0, tao_final, x_left, x_right, f_begin, g_left, g_right, u_exact));
	}
	else if(fdm_method == "Forward") {
		fdmpde_ptr = FDMHeatPDEPtr(new ForwardEuler(_M, _N, 0, tao_final, x_left, x_right, f_begin, g_left, g_right, u_exact));
	}
	else if(fdm_method == "Crank Nicolson") {
		fdmpde_ptr = FDMHeatPDEPtr(new CrankNicolson(_M, _N, 0, tao_final, x_left, x_right, f_begin, g_left, g_right, u_exact));
	}
}

double FDMDirector::alpha_real() const
{
	return alpha;
}

Matrix FDMDirector::u_approx(std::string solve_method)
{
	Matrix early_ex = early_ex_premium();
//	WriteMatrix(early_ex, "Intermediate.csv");
	return fdmpde_ptr->u_approx(solve_method, _op_ptr->OptionType(), early_ex);
}

Vec FDMDirector::approxi_1(std::string solve_method)
{ // Output order: V_approx1, Error_pointwise1

	// For specific American Exact Value
	double v_exact = 4.083817051176386;
	double approx = cal_approx_not_on_the_grid(solve_method);

	Vec result;
	result.push_back(approx);
	if(_op_ptr->OptionType() != "American")
		result.push_back(abs(approx - _op_ptr->V_EXACT()));
	else
		result.push_back(std::abs(approx - v_exact));
	return result;
}

Vec FDMDirector::approxi_2(std::string solve_method)
{// Output order: V_approx2, Error_pointwise2
	
	// For specific American Exact Value
	double v_exact = 4.083817051176386;
	
	int i = int(floor((x_compute - x_left)/delta_x));
	Vec xarr = FDM::Mesh_vec(x_left, x_right, _N);

	Matrix u = u_approx(solve_method);

	double u_approxi_2 = (xarr[i+1] - x_compute) * u(_M, i) + (x_compute - xarr[i]) * u(_M, i+1);
	u_approxi_2 /= xarr[i+1] - xarr[i];

	double V_approx_2 = exp(-a * x_compute - b * tao_final) * u_approxi_2;

	Vec result;
	result.push_back(V_approx_2);

	if(_op_ptr->OptionType() != "American")	
		result.push_back(std::abs(V_approx_2 - _op_ptr->V_EXACT()));
	else
		result.push_back(std::abs(V_approx_2 - v_exact));
		
	return result;
}

double FDMDirector::error_RMS(std::string solve_method)
{
	Vec xarr = FDM::Mesh_vec(x_left, x_right, _N);
	double error = 0;
	int N_RMS = 0;
	double K = _op_ptr->StrikePrice();
	double S0 = _op_ptr->SpotPrice();
	Matrix u = u_approx(solve_method);
//	Matrix temp(_N+1, 3);
	for(int k = 0; k <= _N; k++)
	{
		double Sk = K * exp(xarr[k]);
		double temp_exact = _op_ptr->V_EXACT(Sk);
		if(temp_exact / S0 > 0.00001)
		{
			N_RMS ++;
			double v_approx = exp(-a * xarr[k] - b * tao_final) * u(_M, k);
			//temp(k,0) = Sk;
			//temp(k,1) = v_approx;
			//temp(k,2) = temp_exact;
			error += (v_approx - temp_exact) * (v_approx - temp_exact) / (temp_exact * temp_exact);
		}
	}
	error /= N_RMS;

	error = std::sqrt(error);
//	WriteMatrix(temp, "Intermediate.csv");
	return error;
}

Vec FDMDirector::CalGreeks(std::string solve_method)
{ // Output order Delta, Gamma, Theta
	Vec result = cal_greeks_not_on_the_grid(solve_method);
	return result;
}

Vec FDMDirector::Variance_Reduction(std::string solve_method)
{ // Output order: value of variance reduction, error

	double v_exact = 4.083817051176386; // Just for this specific parameter, you can use the option Exact Pricer
	Vec result;
	OptionPtr euop_ptr;

	if(_op_ptr->CallPutType() == "Put")
	{
		euop_ptr = OptionPtr(new EuropeanPut(_op_ptr->SpotPrice(), _op_ptr->Maturity(), _op_ptr->StrikePrice(),
			_op_ptr->Volatility(), _op_ptr->InterestRate(), _op_ptr->Dividend(), _op_ptr->Dividend_type()));
	}
	if(_op_ptr->CallPutType() == "Call")
	{
		euop_ptr = OptionPtr(new EuropeanCall(_op_ptr->SpotPrice(), _op_ptr->Maturity(), _op_ptr->StrikePrice(),
			_op_ptr->Volatility(), _op_ptr->InterestRate(), _op_ptr->Dividend(), _op_ptr->Dividend_type()));
	}

	FDMDirector euro_dir(euop_ptr, _M, _alpha_temp, _fdm_method);

	double p_ameri = approxi_1(solve_method)[0];
	double p_euro = euro_dir.approxi_1(solve_method)[0];
			
	double p_var_red = p_ameri + (euop_ptr->V_EXACT() - p_euro);
	result.push_back(p_var_red);
	result.push_back(std::abs(p_var_red - v_exact));
	
	return result;
}

Matrix FDMDirector::early_ex_domain()
{ // Only for Crank-Nicolson SOR

	Matrix domain(_M+1, 2);
	Matrix early_premium = early_ex_premium();
	Matrix u = u_approx("SOR");
	Vec xarr = FDM::Mesh_vec(x_left, x_right, _N);
	double T = _op_ptr->Maturity();
	double sig = _op_ptr->Volatility();
	double K = _op_ptr->StrikePrice();

	for(int m = 1; m <= _M; m++)
	{
		int n;
		double t = T - 2 * m * delta_tao / (sig * sig);
		for(n = 1; n <= _N - 1; n++)
		{	
			if(n <= _N - 1 && u(m,n) == early_premium(m-1,n-1) && u(m, n+1) > early_premium(m-1,n))
				break;
		}
		if(n <= _N-1)
		{
			double S_N = K * exp(xarr[n]);
			double S_N_plus_1 = K * exp(xarr[n+1]);
			
			domain(m,0) = t;
			domain(m,1) = (S_N + S_N_plus_1) / 2;
		}
		else
			std::cout << "This option will never early exercise at time: " << t << endl;
	}

	return domain;
}

Matrix FDMDirector::N_x_left_x_right()
{
	Matrix result(1,3);
	result(0,0) = _N; result(0,1) = x_left; result(0,2) = x_right;
	return result;
}