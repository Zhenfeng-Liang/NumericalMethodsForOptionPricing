// This is designed for the NLA class.
// This file includes matrix basic function
//
// Zhenfeng Liang
//
// 11:29 PM, 8/26/2014, Elmhurst, NY
// 8/30/2014 Change the + - and * scalar functions to be friend global functions so as to 
// make the basic operation available, such as 1+m and m+1.
// Add () operator const and non-const versions to read and write the matrix. 
// Note: 用STL vector代替m[n][1]可使程序简化，但运行速度未知，需要进一步对比！

#include "Matrix.hpp"
#include "Solving_Linear_System.hpp"

Matrix::Matrix()
{
	m_row_num = 1;
	m_col_num = 1;

	m_data = new double* [m_row_num];

	for(int j = 0; j < m_row_num; j++)
	{
		m_data[j] = new double [m_col_num];
	}

	for(int j = 0; j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
			m_data[j][k] = 0;
}

Matrix::Matrix(int row_num, int col_num)
{
	m_row_num = row_num;
	m_col_num = col_num;

	m_data = new double* [m_row_num];

	for(int j = 0; j < m_row_num; j++)
	{
		m_data[j] = new double [m_col_num];
	}

	for(int j = 0; j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
			m_data[j][k] = 0;
}

Matrix::Matrix(int row_num, int col_num, double** new_array)
{
	m_row_num = row_num;
	m_col_num = col_num;

	m_data = new double* [m_row_num];

	for(int j = 0; j < m_row_num; j++)
	{
		m_data[j] = new double [m_col_num];
	}

	for(int j = 0; j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
			m_data[j][k] = new_array[j][k];
}

Matrix::Matrix(const Matrix& source)
{
	m_row_num = source.m_row_num;
	m_col_num = source.m_col_num;

	m_data = new double* [m_row_num];

	for(int j = 0; j < m_row_num; j++)
	{
		m_data[j] = new double [m_col_num];
	}

	for(int j = 0;j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
		{//copy each element seperately

			m_data[j][k] = source.m_data[j][k];
		}
}

Matrix::~Matrix()
{
	for(int j = 0; j < m_row_num; j++)
	{
		delete [] m_data[j];
		m_data[j] = NULL;
	}

	delete [] m_data;
	m_data = NULL;
}


int Matrix::Size1() const
{
	return m_row_num;
}

int Matrix::Size2() const
{
	return m_col_num;
}

int Matrix::max_abs_entry_row_index(int a, int b, int k)
{
	int i_max;
	double temp = 0;
	for(int i = a; i <= b; i++)
	{
		if(abs(m_data[i][k]) > temp)
		{
			i_max = i;
			temp = abs(m_data[i][k]);
		}
	}

	return i_max;
}


void Matrix::row_pivot(int i, int j, int k1, int k2)
{
	for(int iterator = k1; iterator <= k2; iterator++)
	{
		double temp = m_data[i][iterator];
		m_data[i][iterator] = m_data[j][iterator];
		m_data[j][iterator] = temp;
	}
}

Matrix Matrix::Trans() const
{
	Matrix temp(m_col_num, m_row_num);
	for(int j = 0;j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
		{//Substract factor seperatly

			temp.m_data[k][j] =  m_data[j][k];
		}

	return temp;
}

Matrix Matrix::inverse() const
{
	int n = m_col_num;
	Matrix temp(n, n);
	
	for(int i = 0; i < n; i++)
	{
		Matrix b(n, 1);
		b(i,0) = 1;
		Matrix x = linear_solve_LU_no_pivoting(*this, b);
		for(int k = 0; k < n; k++)
		{
			temp(k,i) = x(k,0);
		}
	}
	return temp;
}

void Matrix::turn_upside_down()
{
	for(int i = 0; i <= (m_row_num - 1) / 2; i++)
		row_pivot(i, m_row_num - 1 - i ,0, m_col_num - 1);
}

void Matrix::identity_matrix()
{
	for(int j = 0; j < m_row_num; j++)
	{
		m_data[j][j] = 1;
	}
}


double Matrix::norm()
{
	double result = (Trans() * (*this))(0,0);
	return sqrt(result);
}

Matrix& Matrix::operator = (const Matrix& source)
{//Assignment operator

	if(this == &source)
	{
		std::cout << "These Matrixs are identical\n";
		return *this;
	}

	m_row_num = source.m_row_num;
	m_col_num = source.m_col_num;

	for(int j = 0; j < m_row_num; j++)
	{
		delete [] m_data[j];
		m_data[j] = NULL;
	}

	delete [] m_data;
	m_data = NULL;

	m_data = new double* [m_row_num];

	for(int j = 0; j < m_row_num; j++)
	{
		m_data[j] = new double [m_col_num];
	}

	for(int j = 0;j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
		{//copy each element seperately

			m_data[j][k] = source.m_data[j][k];
		}

	return *this;
}

// Matrix operations
Matrix Matrix::operator + (const Matrix& m) const
{
	Matrix temp(m_row_num, m_col_num);

	if((m_row_num != m.m_row_num) || (m_col_num != m.m_col_num))
	{
		cout << "rows or cols are not matched." << endl;
		return temp;
	}

	for(int j = 0;j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
		{//copy each element seperately

			temp.m_data[j][k] =  m_data[j][k] + m.m_data[j][k];
		}
	
	return temp;
}

Matrix Matrix::operator - (const Matrix& m) const
{
	Matrix temp(m_row_num, m_col_num);

	if((m_row_num != m.m_row_num) || (m_col_num != m.m_col_num))
	{
		cout << "rows or cols are not matched." << endl;
		return temp;
	}

	for(int j = 0;j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
		{//copy each element seperately

			temp.m_data[j][k] =  m_data[j][k] - m.m_data[j][k];
		}
	
	return temp;
}

Matrix Matrix::operator * (const Matrix& m) const
{
	Matrix temp(m_row_num, m.m_col_num);
	if(m_col_num != m.m_row_num)
	{
		cout << "This multiplitication is undefined. Row1 != Col2." << endl;
		return temp;
	}

	for(int j = 0; j < m_row_num; j++)
		for(int k = 0; k < m.m_col_num; k++)
		{
			double temp_data = 0;
			for(int flag = 0; flag < m_col_num; flag++)
			{
				temp_data += m_data[j][flag] * m.m_data[flag][k];
			}
			temp.m_data[j][k] = temp_data;
		}
	
	return temp;
}

// Scalar function
Matrix Matrix::operator / (double factor) const
{
	Matrix temp(m_row_num, m_col_num);

	for(int j = 0;j < m_row_num; j++)
		for(int k = 0; k < m_col_num; k++)
		{//Substract factor seperatly

			temp.m_data[j][k] =  m_data[j][k] / factor;
		}
	
	return temp;
}


// Read and Write the elements in the matrix, const and non-const versions
double& Matrix::operator () (int j, int k)
{
	if ((j >= 0) && (j < m_row_num) && (k >= 0) && (k < m_col_num))
	{
		return m_data[j][k];
	}
	else
	{
		std::cout << "The index is out of bound, so return the first element." << std::endl;
		return m_data[0][0];
	}
}

const double& Matrix::operator () (int j, int k) const
{
	if ((j >= 0) && (j < m_row_num) && (k >= 0) && (k < m_col_num))
	{
		return m_data[j][k];
	}
	else
	{
		std::cout << "The index is out of bound, so return the first element." << std::endl;
		return m_data[0][0];
	}
}


Matrix& Matrix::operator <<= (string data)
{
	stringstream iss(data);

	for(int j = 0;j < m_row_num; j++)   
		for(int k = 0; k < m_col_num; k++) 
		{
			string val;
			getline(iss, val, ',');
			stringstream convert(val);
			convert >> m_data[j][k];
		} 

	return *this;
}


// Friend functions

Matrix operator + (const Matrix& m, double factor)
{
	Matrix temp(m.m_row_num, m.m_col_num);

	for(int j = 0;j < m.m_row_num; j++)
		for(int k = 0; k < m.m_col_num; k++)
		{//Add factor seperatly

			temp.m_data[j][k] =  m.m_data[j][k] + factor;
		}
	
	return temp;
}

Matrix operator + (double factor, const Matrix& m)
{
	Matrix temp(m.m_row_num, m.m_col_num);

	for(int j = 0;j < m.m_row_num; j++)
		for(int k = 0; k < m.m_col_num; k++)
		{//Add factor seperatly

			temp.m_data[j][k] =  m.m_data[j][k] + factor;
		}
	
	return temp;
}


Matrix operator - (double factor, const Matrix& m)
{
	Matrix temp(m.m_row_num, m.m_col_num);

	for(int j = 0;j < m.m_row_num; j++)
		for(int k = 0; k < m.m_col_num; k++)
		{//Substract factor seperatly

			temp.m_data[j][k] =  factor - m.m_data[j][k];
		}
	
	return temp;
}

Matrix operator - (const Matrix& m, double factor)
{
	Matrix temp(m.m_row_num, m.m_col_num);

	for(int j = 0;j < m.m_row_num; j++)
		for(int k = 0; k < m.m_col_num; k++)
		{//Substract factor seperatly

			temp.m_data[j][k] = m.m_data[j][k] - factor;
		}
	
	return temp;
}


Matrix operator * (const Matrix& m, double factor)
{
	Matrix temp(m.m_row_num, m.m_col_num);

	for(int j = 0;j < m.m_row_num; j++)
		for(int k = 0; k < m.m_col_num; k++)
		{//Substract factor seperatly

			temp.m_data[j][k] =  m.m_data[j][k] * factor;
		}
	
	return temp;
}

Matrix operator * (double factor, const Matrix& m)
{
	Matrix temp(m.m_row_num, m.m_col_num);

	for(int j = 0;j < m.m_row_num; j++)
		for(int k = 0; k < m.m_col_num; k++)
		{//Substract factor seperatly

			temp.m_data[j][k] =  m.m_data[j][k] * factor;
		}
	
	return temp;
}


std::ostream& operator << (std::ostream& os, const Matrix& m)
{// Print the Matrix

	for (int j = 0; j < m.m_row_num; j++)
	{
		os << "[ ";
		for(int k = 0; k < m.m_col_num; k++)
		{
			os << (m.m_data)[j][k] << " ";
		}
		os << "]" << std::endl;
	}	

	return os;
}

std::istream& operator >> (std::istream &input,Matrix &mat) 
{   
	for(int j = 0;j < mat.Size1(); j++)   
		for(int k = 0; k < mat.Size2(); k++)      
			input >> mat.m_data[j][k];  
	return input;  
}



